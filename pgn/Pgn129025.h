#ifndef PGN_129025_H
#define PGN_129025_H

#include "PgnData.h"

#define PGN_129025_PRIORITY 2
#define PGN_129025_DLEN 8
// TODO Fix latitude and longitude resolution!
#define PGN_129025_RES_LATITUDE 1
#define PGN_129025_RES_LONGITUDE 1

namespace nmea2k{

class Pgn129025:public PgnData{
public:
  
 Pgn129025(int32_t latitude, int32_t longitude):
  PgnData(PGN_126993_PRIORITY,
          127245,
          "Position, Rapid Update PGN 129025",
          PGN_129025_DLEN){
    _translation.fields.latitude = latitude;
    _translation.fields.longitude = longitude;
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline int32_t latitude(){return _translation.fields.latitude;}
  inline int32_t longitude(){return _translation.fields.longitude;}
  inline void set_latitude(int32_t x){_translation.fields.latitude=x;}
  inline void set_longitude(int32_t x){_translation.fields.longitude=x;}
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint32_t latitude,
	longitude;
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
