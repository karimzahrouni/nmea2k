#include "mbed.h"
#include "Pgn.h"

namespace nmea2k{

  Pgn::Pgn(){
    debug("Pgn() empty constructor called\r\n");
  }

  Pgn::~Pgn(){
    debug("~Pgn() destructor called\r\n");
  }

  int Pgn::encode(Pdu &encoded){
    MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				MBED_ERROR_CODE_INVALID_OPERATION),
		"Pgn::encode() should be overriden by subclasses" );
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }

  PgnParser::PgnParser(){
    debug("PgnParser() empty constructor called\r\n"); 
  }

  PgnParser::~PgnParser(){
    debug("~PgnParser() destructor called\r\n"); 
  }

  int PgnParser::parse(Pdu &encoded, Pgn &decoded){
    MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
				MBED_ERROR_CODE_INVALID_OPERATION),
		"PgnParser::parse() should be overrided by subclasses");
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }
  
  
} // namespace nmea2k

