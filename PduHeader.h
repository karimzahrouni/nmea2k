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

  class PduHeader{
  public:
    /** Creates empty uninitialized PduHeader */ 
    PduHeader();

    /** PduHeader from full CAN 32(29) bit id, used on receipt */ 
    PduHeader(unsigned int _id);

    /** PduHeader from priority, pgn, source and destination (optional)*/
    PduHeader(unsigned char priority,
	      unsigned int pgn,
	      unsigned char sa,
	      unsigned char da=NMEA2K_BROADCAST);

    /** Destructor for PduHeader class */ 
    ~PduHeader();

    
    // getters and setters
    
    /** get source address (SA)*/
    inline unsigned char sa() {return _translation.iso.sa;}
    /** set source address (SA)*/ 
    inline void set_sa(unsigned char x) {_translation.iso.sa=x;}
    /** get PDU specific (PS) byte */ 
    inline unsigned char ps() {return _translation.iso.ps;}
    /** set PDU specific (PS) byte */ 
    inline void set_ps(unsigned char x) {_translation.iso.ps=x;}
    /** get PDU format (PF) byte */ 
    inline unsigned char pf() {return _translation.iso.pf;}
    /** set PDU format (PF) byte */ 
    inline void set_pf(unsigned char x) {_translation.iso.pf=x;}    
    /** get data page (DP) bit */ 
    inline unsigned char dp() {return _translation.iso.dp;}
    /** set data page (DP) bit */
    inline void set_dp(unsigned char x) {_translation.iso.dp=x;}
    /** get reserved (R) bit */ 
    inline unsigned char r() {return _translation.iso.r;}
    /** set reserved (R) bit, should be 0*/ 
    inline void set_r(unsigned char x) {
      //MBED_ASSERT(x==0);
      _translation.iso.r=x;}
    /** set priority (P) bits */
    inline unsigned char p() {return _translation.iso.p;}
    /** get priority (P) bits */
    inline void set_p(unsigned char x) {_translation.iso.p=x;}
    /** get CAN 32(29) bit id */ 
    inline unsigned int id() {return _translation.id};
    /** set CAN 32(29) bit id */
    inline void set_id(unsigned int x) {_translation.id=x}; 

    /** @brief returns parameter group number 
	PGN is formed from reserved bit, data page bit, PDU format 
	field (8 bits) and, optionally, PDU specific group extension
	(for PF>=240). See ISO 11783-3 p2. Fancier getter needed
	because of behavior depending on if PF<240 or not. 
     */
    unsigned int pgn();

    /** @brief sets parameter group number. 
	Gives warning if a badly formed PGN is specified, e.g.
	with PF<240 but with a non-zero PS. See ISO 11783-3 p2. 
	Fancier setter needed because of behavior if PF<240 or not. 
     */
    void set_pgn(unsigned int x);

    /** @brief returns destination address
	If PF>240, returns NMEA2K_BROADCAST (255). 
	Fancier getter because of behavior if PF<240 or not. 
	See ISO 11783-3 p2. 
     */
    unsigned char da();

    /** @brief sets destination address
	Gives warning if a non broadcast address is specified for
	PF>=240. Fancier setter because of behavior if PF<240 or not. 
	See ISO 11783-3 p2. 
     */
    void set_da(unsigned char x);

  private:
    /** @brief Handy translation table between ISO 11783 and CAN ID
	Uses bit fields and a union... may be buggy when ported to 
	other processors (e.g. watch this when going from LPC1768 to 
	Nucleo L432KC! The ISO fields are listed LSB to MSB to work
	correctly on LPC1768.)
     */
    union {
      unsigned int id; //<! CAN extended 32(29) bit address ID
      struct { 
	unsigned int sa : 8, //<! source address
	  ps : 8, //<! PDU specific e.g. dest addr, grp ext, proprietary
	  pf : 8, //<! PDU format
	  dp : 1, //<! data page
	  r : 1, //<! reserved (= 0) by ISO 11783-3
	  p : 3, //<! priority, used by CAN hardware layer
	  ignore : 3; //<! ignore first three bits, named so they can be zeroed
      } iso; //!< equivalent ISO 11783-3 header fields
    } _translation;
  }
  
} // namespace nmea2k 

#endif
