/** @file CANLayer.h
    @brief nmea2k::CANlayer for USNA Sailbot nmea2k-like navigational network
    Dennis Evangelista, 2019
*/

#ifndef CANLAYER_H
#define CANLAYER_H

#include "Callback.h" 
#include "drivers/CAN.h" 
#include "PinNames.h"
#include "Frame.h"

/** @def NMEA2K_FREQUENCY
    @brief CAN bus frequency for nmea2k is 250000 Hz */
#define NMEA2K_FREQUENCY 250000

namespace nmea2k{

  /** nmea2k::CANLayer is the physical and data link layer for nmea2k
      It is a CAN bus running at 250000 Hz, and is pretty much inheriting
      everything from the underlying mbed::CAN. The other main difference
      is it uses nmea2k::Frame rather than mbed::CANMessage as the 
      message type. 
   */
  class CANLayer:public mbed::CAN{

  public:
    /** @brief Creates a nmea2k interface connected to specific pins
        @param rd, read from transmitter
        @param td, transmit to transmitter 
        
        On LPC1768 these are probably p9 and p10, or p30 and p29 for
        SY202 rigs. CAN frequency is set to NMEA2K_FREQUENCY, 
        or 250000 Hz. 
    */
    CANLayer(PinName rd, PinName td);

    /** @brief Write a Frame to the nmea2k bus 
        @param f, the Frame to write
        @returns
          0 if write failed,
          1 if successful 
        
          Pretty much inherited from CAN.
    */
    int write(Frame f);

    /** @brief Read a Frame from the nmea2k bus
        @param f, a Frame to read to
        @param handle, a message filter handle, 0 for any message
        @returns
          0 if no message arrived,
          1 if message arrived
        
          Pretty much inherited from CAN. 
    */
    int read(Frame &f, int handle = 0);

    /** @brief Attach a function to call whenever a CAN frame 
        received interrupt is generated.
        
        @param func, a pointer to a void() function, or 0 to set none
        @param type, which CAN interrupt to attach the member 
        function to, e.g. CAN::RxIrq for message received.

        This function locks the deep sleep while a callback is attached.
        Pretty much inherited from CAN. 
    */
    void attach(Callback<void()> func, IrqType type=RxIrq);
  }; // class CANLayer
 
} // namespace nmea2k

#endif
