#ifndef PGN_130306_H
#define PGN_130306_H

#include "PgnData.h"

#define PGN_130306_PRIORITY 2
#define PGN_130306_DLEN 8
#define PGN_130306_SPEED_RES 100
#define PGN_130306_ANGLE_RES 10000
#define PGN_130306_REF_TRUE 0
#define PGN_130306_REF_MAGNETIC 1
#define PGN_130306_REF_APPARENT 2
#define PGN_130306_REF_TRUE_BOAT 3
#define PGN_130306_REF_TRUE_WATER 4

namespace nmea2k{

class Pgn130306:public PgnData{
public:
  
  Pgn130306(uint8_t sid,
            uint16_t wind_speed,
            uint16_t wind_angle,
            uint8_t reference) :
  PgnData(PGN_130306_PRIORITY,
          130306,
          "Wind Data PGN 130306",
          PGN_130306_DLEN){
    _translation.fields.sid = sid;
    _translation.fields.wind_speed = wind_speed;
    _translation.fields.wind_angle = wind_angle;
    _translation.fields.reference = reference; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t sid(){return _translation.fields.sid;}
  inline void set_sid(uint8_t x){_translation.fields.sid=x;}
  inline uint16_t wind_speed(){return _translation.fields.wind_speed;}
  inline void set_wind_speed(uint16_t x){_translation.fields.wind_speed=x;}
  inline uint16_t wind_angle(){return _translation.fields.wind_angle;}
  inline void set_wind_angle(uint16_t x){_translation.fields.wind_angle=x;}
  inline uint8_t reference(){return _translation.fields.reference;}
  inline void set_reference(uint8_t x){_translation.fields.reference=x;}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t sid;
      uint16 wind_speed,
          wind_angle;
      uint8_t reference,
          unused[2];
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
