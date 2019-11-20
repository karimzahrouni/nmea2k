#ifndef PGN_126993_H
#define PGN_126993_H

#include "PgnData.h"

#define PGN_126993_PRIORITY 7
#define PGN_126993_DLEN 8

namespace nmea2k{

class Pgn126993:public PgnData{
public:
  
 Pgn126993(uint16_t update_rate,
	   uint8_t heartbeat_sequence_counter):
  PgnData(PGN_126993_PRIORITY,
          126993,
          "Heartbeat PGN 126993",
          PGN_126993_DLEN){
    _translation.fields.update_rate = update_rate;
    _translation.fields.heartbeat_sequence_counter =
      heartbeat_sequence_counter; 
  };

 Pgn126993(unsigned char* data):
  PgnData(PGN_126993_PRIORITY,
	  126993,
	  "Heartbeat PGN 126993",
	  PGN_126993_DLEN){
    for (int i=0; i<PGN_126993_DLEN; i++)
      _translation.data[i] = data[i];
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint16_t update_rate(){return _translation.fields.update_rate;}
  inline void set_update_rate(uint16_t x){
    _translation.fields.update_rate = x;
  }
  inline uint8_t heartbeat_sequence_counter(){
    return _translation.fields.heartbeat_sequence_counter;
  }
  inline void set_heartbeat_sequence_counter(uint8_t x){
    _translation.fields.heartbeat_sequence_counter = x;}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint16_t update_rate;
      uint8_t heartbeat_sequence_counter,
	unused[5];
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
