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

    inline uint8_t p(){return _htrans.iso.p;}
    inline void set_p(uint8_t x){_htrans.iso.p = x & 0x7;} 
    uint32_t pgn();
    void set_pgn(uint32_t x);
    uint8_t da();
    void set_da(uint8_t x);
    inline uint8_t sa(){return _htrans.iso.sa;}
    inline void set_sa(uint8_t x){_htrans.iso.sa = x & 0xff;}

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
    } _htrans;
	
  }; // class Nmea2kMessage


  class Nmea2kName{
  public:
    // constructors and destructors
    Nmea2kName();
    //~Nmea2kName();

    // attribute set and get

  private:
    union {
      uint8_t data[8] = {0xff,0xff,0xff,0xff,
			 0xff,0xff,0xff,0xff};
      struct{
	uint32_t id : 21,
	  manufacturer_code : 11;
	uint8_t device_instance_lower : 3, //<! aka ECU instance
	  device_instance_upper : 5, //<! aka Function Instance
	  device_function, //<! aka Function
	  reserved : 1,
	  device_class : 7,
	  system_instance : 4, //<! aka device class instance
	  industry_group : 3,
	  address_capable : 1; //<! aka arbitrary address capable
      } fields;
    } _dtrans;
  };


  class Nmea2kProductInfo{
  public:
    // constructors and destructors:
    Nmea2kProductInfo();
    //~Nmea2kProductInfo();

    // attribute set and get
    // LATER
    
  private:
    union{
      uint8_t data[134];
      struct{
	uint32_t nmea_2000_version : 16,
	  product_code : 16;
	char 
	  model_id[32],
	  software_version_code[32],
	  model_serial_code[32];
	uint8_t certification_level,
	  load_equivalency;
      } fields;
    } _dtrans;
      
  };

  
  class Nmea2k{
  public:
    // constructors and destructors: 
    Nmea2k();
    //~Nmea2k();

    // methods
    int transmit(Nmea2kMessage *m); 
    // int transmit_multipacket(Nmea2kMessage *m); 
    // int transmit_fastpacket(Nmea2kMessage *m); 

    // attribute set and get
    Nmea2kName * name();
    void set_name(Nmea2kName *x);
    Nmea2kProductInfo * pinfo();
    void set_pinfo(Nmea2kProductInfo *x); 
    // uint8_t max_tx_rate();
    // void set_max_tx_rate(uint8_t x); 
    
    /* OPEN QUESTIONS
       1. Where to provide hook for scanning incoming PGN and address
       and dispatching raw packets to a parser, using rx packet queue. 

       2. Where to provide hook for scanning through complete
       received messages and dispatching based on what we got, using 
       incoming message queue. 
     */
    
  private:
    // name
    // product info
    // max_tx_rate
    // address
    // CAN bus

    // outgoing message queue
    // tx frame queue, process, thread, single frame and fast packet
    // tx queue, process, thread, multipacket LATER
    
    // rx frame queue, process, thread, single frame and fast packet
    // rx queue, process, thread, multipacket LATER
    // incoming message queue
    
  }; // class Nmea2k
  
  
} // namespace nmea2k

#endif

