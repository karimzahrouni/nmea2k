#ifndef PGN_130312_H
#define PGN_130312_H

#include "PgnData.h"

#define PGN_130312_PRIORITY 5
#define PGN_130312_DLEN 8
#define PGN_130312_SEA_TEMP 0
#define PGN_130312_OUTSIDE_TEMP 1
#define PGN_130312_INSIDE_TEMP 2
#define PGN_130312_ENGINE_ROOM_TEMP 3
#define PGN_130312_MAIN_CABIN_TEMP 4
#define PGN_130312_LIVE_WELL_TEMP 5
#define PGN_130312_BAIT_WELL_TEMP 6
#define PGN_130312_REEFER_TEMP 7
#define PGN_130312_HEATING_SYS_TEMP 8
#define PGN_130312_DEWPOINT_TEMP 9
#define PGN_130312_APPARENT_WIND_CHILL_TEMP 10
#define PGN_130312_THEORETICAL_WIND_CHILL_TEMP 11
#define PGN_130312_HEAT_INDEX_TEMP 12
#define PGN_130312_FREEZER_TEMP 13
#define PGN_130312_EXHAUST_GAS_TEMP 14
#define PGN_130312_TEMP_RES 100

namespace nmea2k{

class Pgn130312:public PgnData{
public:
  
  Pgn130306(uint8_t sid,
            uint8_t instance,
            uint8_t source,
            uint16_t actual_temperature, 
            uint16_t set_temperature):
  PgnData(PGN_130312_PRIORITY,
          130312,
          "Temperature PGN 130312",
          PGN_130312_DLEN){
    _translation.fields.sid = sid;
    _translation.fields.instance = instance;
    _translation.fields.source = source;
    _translation.fields.actual_temperature = actual_temperature;
    _translation.fields.set_temperature = set_temperature;
  };

 Pgn130312(unsigned char* data):
  PgnData(PGN_130312_PRIORITY,
	  130312,
	  "Temperature PGN 130312",
	  PGN_130312_DLEN){
    for (int i=0; i<PGN_130312_DLEN; i++)
      _translation.data[i] = data[i]; 
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t sid(){return _translation.fields.sid;}
  inline void set_sid(uint8_t x){_translation.fields.sid=x;}
  inline uint8_t instance(){return _translation.fields.instance;}
  inline void set_instance(uint8_t x){_translation.fields.instance=x;}
  inline uint8_t source(){return _translation.fields.source;}
  inline void set_source(uint8_t x){_translation.fields.source=x;}
  inline uint16_t actual_temperature(){
    return _translation.fields.actual_temperature;
  }
  inline void set_actual_temperature(uint16_t x){
    _translation.fields.actual_temperature=x;
  }
  inline uint16_t get_set_temperature(){
    return _translation.fields.set_temperature;
  }
  inline void set_set_temperature(uint16_t x){
    _translation.fields.set_temperature=x;
  }
  
  
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                             0xff,0xff,0xff,0xff};
    struct{
      uint8_t sid,
          instance,
          source;
      uint16_t actual_temperature,
          set_temperature;
      uint8_t reserved;
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
