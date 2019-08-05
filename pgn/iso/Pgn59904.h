#ifndef PGN_59904_H
#define PGN_59904_H

#include "PgnData.h"

#define PGN_59904_PRIORITY 6
#define PGN_59904_DLEN 8

namespace nmea2k{

class Pgn59904:public PgnData{
public:
  
Pgn59904(uint32_t pgn):
  PgnData(PGN_59904_PRIORITY,
          59904,
          "ISO Request PGN 59904",
          PGN_59904_DLEN){
    set_pgn(pgn); 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint32_t pgn(){
    uint32_t result = pgn[0];
    result = (result << 8) + pgn[1];
    result = (result << 8) + pgn[2];
    return result;
  }
  inline void set_pgn(uint32_t x){
    _translation.fields.pgn[0] = (x>>16) & 0xff;
    _translation.fields.pgn[1] = (x>>8) & 0xff;
    _translation.fields.pgn[2] = x & 0xff; 
  }
  
private:
  union{
    unsigned char data[3] = {0xff,0xff,0xff};
    struct{
      uint8_t pgn[3];
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
