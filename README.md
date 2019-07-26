# USNA Sailbot `nmea2k` mbed library
### Dennis Evangelista

"NMEA 2000" is a registered trademark of NMEA; this work represents experiment and study to create a similar protocol for non-commercial use within USNA autonomous sailing vessels ("Sailbot") and other academic projects. 

## NMEA 2000 implementation
### Layer 1: Physical layer
The physical layer of the Sailbot NMEA2000 bus consists of NMEA2000 thin cabling with 4(5) conductors: (nominal) 12V, ground, CAN high, CAN low, and shield. Sailbot nodes are connected to a cable backbone terminated on each end with 120 ohm terminations. 

### Layer 2: Data link layer
The data link layer transmits single frames from one node to another, and consists of CAN connections; on the mbed LPC1768 and Nucleo L432KC boards these are implemented using the built in CAN library, <https://os.mbed.com/docs/mbed-os/v5.13/apis/can.html>. 

The port is instantiated as a `CAN(PinName rd, PinName tx)` object. A single frame is sent using the `CAN.write(CANMessage msg)` method. A single frame is read using the `CAN.read(CANMessage &msg, int handle=0)` method. A callback function, to be called whenever a `CAN` frame received interrupt is generated, can be attached using the `CAN.attach()` method. 

The CAN bus frequency for the data link layer is 250 kbits/s. This layer uses the `CANExtended` 29-bit identification field. 

### Layer 3/4: Network/Transport layer
The network layer includes ways of transmitting and receiving packets of data that do not fit in a single 8-byte CAN frame, namely ISO 11783 multi-packet (NOT IMPLEMENTED) and NMEA2000 fast packet (default). 

This layer is responsible for breaking a NMEA2000 message into several frames for transmission; or reassembling several frames for decoding into a NMEA2000 message.

### Layer 7: Application layer
This layer provides the application with a means to construct various NMEA2000 messages (for transmission, publishing). This layer also provides the application with functions for parsing received data (recieve, subscribe). 

### User stories
#### Transmit (eventual publish, or outgoing service or action call?)
An mbed acting as a sensor node wishes to publish compass headings. To do so, it should do the following:
* Create the n2k port
* Create the message to send
* Use a write method to send the message. This may be within its own thread (mbed OS5) so as to periodically execute. 

#### Receive (eventual subscribe, or incoming service or action call?)
A different mbed may need to receive sensor data and log it as it comes in:
* Create the n2k port
* As frames are recieved, ignore ones that are not of interest and otherwise pass the ones that are of interest to a parser. 
* When the parser has enough to spit out a result, take the result and log it. 
* This may be within its own thread as well. 

#### Pre-made NMEA2000 PGNs
Users want wind data, rudder movement, sail movement, GPS lat lon ready to go, and the ability to add/extend additional messages. 

## Notes, bugs, and oolies

### `CAN.attach()` bugs in mbed-os
`CAN` uses a Mutex that unfortunately makes ISRs attached to it with `CAN.attach()` act funky. To use this properly, you have to comment out calls to `lock()` and `unlock()` in `mbed-os/drivers/CAN.cpp` so that you can call `CAN.read()` inside your ISR - it is needed because that is what clears the interrupt. See `TESTS/physical/interrupt-vomit` for an example that does this and uses an `EventQueue` to set additional events (e.g. `printf` calls) outside the `CAN::RxIrq` interrupt context. 
