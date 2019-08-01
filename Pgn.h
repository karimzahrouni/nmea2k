#ifndef PGN_H
#define PGN_H

#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{
  
  class Pgn{
  public:
    PduHeader header; // do I want this? 
    Pgn();
    ~Pgn();

    // factory method for corresponding Pdu(s)
    int encode(Pdu &encoded);

    // need to set and get header, data, and any fields
    int set_header(PduHeader h);
    int set_data(unsigned char *data, unsigned char len);

  private:
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
    int parse(Pdu &encoded, Pgn &decoded); 
  };
  
} // namespace nmea2k

#endif
