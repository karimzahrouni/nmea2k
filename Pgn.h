#ifndef PGN_H
#define PGN_H

#include "nmea2k.h"
#include "Pdu.h"

namespace nmea2k{
  
  class Pgn{
  public:
    PduHeader header; // do I need this???
    unsigned char len;
    union{
      unsigned char data[8];
      struct{
	unsigned char unused[8]; 
      } fields;
    } translation;    
    Pgn();
    ~Pgn();
  }; // class Pgn

  // abstract factory methods
  int encode(Pgn &raw, Pdu &encoded);
  int decode(Pdu &raw, Pgn &decoded); 
  
} // namespace nmea2k

#endif
