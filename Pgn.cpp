/** @file Pgn.cpp
    @brief Pgn implementation file
    Dennis Evangelista, 2019
*/

#include "Pgn.h"
#include "mbed.h"
#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{

  Pgn::Pgn():len(NMEA2K_SINGLE_FRAME_MAX_LEN){
    debug("Pgn() empty constructor called %p\r\n",this);
  }

  /*
  // By rule of 3, comment this or also declare copy constructor and operator
  // this was just trivial destructor anyway... 
  Pgn::~Pgn(){
    debug("~Pgn() destructor called %p\r\n",this);
  }
  */

  int Pgn::encode(PduHeader *h,
		  Pdu *encoded){
    MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				MBED_ERROR_CODE_INVALID_OPERATION),
		"Pgn::encode() should be overriden by subclasses" );
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }

  void Pgn::get_data(unsigned char *d, unsigned char *l){
    *l = len;
    memcpy(d,_translation.data,len);
    return; 
  }

  void Pgn::set_data(unsigned char *x, unsigned char len){
    this->len = len; 
    memcpy(_translation.data,x,len);
    return; 
  }





  
  PgnParser::PgnParser(){
    debug("PgnParser() empty constructor called\r\n"); 
  }

  PgnParser::~PgnParser(){
    debug("~PgnParser() destructor called\r\n"); 
  }

  int PgnParser::parse(Pdu *encoded, Pgn *decoded){
    if (encoded->len == decoded->len){
      decoded->set_data(encoded->data,encoded->len);
      return MBED_SUCCESS;
    }
    else{
      debug("warning: encoded Pdu has wrong length for this Pgn, no puedo\r\n");
      MBED_WARNING( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				  MBED_ERROR_CODE_INVALID_ARGUMENT),
		    "Encoded Pdu has wrong length for this Pgn\r\n"); 
      return MBED_ERROR_CODE_INVALID_ARGUMENT;
    } // else
  } // int parse(encoded, decoded)
  
  
} // namespace nmea2k

