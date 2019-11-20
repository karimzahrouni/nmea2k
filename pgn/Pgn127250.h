#ifndef PGN_127250_H
#define PGN_127250_H

#include "PgnData.h"

#define PGN_127250_PRIORITY 2
#define PGN_127250_DLEN 8
#define PGN_127250_ANGLE_RES 10000
#define PGN_127250_REF_TRUE 0
#define PGN_127250_REF_MAGNETIC 1
#define PGN_127250_REF_ERROR 2
#define PGN_127250_REF_NULL 3

namespace nmea2k{

class Pgn127250:public PgnData{
public:
  Pgn127250(uint8_t sid,
            uint16_t heading,
            int16_t deviation,
            int16_t variation,
            uint8_t reference) :
  PgnData(PGN_127250_PRIORITY,
          127250,
          "Vessel Heading PGN 127250",
          PGN_127250_DLEN){
    _translation.fields.sid = sid;
    _translation.fields.heading = heading;
    _translation.fields.deviation = deviation;
    _translation.fields.variation = variation;
    _translation.fields.reference = reference;
  };

 Pgn127250(unsigned char* data):
  PgnData(PGN_127250_PRIORITY,
	  127250,
	  "Vessel Heading PGN 127250",
	  PGN_127250_DLEN){
    for (int i=0; i<PGN_127250_DLEN; i++)
      _translation.data[i] = data[i]; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t sid(){return _translation.fields.sid;}
  inline void set_sid(uint8_t x){_translation.fields.sid=x;}
  inline uint16_t heading(){return _translation.fields.heading;}
  inline void set_heading(uint16_t x){_translation.fields.heading=x;}
  inline int16_t deviation(){return _translation.fields.heading;}
  inline void set_deviation(int16_t x){_translation.fields.deviation=x;}
  inline int16_t variation(){return _translation.fields.heading;}
  inline void set_variation(int16_t x){_translation.fields.variation=x;}
  inline uint8_t reference(){return _translation.fields.reference;}
  inline void set_reference(uint8_t x){_translation.fields.reference=x;}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t sid;
      uint16_t heading,
          deviation,
          variation;
      uint8_t reference : 2,
          unused : 6;
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
