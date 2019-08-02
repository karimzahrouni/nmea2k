#ifndef PGN_H
#define PGN_H

#include "nmea2k.h"
#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{
  
  class Pgn{
  public:
    unsigned int len;
    Pgn();
    ~Pgn();

    // factory method for corresponding Pdu(s)
    int encode(nmea2k::PduHeader *h, nmea2k::Pdu *encoded);

    // set and get
    void set_data(unsigned char *x, unsigned char len); 

  protected:
    union{
      unsigned char data[8] = {0xff};
      struct{
	unsigned char ununsed[8];
      } fields;
    } _translation;
  }; // class Pgn

  class PgnParser{
  public:
    PgnParser();
    ~PgnParser();
    int parse(nmea2k::Pdu *encoded, nmea2k::Pgn *decoded); 
  };
  
} // namespace nmea2k

#endif
