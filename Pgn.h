#ifndef PGN_H
#define PGN_H

#include "nmea2k.h"
#include "Pdu.h"

namespace nmea2k{
  
  class Pgn{
  public:
    PduHeader header;
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

  int encode(Pgn &raw, Pdu &encoded);
  
} // namespace nmea2k

#endif
