/** @file Frame.cpp
    @brief nmea2k::Frame implementation
    Dennis Evangelista, 2019
*/

#include "mbed.h"
#include "nmea2k.h"

namespace nmea2k{

  
  Frame::Frame() :
    CANMessage(){
    type = mbed::CANData; 
    format = mbed::CANExtended; 
    //debug("nmea2k::Frame() constructor called\r\n");
  }; // nmea2k::Frame() constructor

  
  Frame::Frame(unsigned int _id,
	       const unsigned char *_data,
	       unsigned char _len) :
    CANMessage(_id,_data,_len,mbed::CANData,mbed::CANExtended){
    //debug("nmea2k::Frame(_id,_data,_len) called (unsigned char data)\r\n");
  }; // nmea2k::Frame(_id,_data,_len) w unsigned char data implementation

  
  Frame::Frame(unsigned int _id,
	       const char *_data,
	       unsigned char _len) :
    CANMessage(_id,_data,_len,mbed::CANData,mbed::CANExtended){
    //debug("nmea2k::Frame(_id,_data,_len) called (char data)\r\n");
  }; // nmea2k::Frame(_id,_data,_len) w char data implementation

  
  Frame::~Frame(){
    //debug("nmea2k::~Frame() destructor called\r\n");
  }; // nmea2k::~Frame() destructor

} // namespace nmea2k
