#ifndef PGN_130314_H
#define PGN_130314_H

#include "PgnData.h"

#define PGN_130314_PRIORITY 5
#define PGN_130314_DLEN 8
#define PGN_130314_ATMOSPHERIC_PRESSURE 0
#define PGN_130314_WATER_PRESSURE 1
#define PGN_130314_STEAM_PRESSURE 2
#define PGN_130314_COMPRESSED_AIR_PRESSURE 3
#define PGN_130314_HYDRAULIC_PRESSURE 4
#define PGN_130314_PRESSURE_HIRES 10

namespace nmea2k{

class Pgn130314:public PgnData{
public:
  
  Pgn130306(uint8_t sid,
            uint8_t instance,
            uint8_t source,
            uint32_t pressure):
  PgnData(PGN_130314_PRIORITY,
          130314,
          "Actual Pressure PGN 130314",
          PGN_130314_DLEN){
    _translation.fields.sid = sid;
    _translation.fields.instance = instance;
    _translation.fields.source = source;
    _translation.fields.pressure = pressure;
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t sid(){return _translation.fields.sid;}
  inline void set_sid(uint8_t x){_translation.fields.sid=x;}
  inline uint8_t instance(){return _translation.fields.instance;}
  inline void set_instance(uint8_t x){_translation.fields.instance=x;}
  inline uint8_t source(){return _translation.fields.source;}
  inline void set_source(uint8_t x){_translation.fields.source=x;}
  inline uint32_t pressure(){
    return _translation.fields.pressure;
  }
  inline void set_pressure(uint32_t x){
    _translation.fields.pressure=x;
  }
  
  
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff};
    struct{
      uint8_t sid,
          instance,
          source;
      uint32_t pressure;
      uint8_t reserved;
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
