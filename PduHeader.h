/** @file PduHeader.h
    @brief PduHeader related definitions for CAN-based "nmea2k" network

    PduHeader.h header file
    Header file for "nmea2k"-like navigational network for USNA Sailbot use
    Dennis Evangelista, 2019
*/

#ifndef PDUHEADER_H
#define PDUHEADER_H

#include "nmea2k.h"

namespace nmea2k {

  /** @brief ISO11783-3 Protocol Data Unit (PDU) header information
      ISO11783-3 divides the 32 bit CAN extended ID into several
      fields, specifically, priority (P), reserved (R), data page (DP),
      PDU format (PF), PDU specific (PS, which may be a destination 
      address, group extension, or proprietary), and source address (SA). 

      A parameter group number (PGN) is formed from R, DP, PF, and 
      (optionally) PS. Depending on the PGN, there may be a destination
      address (DA) or not. 

      These are implemented here as nmea2k::PduHeader, which is intended
      to be aggregated together with nmea2k::Frame to form a complete
      Protocol Data Unit (nmea2k::Pdu), which is the minimum unit
      that gets transmitted around in the nmea2k protocol. 
   */
  class PduHeader{
    
  public:
    
    /** Creates empty uninitialized nmea2k::PduHeader */
    PduHeader();
    
    /** nmea2k::PduHeader from full CAN 32(29) bit id */
    PduHeader(unsigned int id);

    /** nmea2k::PduHeader from priority, pgn, source, and destination */ 
    PduHeader(unsigned char priority,
	      unsigned int pgn,
	      unsigned char sa,
	      unsigned char da=NMEA2K_BROADCAST);

    /** Destructor for PduHeader class */ 
    ~PduHeader;

    /** get source address (SA) byte */
    inline unsigned char sa() {return _translation.iso.sa}
    /** set source address (SA) byte */
    inline void set_sa(unsigned char x) { _translation.iso.sa = x;}
    /** get PDU specific (PS) byte */
    inline unsigned char ps() {return _translation.iso.ps; }
    /** set PDU specific (PS) byte */
    inline void set_ps(unsigned char x) { _translation.iso.ps = x;}
    /** get PDU format (PF) byte */ 
    inline unsigned char pf() {return _translation.iso.pf;}
    /** set PDU format (PF) byte */ 
    inline void set_pf(unsigned char x) {_translation.iso.pf = x;}
    /** get data page (DP) bit */
    inline unsigned char dp() {return _translation.iso.dp;}
    /** set data page (DP) bit */
    inline void set_dp(unsigned char x) {_translation.iso.df = (x & 0x01);}
    /** get reserved (R) bit */
    inline unsigned char r() {return _translation.iso.r;}
    /** set reserved (R) bit, should be 0*/
    inline void set_r(unsigned char x){
      //MBED_ASSERT(x==0);
      _translation.iso.r = (x & 0x01);
    } // void set_r(x)
    /** get priority (P), 3 bits; 0 highest, 6 lowest priority */ 
    inline unsigned char p() {return _translation.iso.p;}
    /** set priority (P), 3 bits; 0 highest, 6 lowest priority */ 
    inline void set_p(unsigned char x) {_translation.iso.p = (x & 0x07);}
    /** get ignored upper 3 bits, should never use */ 
    inline unsigned char ignore() {return _translation.iso.ignore;}
    /** set ignored upper 3 bits, should never use */
    inline void set_ignore(unsigned char x){
      _translation.iso.ignore = (x & 0x07);
    } // void set_ignore(x)

    /** @brief Return parameter group number (PGN)
	@returns parameter group number
	PGN is formed from reserved bit, data page bit, PDU format
	field (8 bits), and, optionally, PDU specific group extension
	(for PF>=240). See ISO11783-3 p2. 
    */
    unsigned int pgn();

    /** @brief Sets parameter group number (PGN) 
	@returns
	  MBED_SUCCESS (0) if PGN was successfully set
	  (negative) error code if PGN was badly formed
	Gives a warning if a badly formed PGN is specified, e.g.
	with PF<240 but with non-zero PS. See ISO11783-3 p2.
     */
    int set_pgn(unsigned int x);

    /** @brief Returns destination address (DA)
	@returns
	  destination address, if PF<240
	  NMEA2K_BROADCAST (255) otherwise
	See ISO11783-3 p2. 
    */
    unsigned char da();

    /** @brief Set destination address (DA)
	@returns
	  MBED_SUCCESS (0) if DA was successfully set
	  (negative) error code if a non-broadcast address is 
	  specified for PF>=240. 
	See ISO11783-, p2. 
    */
    int set_da(unsigned char x);

    /** @brief Get 32(29) bit CAN extended id 
	Named get_id() to avoid confusion with CANMessage public member
	id, which I can't hide (CAN requires it for write and read
	and there's not a convenient way to change that behavior.)
	Use this instead of directly accessing id in Frame, PduHeader,
	and Pdu. 
     */
    inline unsigned int get_id() {return _translation.id;}

    /** @brief Set 32(29) bit CAN extended id
	@returns
	  MBED_SUCCESS (0) if CAN ID successfully set
	  (negative) error code otherwise, i.e. if id would result in 
	  badly formed PGN
	Use this instead of directly accessing CANMessage::id in Frame, 
	PduHeader, and Pdu. CAN requires the id to write and read,
	and does not provide a convenient way to modify this behavior
	to control id+ISO header stuff together... 
     */
    int set_id(unsigned int x);    

  private:
    
    /** @brief Handy translation table between ISO11783-3 and CAN ID
	Uses bit fields and a union... may be buggy if ported to other
	procesors based on endianness (i.e. watch this when going from
	LPC1768 to Nucleo L432KC!); however the mbed C/C++ implementations
	seem to allow this as it is a pretty normal way to work with low
	level stuff on a microprocessor. The ISO fields are listed here
	in the struct from LSB to MSB to work correctly on an LPC1768
	and should be regression tested using the TESTS/pduheader/ tests
	after major changes. */ 
    union {
      unsigned int id; //<! CAN extended 32(29) bit address id

      /** @brief provides ISO11783-3 header fields */
      struct {
	unsigned int sa : 8, //<! source address
	  ps : 8, //<! PDU specific, e.g. dest addr, grp ext, proprietary
	  pf : 8, //<! PDU format
	  dp : 1, //<! data page
	  r : 1, //<! reserved (= 0) by ISO 11783-3
	  p : 3, //<! priority, used by CAN hardware layer
	  ignore : 3; //<! ignore first three bits; named so they can be zeroed
      } iso; //<! provides ISO11783-3 header fields
    } _translation; //<! handy translation table between CAN and ISO11783-3
    }; // class PduHeader
  
} // namespace nmea2k 

#endif
