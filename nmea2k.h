/** @file nmea2k.h
    @brief nmea2k library for CAN-based navigational network like "nmea2k"

    nmea2k.h header file
    Header file for "nmea2k"-like navigational network for USNA Sailbot use
    Dennis Evangelista, 2019
*/

#ifndef NMEA2K_H
#define NMEA2K_H

#define NMEA2K_VERSION "14.3.0" //!< nmea2k version for Sailbot Hull 14 mod 3
#define NMEA2K_FREQUENCY 250000 //!< CAN bus frequency for NM2K is 250000 Hz
#define NMEA2K_BROADCAST 255 //!< Address used for broadcast messages

#include "mbed.h"

namespace nmea2k {



  
  /** nmea2k::Frame is a single frame of data. It inherits nearly everything 
      from mbed::CANMessage but is set to use CANData type and 
      CANExtended format. Mainly this is done for clean abstraction 
      purposes. 

      Frame is one of the primitives used in layer 1 (physical layer) and
      layer 2 (data link layer) of nmea2k. 
  */ 
  class Frame:public mbed::CANMessage {
  public:
    /** Creates empty nmea2k Frame */ 
    Frame();

    /** Creates nmea2k::Frame with specific content.
	@param _id, raw message ID (for CAN purposes)
	@param _data, message data
	@param _len, message data length

	For nmea2k use, type is CANData, format is CANExtended. 
	This is within the constructors and should not be altered
	by the user. */ 
    Frame(unsigned int _id, const unsigned char *_data, unsigned char _len=8);

    /** Creates nmea 2k Frame with specific content.
	@param _id, raw message ID (for CAN purposes)
	@param _data, message data
	@param _len, message data length

	For nmea2k use, type is CANData, format is CANExtended.
	This is within the constructors and should not be altered 
	by the user. */ 
    Frame(unsigned int _id, const char *_data, unsigned char _len=8);

    /** Destructor for nmea2k Frame class */ 
    ~Frame();
  }; // class Frame


  /** nmea2k::CanLayer implements layer 2, the data link layer. It inherits
      from the builtin mbed::CAN class. It is set to use bus frequency 
      NMEA2K_FREQUENCY (250000 Hz). One constructor is provided, 
      nmea2k::CanLayer(rd,td), plus a destructor.

      Several functions are inherited from mbed::CAN that are likely to be 
      useful, namely read(), write(), and attach(), which attaches a callback
      for use when a CAN::RxIrq is generated during receipt ofa  new CAN frame.

      To allow proper functioning of CAN::RxIrq interrupt service routines, 
      we have to alter the behavior of CAN.read() to not include a Mutex 
      lock() and unlock(). This workaround seems to work currently but 
      should be watched if they fix CAN's behavior later and it starts to 
      become buggy. 
  */
  class CanLayer:public mbed::CAN {
  public:

    /** Class constructor for nmea2k::CanLayer class
	@param rd, receive from transceiver (must be CAN capable, eg p9, p30)
	@param td, transmit to transceiver (must be CAN capable, eg p10, p29)

	Example:
	@code
	nmea2k::CanLayer sailbus(p9,p10); // p30,p29 also work on LPC1768, SY202
	@code
    */
    CanLayer(PinName rd, PinName td);

    /** Destructor for nmea2k::CanLayer class */ 
    ~CanLayer();

    /* The following are modified from mbed::CAN behavior to use
       nmea2k::Frame for abstraction purposes and to deal with the Mutex
       during reads. */

    /** Write a single nmea2k::Frame to the bus. 
	@param frame, the Frame to write.
	@returns
	  0 if write failed
	  1 if write was successful
    */
    int write(Frame frame);

    /** Read a single nmea2k::Frame from the bus
	@param frame, a Frame to read to
	@param handle message filter handle (0 for any message) 
	@returns
	  0 if no message arrived
	  1 if message arrived
	Behavior of this function is modified from CAN::read() 
	to not use Mutex lock() unlock(); this may result in 
	odd behavior in future but currently seems to work. 
    */
    int read(Frame &frame, int handle=0);

    /** Attach a function to call whenever a CAN frame received interrupt 
	is generated.  This function locks the deep sleep while the 
	callback is attached. 
	@param func, a pointer to a void function, or 0 to set as none
	@param type, which CAN interrupt to attach the member function to
    */
    void attach(mbed::Callback<void()> func, CAN::IrqType type=CAN::RxIrq);

    // not exposing filter since we'll probably need to look for both
    // NMEA2K_BROADCAST as well as our own node address? 
  }; // class CanLayer















  /** Iso11783Header_t is used for encoding and decoding CAN extended
      32(29) bit id into stuff used by Nmea2k. These are defined here
      from LSB to MSB.
  */
  typedef struct Iso11783Header_t {
    unsigned char sa, //<! source address
      ps,     //<! PDU specific e.g. dest addr, grp ext, proprietary
      pf,     //<! PDU format
      dp : 1, //<! data page
      r : 1,  //<! reserved (= 0) by ISO 11783-3
      p : 3,  //<! priority, used only by CAN hardware layer
      ignore: 3;    //<! ignore first three bits, named so they can be set
  } Iso11783Header_t; // Iso11783Header_t

  /** PduHeader_t is a union for easy translation between CAN 32(29) bit id
      and ISO11783-3 header fields
  */
  typedef union PduHeader_t {
    unsigned int id; //!< CAN extended 32(29) bit address id
    Iso11783Header_t iso; //!< equivalent ISO 11783-3 header fields
  } PduHeader_t; // PduHeader_t




  
  /** Pdu contains a Protocol Data Unit, which is a single frame that has
      priority, data page, PDU format, PDU specific, and source address.
      A Pdu has a PGN, and may have a destination address; these can be
      found and used in routing the Pdu to the correct place.
  */
  class Pdu:public Frame {
  public:
    PduHeader_t header; //<! used to translate CAN id <-> PGN etc.

    /** Creates empty PDU
     */
    Pdu();

    /** Creates PDU with specific content. 
	@param _id, message id (for CAN purposes)
	@param _data, message data
	@param _len, message data length

	Pdu inherits from Frame but knows about ISO 11783-3 headers
	and thus has priority, data page, PDU format, PDU specific, and 
	source address, accessed via PduHeader_t member Pdu::header. 

	For convenient dispatch of received message, getters for
	PGN and destination address are provided, i.e. Pdu::pgn() and Pdu::da(),
	respectively. 
    */
    Pdu(unsigned int _id, const unsigned char * _data, unsigned char len=8);

    /** Creates PDU with specific content. 
	@param _id, message id (for CAN purposes)
	@param _data, message data
	@param _len, message data length

	Pdu inherits from Frame but knows about ISO 11783-3 headers
	and thus has priority, data page, PDU format, PDU specific, and 
	source address, accessed via PduHeader_t member Pdu::header. 

	For convenient dispatch of received message, getters for
	PGN and destination address are provided, i.e. Pdu::pgn() and Pdu::da(),
	respectively. 
    */
    Pdu(unsigned int _id, const char * data, unsigned char len=8);

    /* TODO LATER - need to decide which calling signatures we actually
       want???
    Pdu(unsigned char, unsigned char,
        unsigned char, unsigned char, unsigned char,
        const unsigned char *, unsigned char);
    Pdu(unsigned char, unsigned char,
        unsigned char, unsigned char, unsigned char,
        const char *, unsigned char);
    */

    /** Destructor for nmea2k::Pdu class */ 
    ~Pdu();

    
    // setters
    /** Set CAN id 
	@param _id, the desired id, used when constructing from a received
	message. Necessary to 'override' CAN id to allow proper decoding 
	of the necessary ISO11783-3 header stuff. 
    */ 
    void set_id(unsigned int _id); 


    
    // getters
    /** Get CAN id 
	@returns
	  the CAN id of the PDU, for use during transmission
	This function is necessary to `override' CAN id to allow proper
	encoding of necessary ISO11783-3 header stuff. 
     */
    unsigned int id(); 
    
    /** Get PGN
	@returns 
	  the PGN of the PDU, for message dispatch upon receipt 
    */
    unsigned int pgn();
    
    /** Get destination address
	@returns 
	  the destination address of the PDU, for message
	  dispatch upon receipt. Returns NMEA2K_BROADCAST
	  if message is a broadcast message or has no
	  destination address
    */
    unsigned char da(); 
  }; // class Pdu







  /*
  class Nmea2k {
  public:
    Nmea2k();
    ~Nmea2k();

    // send
    // send_fast LATER
    // send_multi LATER not within Nmea2k 

    // attach
    // hook for user context receipt handling, rx callback
    // hook for tx callback? 

  private:
    // _tx_queue
    // _tx_thread

    // _rx_queue
    // _rx_thread?
  };
  */

} // namespace nmea2k

#endif // NMEA2K_H


