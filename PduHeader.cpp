/** @file PduHeader.cpp
    @brief Implementation file for PduHeader objects

    Implementation file for PduHeader objects
    Dennis Evangelista, 2019
*/

#include "mbed.h"
#include "nmea2k.h"
#include "PduHeader.h"

namespace nmea2k {

  PduHeader::PduHeader(){
  }

  PduHeader::PduHeader(unsigned int _id){
    _translation.id = _id;
    if ((_translation.iso.pf<240) && (_translation.iso.ps!=0))
      MBED_WARNING1( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				     MBED_ERROR_CODE_UNSUPPORTED),
		     "id resulted in possibly badly formed PGN",
		     _id);
  }

  PduHeader::PduHeader(unsigned char priority,
		       unsigned int pgn,
		       unsigned char sa,
		       unsigned char da){
    _translation.iso.ignore = 0;
    _translation.iso.p = priority & (0x7);
    set_pgn(pgn);
    set_da(da); 
    _translation.iso.sa = sa;    
  }

  PduHeader::~PduHeader(){
  }

  unsigned int PduHeader::pgn(){
    /* From ISO11783-3 page 2, the procedure for the bit fields 
       to be converted to Parameter Group Numbers is as follows: 
       if the PDU Format value is less than 240, then the lower byte 
       of the PGN is set to 0. 
    */
    unsigned int result = (_translation.iso.r << 17); 
    MBED_ASSERT(result==0); // r should always be 0
    result += (_translation.iso.dp << 16);
    result += (_translation.iso.pf << 8); 
    if (_translation.iso.pf<240)
      result += _translation.iso.ps;
    return result;
  } // pgn() getter
    
  void PduHeader::set_pgn(unsigned int x){
    unsigned char b1,b2,b3;
    b1 = (x>>16) & 0x03;
    b2 = (x>>8) & 0xff;
    b3 = (x & 0xff);
      
    if ((b2<240) && (b3!=0)){
      MBED_WARNING1( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				     MBED_ERROR_CODE_UNSUPPORTED),
		     "Badly formed PGN, no puedo",
		     x);
    } // if badly formed PGN throw warning
    else {
      _translation.iso.r = b1>>1; 
      //MBED_ASSERT(_translation.iso.r==0); // r should always be 0
      _translation.iso.dp = b1 & 0x01;
      _translation.iso.pf = b2;
      _translation.iso.ps = b3;
    } // else
    return; 
  } // set_pgn() setter
    
  unsigned char PduHeader::da(){
    if (_translation.iso.pf<240)
      return _translation.iso.ps;
    else
      return NMEA2K_BROADCAST;
  } // da() getter
      
  void PduHeader::set_da(unsigned char x){
    if (_translation.iso.pf<240)
      _translation.iso.ps = x;
    else if (x != NMEA2K_BROADCAST) {
      MBED_WARNING1 ( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				      MBED_ERROR_CODE_UNSUPPORTED),
		      "Trying to set DA for PGN w none, no puedo",
		      x);
    } // if setting DA for PGN w none, throw warning
    return; 
  } // set_da() setter

  
} // namespace nmea2k 
