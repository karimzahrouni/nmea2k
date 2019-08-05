#ifndef PGN_126993_H
#define PGN_126993_H

#include "PgnData.h"

#define PGN_126993_PRIORITY 7
#define PGN_126993_DLEN 8

namespace nmea2k{

class Pgn126993:public PgnData{
public:
  
 Pgn126993(uint16_t interval, uint8_t count):
  PgnData(PGN_126993_PRIORITY,
          126993,
          "Heartbeat PGN 126993",
          PGN_126993_DLEN){
    _translation.fields.interval = interval;
    _translation.fields.count = count; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint16_T interval;
      uint8_t count,
	unused[5];
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
