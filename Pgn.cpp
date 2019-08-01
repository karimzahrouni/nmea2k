/** @file Pgn.cpp
    @brief Pgn implementation file
    Dennis Evangelista, 2019
*/

#include "mbed.h"
#include "Pgn.h"

namespace nmea2k{

  Pgn::Pgn(){
    debug("Pgn() empty constructor called %p\r\n",this);
  }

  Pgn::~Pgn(){
    debug("~Pgn() destructor called %p\r\n",this);
  }

  int Pgn::encode(unsigned int sa,
		  Pdu *encoded,
		  unsigned char p,
		  unsigned char da){
    MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				MBED_ERROR_CODE_INVALID_OPERATION),
		"Pgn::encode() should be overriden by subclasses" );
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }

  void set_data(unsigned char *x, unsigned char len){
    memcpy(_translation.data,x,len);
  }





  
  PgnParser::PgnParser(){
    debug("PgnParser() empty constructor called\r\n"); 
  }

  PgnParser::~PgnParser(){
    debug("~PgnParser() destructor called\r\n"); 
  }

  int PgnParser::parse(Pdu *encoded, Pgn *decoded){
    MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				MBED_ERROR_CODE_INVALID_OPERATION),
		"PgnParser::parse() should be overrided by subclasses");
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }
  
  
} // namespace nmea2k

