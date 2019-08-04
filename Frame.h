/** @file Frame.h
    @brief Frame header for nmea2k library

    Frame.h header file
    Frames are special CANMessages sent in the data link layer of nmea2k
    Dennis Evangelista
*/

#ifndef FRAME_H
#define FRAME_H

#include "drivers/CAN.h" 

namespace nmea2k{
  
  /** @brief A single frame of nmea2k data
      nmea2k::Frame is a single frame of data. It is an mbed::CANMessage, so
      it inherits nearly everything, but is set to use CANData type and
      CANExtended format. Mainly this is done for clean abstraction purposes. 
      Inheritance was used here because of is-a... 
      
      CANMessage has additional public members id, data, and len. It
      is OK to access data and len but for compatibility with downstream
      PDU stuff we will try to avoid using Frame.id directly; use
      the get and set functions instead. 

      Frame is one of the primitives used in layer 1 (physical layer)
      and layer 2 (data link layer) of nmea2k. 

      Frame does _not_ know about ISO11783-3 header stuff; for that 
      purpose it is aggregated with a PduHeader in a Pdu object. 
  */
  class Frame:public mbed::CANMessage {
    
  public:
    /** Creates empty nmea2k::Frame */
    Frame();

    /** Creates nmea2k::Frame with specific content.
	@param id, raw message id (for CAN purposes)
	@param data, message data
	@param len, message data length

	For nmea2k use, type is CANData, format is CANExtended.
	This is within the constructors and should not be altered 
	by they user. 
    */
    Frame(unsigned int id, const unsigned char *data, unsigned char len=8);

    /** Creates nmea2k::Frame with specific content.
	@param id, raw message id (for CAN purposes)
	@param data, message data
	@param len, message data length

	For nmea2k use, type is CANData, format is CANExtended.
	This is within the constructors and should not be altered 
	by they user. 
    */
    Frame(unsigned int id, const char *data, unsigned char len=8);

    /** Destructor for nmea2k::Frame class */
    // Based on rule of three I don't want to define this otherwise
    // I also have to define some other junk or risk getting strange
    // destructor calls when things are copied or whatever. It was a
    // trivial destructor anyway, so I'll leave it out here and accept
    // the default one the compiler produces. We can put it back in
    // if necessary for debugging purposes? 
    //~Frame(); 

  }; // class Frame

  
} // namespace nmea2k

#endif
