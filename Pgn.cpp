#include "mbed.h"
#include "nmea2k.h"
#include "Pgn.h"

namespace nmea2k{

  Pgn::Pgn(){
  }

  Pgn::~Pgn(){
  }

  int Pgn::encode(Pdu &encoded){
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }

  PgnParser::PgnParser(){
  }

  PgnParser::~PgnParser(){
  }

  int PgnParser::parse(Pdu &encoded, Pgn &decoded){
    return MBED_ERROR_CODE_INVALID_OPERATION;
  }
  
  
} // namespace nmea2k

