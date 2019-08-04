#ifndef PGN_126993_H
#define PGN_126993_H

#include "PgnData.h"

#define PGN_126993_PRIORITY 7
#define PGN_126993_DLEN 8

namespace nmea2k{

class Pgn126993:public PgnData{
public:
  
 Pgn126993(uint16_t interval_100, uint8_t count):
  PgnData(PGN_126993_PRIORITY,
          126993,
          "Heartbeat PGN 126993",
          PGN_126993_DLEN){
    _translation.fields.interval = interval_100;
    _translation.fields.count = count; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t unused[3],
        count;
      uint16_t interval; 
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
