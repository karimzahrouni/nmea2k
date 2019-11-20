#ifndef PGN_59392_H
#define PGN_59392_H

#include "PgnData.h"

#define PGN_59392_PRIORITY 6
#define PGN_59392_DLEN 8
#define PGN_59392_ACK 0
#define PGN_59392_NACK 1
#define PGN_59392_ACCESS_DENIED 2
#define PGN_59392_ADDRESS_BUSY 3

namespace nmea2k{

class Pgn59392:public PgnData{
public:
  
Pgn59392(uint8_t control,
         uint8_t group_function,
         uint32_t pgn):
  PgnData(PGN_59392_PRIORITY,
          59392,
          "ISO Acknowledgement PGN 59392",
          PGN_59392_DLEN){
    set_control(control);
    set_group_function(group_function);
    set_pgn(pgn); 
  };
  
 Pgn59392(unsigned char* data):
  PgnData(PGN_59392_PRIORITY,
	  59392,
	  "ISO Acknowledgement PGN 59392",
	  PGN_59392_DLEN){
    for (int i=0; i<PGN_59392_DLEN; i++)
      _translation.data[i] = data[i]; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t control(){return _translation.fields.control;}
  inline void set_control(uint8_t x){_translation.fields.control=control;}
  inline uint8_t group_function(){return _translation.fields.group_function;}
  inline void set_group_function(uint8_t x){
    _translation.fields.group_function=x;
  }
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
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t control,
          group_function,
          reserved[3],
          pgn[3];
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
