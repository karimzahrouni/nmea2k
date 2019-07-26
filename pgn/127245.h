#ifndef PGN127245_H
#define PGN127245_H

#define PGN127245_LEN 8

class Pgn127245:public Pgn{
public:
  Pgn127245();
  ~Pgn127245();
  //inherit P, DP, PF, PS, SA from Pgn? 
  
  //data translation table using bit field union trick
  /*union {
    unsigned char data[PGN127245_LEN];
    struct {
    } fields; 
    } data;
  */
  
  //Pdu pdu(); // factory method, inherited from Pgn?

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
};





class Pgn127245Parser:public PgnParser{
public:
  //Pgn parse(Pdu m); // factory method, inherited from PgnParser
  Pgn127245Parser();
  ~Pgn127245Parser();
};

#endif
