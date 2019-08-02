#ifndef PGN_H
#define PGN_H

#include "PduHeader.h"
#include "Pdu.h"

#define NMEA2K_SINGLE_FRAME_MAX_LEN 8

namespace nmea2k{
  
  class Pgn{
  public:
    unsigned int len; //<! using unsigned int for future MultiPacket use
    Pgn();
    ~Pgn();

    // factory method for corresponding Pdu(s)
    int encode(PduHeader *h, Pdu *encoded);

    // set and get
    void get_data(unsigned char *d, unsigned char *l); 
    void set_data(unsigned char *x, unsigned char len); 

  protected:
    union{
      unsigned char data[NMEA2K_SINGLE_FRAME_MAX_LEN] = {0xff};
      struct{
	unsigned char ununsed[NMEA2K_SINGLE_FRAME_MAX_LEN];
      } fields;
    } _translation;
  }; // class Pgn

  class PgnParser{
  public:
    PgnParser();
    ~PgnParser();
    int parse(Pdu *encoded, Pgn *decoded); 
  };
  
} // namespace nmea2k

#endif
