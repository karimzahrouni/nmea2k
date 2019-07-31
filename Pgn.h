#ifndef PGN_H
#define PGN_H

#include "nmea2k.h"
#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{
  
  class Pgn{
  public:
    PduHeader header; // do I need this???
    unsigned char len;
    union{
      unsigned char data[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
      struct{
	unsigned char unused[8]; 
      } fields;
    } translation;    
    Pgn();
    ~Pgn();

    // factory method for corresponding Pdu(s)
    int encode(Pdu &encoded);
  }; // class Pgn

  class PgnParser{
  public:
    PgnParser();
    ~PgnParser();
    int parse(Pdu &encoded, Pgn &decoded); 
  }
  
} // namespace nmea2k

#endif
