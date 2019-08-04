#ifndef PGNDATA_H
#define PGNDATA_H

namespace nmea2k{

  
  class PgnData{
  public:
    char *name;
    unsigned int dlen; 
    PgnData();

    // set fields (later), get data
    unsigned char* data();   
  }; // class PgnData

  
  class PgnParser{
  public:
    PgnParser();
    PgnData* parse(unsigned char *data, unsigned char len); 
  };

  
} // namespace nmea2k

#endif
