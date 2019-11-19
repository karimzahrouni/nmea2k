#ifndef PGN_127245_H
#define PGN_127245_H

#include "PgnData.h"

#define PGN_127245_PRIORITY 2
#define PGN_127245_DLEN 8
#define PGN_127245_DIRECTION_NONE 0
#define PGN_127245_DIRECTION_RIGHT 1
#define PGN_127245_DIRECTION_LEFT 2
#define PGN_127245_ANGLE_NONE 0x7fff
#define PGN_127245_ANGLE_RES 10000

namespace nmea2k{

  class Pgn127245:public PgnData{
  public:
  
 Pgn127245(uint8_t instance, uint8_t direction_order,
	   int16_t angle_order, int16_t position):
  PgnData(PGN_127245_PRIORITY,
          127245,
          "Rudder PGN 127245",
          PGN_127245_DLEN){
    _translation.fields.instance = instance;
    _translation.fields.direction_order = direction_order;
    _translation.fields.angle_order = angle_order;
    _translation.fields.position = position;
  };
  
  unsigned char* data(){return &_translation.data[0];}
  inline uint8_t instance(){return _translation.fields.instance;}
  inline void set_instance(uint8_t x){_translation.fields.instance=x;}
  inline uint8_t direction_order(){return _translation.fields.direction_order;}
  inline void set_direction_order(uint8_t x){
    _translation.fields.direction_order=x;
  }
  inline int16_t angle_order(){return _translation.fields.angle_order;}
  inline void set_angle_order(int16_t x){
    _translation.fields.angle_order=x;
  }
  inline int16_t position(){return _translation.fields.position;}
  inline void set_position(int16_t x){
    _translation.fields.position=x;
  }
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
                              0xff,0xff,0xff,0xff};
    struct{
      uint8_t instance,
          reserved : 5,
          direction_order : 3;
      uint16_t angle_order,
          position,
          unused;
    } fields;
  } _translation;
};


  class Pgn127245Parser: public PgnParser{
  public:
    
  Pgn127245Parser():
    PgnParser(){
    };

    SharedPtr<Pgn127245> parse(Frame f){
      // for simple single frame PGN,
      // try creating a new Pgn127245
      // copy the frame data to it
      // if all is well return it
      // otherwise return NULL

      // seems kinda dumb to have to do this for each guy
      // why not just have a constructor case with data? 
      return NULL;
    }

  private:
  }; // Pgn127245Parser
  

 
} // namespace nmea2k

#endif
