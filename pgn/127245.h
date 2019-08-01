#ifndef PGN127245_H
#define PGN127245_H

#include "Pgn.h"
#include "PduHeader.h"
#include "Pdu.h"

#define PGN127245_LEN 8

class Pgn127245:public Pgn{
public:
  Pgn127245();
  ~Pgn127245();

  int encode(PduHeader *h,
	     Pdu *encoded)
    
  // getters (apply scaling, resolution, units)
  unsigned char instance();
  unsigned char direction_order();
  unsigned char angle_order();
  float position();

  // setters (apply scaling, resolution, units). 
  void set_instance(unsigned char i);
  void set_direction_order(unsigned char d);
  void set_angle_order(unsigned char a);
  void set_position(float p);

 private:
  union{
    unsigned char data[PGN127245_LEN];
    struct{
      unsigned char unused[PGN127245_LEN]; 
    }
  } _translation;
};





class Pgn127245Parser:public PgnParser{
public:
  Pgn127245Parser();
  ~Pgn127245Parser();
  int parse(Pdu *encoded, Pgn127245 *decoded); 
};

#endif
