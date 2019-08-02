#include "Pgn127245.h"
#include "mbed.h"

namespace nmea2k{
  
  Pgn127245::Pgn127245() :
    Pgn(),len(PGN127245_LEN){
    debug("nmea2k::Pgn127245() constructor called %p\r\n",this); 
  };
  
  //~Pgn127245();

  int Pgn127245::encode(PduHeader *h,
			Pdu *encoded){
    encoded->set_header(*h); // copy ISO header to encoded PDU
    memcpy(encoded->data,_translation.data,len); // copy data to PDU
    encoded->len = len;
    return MBED_SUCCESS; 
  }
  
} \\namespace nmea2k
