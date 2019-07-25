/** @file nmea2k.h
    @brief nmea2k library for CAN-based navigational network like "NM2K"

    nmea2k.h header file
    Header file for "NM2K"-like navigational network for USNA Sailbot use
    Dennis Evangelista, 2019
*/

#ifndef NMEA2K_H
#define NMEA2K_H
#define NMEA2K_VERSION "14.3.0" //!< nmea2k version for Sailbot Hull 14 mod 3
#define NMEA2K_FREQUENCY 250000 //!< CAN bus frequency for NM2K is 250000 Hz

#include "mbed.h"

namespace nmea2k {

  class Nmea2kFrame:public CANMessage{
  public:
    Nmea2kFrame();
    Nmea2kFrame(unsigned int, const unsigned char *, unsigned char);
    Nmea2kFrame(unsigned int, const char *, unsigned char); 
    ~Nmea2kFrame(); 
  };

  class Nmea2kCAN:public CAN{
  public:
    Nmea2kCAN(PinName, PinName);
    ~Nmea2kCAN();
    int write(Nmea2kFrame);
    int read(Nmea2kFrame, int);
    void attach(Callback<void()>, IrqType); 
  };










  

  


  /** Iso11783Header is ued for encoding and decoding CAN extended 
      32(29) bit id into stuff used by Nmea2k. */
  struct Iso11783Header{
    : 3;                  //<! ignore first three bits
    unsigned char p : 3;  //<! priority, used only by CAN hardware layer
    unsigned char r : 1;  //<! reserved (= 0) by ISO 11783-3
    unsigned char dp : 1; //<! data page
    unsigned char pf;     //<! PDU format
    unsigned char ps;     //<! PDU specfic: dest, grp ext, or proprietary
    unsigned char sa;     //<! source address
  }; // Iso11783Header
  
  /** PDUHeader is a union for easy translation between CAN 32(29) bit id 
      and ISO11783-3 header fields
  */
  union PDUHeader{
    unsigned int id; //!< CAN extended 32(29) bit address id
    Iso11783Header iso; //!< equivalent ISO 11783-3 header fields
  }; // PDUHeader
  
  
  class BasePDU:public Nmea2kFrame{
  public:
    PDUHeader header; //<! Used to translate CAN id <-> PGN etc.
    unsigned int pgn;
    unsigned char da; 
    BasePDU();
    BasePDU(unsigned int, const unsigned char *, unsigned char);
    BasePDU(unsigned int, const char *, unsigned char);
    BasePDU(unsigned char, unsigned char,
	    unsigned char, unsigned char, unsigned char,
	    const unsigned char *, unsigned char);
    BasePDU(unsigned char, unsigned char,
	    unsigned char, unsigned char, unsigned char,
	    const char *, unsigned char);
    ~BasePDU(); 
  };

  class Nmea2k{
  private:
    Nmea2kCAN _nmea2k;
    
  public:
    Nmea2k();
    ~Nmea2k();
    // send queue and thread
    // hook for attaching receipt handler
  };

  
} // namespace nmea2k

#endif // NMEA2K_H


