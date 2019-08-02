#ifndef PGN127245_H
#define PGN127245_H

#include "Pgn.h"
#include "math.h"
#include "PduHeader.h"
#include "Pdu.h"

#define PGN127245_LEN 8
#define PGN127245_DIR_NONE 0
#define PGN127245_DIR_RIGHT 1
#define PGN127245_DIR_LEFT 2
#define PGN127245_DIR_AMIDSHIPS 3
#define PGN127245_ANG_NONE 0x7fff
#define PGN127245_POS_NONE 0x7fff

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
    inline void set_instance(uint8_t x){
      _translation.fields.instance=x;
    }
    inline void set_direction_order(uint8_t x){
      _translation.fields.direction_order = x & 0x3; 
    };
    inline void set_angle_order(float rad){
      int16_t x = round(10000*rad); 
      _translation.fields.angle_order = x;
    }
    inline void set_position(float rad){
      int16_t x = round(10000*rad); 
      _translation.fields.position = x;
    };

  private:
    union{
      unsigned char data[PGN127245_LEN] = {0xff,0xff,0xff,0xff,
					   0xff,0xff,0xff,0xff};
      /** @struct _translation
	  @brief Handy translation table
	  See this reference: <http://data.over-blog-kiwi.com/0/54/01/67/20151122/ob_f92436_nmea2k-network-design-v2.pdf> 
       */
      struct{ // fields in reverse order... 
	int16_t unused,
	  position, //<! current angle of rudder in units of 0.0001 rad
	  angle_order; //<! 0x7fff indicates no angle order present? 
        uint8_t reserved : 6, 
	  direction_order : 2, //<! 0 is no direction order 
	  instance; //<! Identifies rudder instance, 0-251 (did they mean 255?). 
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
