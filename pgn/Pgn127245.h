#ifndef PGN127245_H
#define PGN127245_H

#include "Pgn.h"
#include "PduHeader.h"
#include "Pdu.h"

#define PGN127245_LEN 8

namespace nmea2k{

  class Pgn127245:public Pgn{
  public:

    Pgn127245();


    
    int encode(PduHeader *h,
	       Pdu *encoded);

    // getters (apply scaling, resolution, units)
    inline unsigned char instance(){
      return _translation.fields.instance; 
    }
    inline unsigned char direction_order(){
      return _translation.fields.direction_order; 
    }
    float angle_order(){
      return (float) _translation.fields.angle_order * 1e-4;
    }
    float position(){
      return (float) _translation.fields.position * 1e-4;
    }

    // setters (apply scaling, resolution, units). 
    inline void set_instance(unsigned char x){
      _translation.fields.instance=x;
    }
    inline void set_direction_order(unsigned char x){
      _translation.fields.direction_order = x & 0x3; 
    };
    inline void set_angle_order(float rad){
      int x = round(10000*rad); 
      _translation.fields.angle_order[0] = x & 0xff;
      _translation.fields.angle_order[1] = (x >> 8) & 0xff;
    }
    inline void set_position(float rad){
      int x = round(10000*rad); 
      _translation.fields.position[0] = x & 0xff;
      _translation.fields.position[1] = (x >> 8) & 0xff; 
    };

  private:
    union{
      unsigned char data[PGN127245_LEN] = {0xff,0xff,0xff,0xff,
					   0xff,0xff,0xff,0xff};
      struct{
	uint16t position;
	uint16t angle_order;
        unsigned char reserved : 6, 
	  direction_order : 2,
	  instance,
	  unused[2]; 
      } fields; 
    } _translation;
  }; // class Pgn127245







  class Pgn127245Parser:public PgnParser{
  public:
    Pgn127245Parser();
    //~Pgn127245Parser();
    int parse(Pdu *encoded, Pgn127245 *decoded); 
  };





  
} // namespace nmea2k

#endif
