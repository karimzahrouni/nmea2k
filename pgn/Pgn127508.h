#ifndef PGN_127508_H
#define PGN_127508_H

#include "PgnData.h"

#define PGN_127508_PRIORITY 3
#define PGN_127508_DLEN 8
#define PGN_127508_VOLTAGE_RES 100
#define PGN_127508_CURRENT_RES 10
#define PGN_127508_TEMPERATURE_RES 100

namespace nmea2k{

class Pgn127508:public PgnData{
public:
  Pgn127508(uint8_t instance, // instance
	    int16_t voltage, 
	    int16_t current, 
	    uint16_t temperature,
	    uint8_t sid) : // sensor id
  PgnData(PGN_127508_PRIORITY,
          127508,
          "Battery Status PGN 127508",
          PGN_127508_DLEN){
    _translation.fields.instance = instance;
    _translation.fields.voltage = voltage;
    _translation.fields.current = current;
    _translation.fields.temperature = temperature;
    _translation.fields.sid = sid;
  };
  
  unsigned char* data(){return &_translation.data[0];}

  inline uint8_t instance(){return _translation.fields.instance;}
  inline void set_instance(uint8_t x){_translation.fields.instance = x;}
  inline int16_t voltage(){return _translation.fields.voltage;}
  inline void set_voltage(int16_t x){_translation.fields.voltage=x;}
  inline int16_t current(){return _translation.fields.current;}
  inline void set_current(int16_t x){_translation.fields.current=x;}
  inline uint16_t temperature(){return _translation.fields.temperature;}
  inline void set_temperature(int16_t x){_translation.fields.temperature=x;}
  inline uint8_t sid(){return _translation.fields.sid;}
  inline void set_sid(uint8_t x){_translation.fields.sid=x;}
    
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t instance;
      int16_t voltage,
	current,
	temperature;
      uint8_t sid;
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
