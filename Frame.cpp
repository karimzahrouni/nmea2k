/** @file Frame.cpp
    @brief nmea2k::Frame implementation
    Dennis Evangelista, 2019
*/

#include "Frame.h"
//#include "mbed_debug.h"
#include "drivers/CAN.h"

namespace nmea2k{

  
  Frame::Frame() :
    mbed::CANMessage(){
    type = CANData; 
    format = CANExtended; 
    //debug("nmea2k::Frame() constructor called %p\r\n",this);
  } // nmea2k::Frame() constructor

  
  Frame::Frame(unsigned int id,
	       const unsigned char *data,
	       unsigned char len) :
    mbed::CANMessage(id,data,len,CANData,CANExtended){
    //debug("nmea2k::Frame(id,data,len) called (unsigned char data) %p\r\n", this);
  } // nmea2k::Frame(id,data,len) w unsigned char data implementation

  
  Frame::Frame(unsigned int id,
	       const char *data,
	       unsigned char len) :
    mbed::CANMessage(id,data,len,CANData,CANExtended){
    //debug("nmea2k::Frame(id,data,len) called (char data) %p\r\n",this);
  } // nmea2k::Frame(id,data,len) w char data implementation
  
} // namespace nmea2k
