/** @file nmea2k.h
    @brief nmea2k library for CAN-based navigational network like "nmea2k"

    nmea2k.h header file
    CAN-based navigational network like "nmea2k" for USNA Sailbot use
    Dennis Evangelista, 2019
*/


#ifndef NMEA2K_H
#define NMEA2K_H

/** @def NMEA2K_VERSION
    @brief nmea2k version for Sailbot Hull 14 mod 3 */
#define NMEA2K_VERSION "14.3.0"

#include "Frame.h"
#include "CANLayer.h"
#include "PduHeader.h"
#include "PgnData.h"

namespace nmea2k{

  class Nmea2kMessage{
  public:
    const char *name;
    unsigned int dlen; 
    
    Nmea2kMessage();
    //~Nmea2kMessage();

    inline uint8_t p(){return _header.iso.p;}
    inline void set_p(uint8_t x){_header.iso.p = x & 0x7;} 
    uint32_t pgn();
    void set_pgn(uint32_t x);
    uint8_t da();
    void set_da(uint8_t x);
    inline uint8_t sa(){return _header.iso.sa;}
    inline void set_sa(uint8_t x){_header.iso.sa = x & 0xff;}

    uint8_t* get_data(); // for subclass use
    
  private:
    union {
      uint32_t id;
      struct {
	uint32_t sa : 8,
	  ps : 8,
	  pf : 8,
	  dp : 1,
	  r : 1,
	  p : 3,
	  ignore : 3;
      } iso;
    } _header
	
  }; // class Nmea2kMessage





  
  class Nmea2k{
  public:
    Nmea2k();
    //~Nmea2k();

    // methods
    // int transmit(Nmea2kMessage *m); 
    // int transmit_multipacket(Nmea2kMessage *m); 
    // int transmit_fastpacket(Nmea2kMessage *m); 

    // attribute set and get
    //pointer to name type name();
    //void set_name(pointer to name type);
    // pointer to product info type pinfo();
    // void set_pinfo(pointer to product info type); 
    // uint8_t max_rate();
    // void set_max_rate(uint8_t x); 
    
    
  private:
    // CAN bus
    
    // tx queue, process, thread, single frame and fast packet
    // rx queue, process, thread, single frame and fast packet
    // tx queue, process, thread, multipacket
    // rx queue, process, thread, multipacket
    
  }; // class Nmea2k
  
  
} // namespace nmea2k

#endif

