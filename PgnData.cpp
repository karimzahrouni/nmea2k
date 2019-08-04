/** @file Pgn.cpp
    @brief Pgn implementation file
    Dennis Evangelista, 2019
*/

#include "PgnData.h"
#include "mbed_debug.h"
#include "mbed_error.h"

namespace nmea2k{

PgnData::PgnData() :
    name("Generic PGN"),
    dlen(8){
  debug("nmea2k::PgnData() empty constructor called %p\r\n",this);
}

unsigned char* PgnData::data(){
  MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
                              MBED_ERROR_INVALID_OPERATION),
              "should be overridden by subclasses");
  return NULL; 
}

PgnParser::PgnParser(){
  debug("PgnParser() empty constructor called %p\r\n",this); 
}

PgnData* PgnParser::parse(unsigned char *data, unsigned char len){
  MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
                              MBED_ERROR_CODE_INVALID_OPERATION),
              "should be overridden by subclasses");
  return NULL;
} // PgnData* parse(data, len);
  
  
} // namespace nmea2k

