/** @file Pgn.cpp
    @brief Pgn implementation file
    Dennis Evangelista, 2019
*/

#include "PgnData.h"
//#include "mbed_debug.h"
#include "mbed_error.h"

namespace nmea2k{

PgnData::PgnData() :
    p(7), pgn(0), name("Generic Empty PGN 0"), dlen(8){
  //debug("nmea2k::PgnData() empty constructor called %p\r\n",this);
}

PgnData::PgnData(unsigned char p, unsigned int pgn, const char *name, unsigned int dlen) :
    p(p),pgn(pgn),name(name),dlen(dlen){
  //debug("nmea2k::PgnData(p,pgn,name,dlen) called %p\r\n", this); 
}

unsigned char* PgnData::data(){
  MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
                              MBED_ERROR_INVALID_OPERATION),
              "PgnData::data() should be overridden by subclasses");
  return NULL; 
}

PgnParser::PgnParser(){
  //debug("PgnParser() empty constructor called %p\r\n",this); 
}

  SharedPtr<nmea2k::PgnData> PgnParser::parse(nmea2k::Frame f){
  MBED_ERROR( MBED_MAKE_ERROR(MBED_MODULE_APPLICATION,
                              MBED_ERROR_CODE_INVALID_OPERATION),
              "PgnParser::parse() should be overridden by subclasses");
  return NULL;
} // PgnData* parse(data, len);
  
  
} // namespace nmea2k

