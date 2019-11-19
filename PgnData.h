#ifndef PGNDATA_H
#define PGNDATA_H

#include "platform/SharedPtr.h"

namespace nmea2k{

  
  class PgnData{
  public:
    unsigned char p; 
    unsigned int pgn; 
    const char *name;
    unsigned int dlen;
    PgnData();

    PgnData(unsigned char p, unsigned int pgn, const char *name, unsigned int dlen); 

    // set fields (later), get data
    unsigned char* data();   
  }; // class PgnData

  
  class PgnParser{
  public:
    PgnParser();
    SharedPtr<PgnData> parse(PgnData d); 
  };

  
} // namespace nmea2k

#endif
