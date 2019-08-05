/** @file PduHeader.cpp
    @brief Implementation file for PduHeader objects

    Implementation file for PduHeader objects
    Dennis Evangelista, 2019
*/

#include "PduHeader.h"
#include "mbed_debug.h"
#include "mbed_error.h"


namespace nmea2k {

  PduHeader::PduHeader(){
    //debug("PduHeader() empty constructor called %p\r\n",this);
    _translation.id = 0; 	
  }

  PduHeader::PduHeader(unsigned int id){
    //debug("PduHeader(id) called %p\r\n",this);
    _translation.id = id;
  }

  PduHeader::PduHeader(unsigned char priority,
		       unsigned int pgn,
		       unsigned char sa,
		       unsigned char da){
    //debug("PduHeader(priority,pgn,sa,da) called %p\r\n",this);
    _translation.iso.ignore = 0;
    _translation.iso.p = priority & (0x7);
    set_pgn(pgn);
    set_da(da); 
    _translation.iso.sa = sa;    
  }

  /*
  PduHeader::~PduHeader(){
    debug("~PduHeader() destructor called %p\r\n",this);
  }
  */

  unsigned int PduHeader::pgn(){
    /* From ISO11783-3 page 2, the procedure for the bit fields 
       to be converted to Parameter Group Numbers is as follows: 
       if the PDU Format value is less than 240, then the lower byte 
       of the PGN is set to 0. 
    */
    unsigned int result = (_translation.iso.r << 17); 
    //MBED_ASSERT(result==0); // r should always be 0
    result += (_translation.iso.dp << 16);
    result += (_translation.iso.pf << 8); 
    if (_translation.iso.pf>=240)
      result += _translation.iso.ps;
    return result;
  } // pgn() getter
    
  int PduHeader::set_pgn(unsigned int x){
    unsigned char b1,b2,b3;
    b1 = (x>>16) & 0x03;
    b2 = (x>>8) & 0xff;
    b3 = (x & 0xff);
      
    if ((b2<240) && (b3!=0)){
      debug("warning: badly formed PGN %d, PF<240 but PS set, no puedo\r\n",x);
      MBED_WARNING1( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				     MBED_ERROR_CODE_UNSUPPORTED),
		     "badly formed PGN, PF<240 but PS set, no puedo",
		     x);
      return MBED_ERROR_CODE_INVALID_ARGUMENT;
    } // if badly formed PGN throw warning
    else if (b1>>1){
      debug("warning: badly formed PGN %d, wants to set R=1, no puedo\r\n",x);
      MBED_WARNING1( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				     MBED_ERROR_CODE_UNSUPPORTED),
		     "badly formed PGN, setting R=1, no puedo",
		     x);
      return MBED_ERROR_CODE_INVALID_ARGUMENT;
    }
    else {
      _translation.iso.r = b1>>1; 
      //MBED_ASSERT(_translation.iso.r==0); // r should always be 0
      _translation.iso.dp = b1 & 0x01;
      _translation.iso.pf = b2;
      _translation.iso.ps = b3;
      return MBED_SUCCESS;
    } // else
  } // set_pgn() setter

  int PduHeader::set_id(unsigned int x){
    unsigned char r;
    r = (x>>25)&0x1;
    // Note we don't need to check (PF<240) and PS==0 because
    // it could be encoding a destination address. 
    if (r){
      debug("warning: badly formed id %x, wants to set R=1, no puedo\r\n",x);
      MBED_WARNING1( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				     MBED_ERROR_CODE_UNSUPPORTED),
		     "badly formed id, setting R=1, no puedo",
		     x);
      return MBED_ERROR_CODE_INVALID_ARGUMENT;
    }
    else {
      _translation.id = x; 
      return MBED_SUCCESS;
    } // else
  } // set_id
  
  unsigned char PduHeader::da(){
    if (_translation.iso.pf<240)
      return _translation.iso.ps;
    else
      return NMEA2K_BROADCAST;
  } // da() getter
      
  int PduHeader::set_da(unsigned char x){
    if (_translation.iso.pf<240){
      _translation.iso.ps = x;
      return MBED_SUCCESS;
    } // if pf<240
    else if (x != NMEA2K_BROADCAST) {
      debug("warning: trying to set DA %x for PGN w none, no puedo\r\n",x);
      MBED_WARNING1 ( MBED_MAKE_ERROR(MBED_MODULE_DRIVER,
				      MBED_ERROR_CODE_UNSUPPORTED),
		      "trying to set DA for PGN w none, no puedo",
		      x);
      return MBED_ERROR_CODE_INVALID_ARGUMENT;
    } // if setting DA for PGN w none, throw warning
    else return MBED_SUCCESS; // ok to set DA=255 for pg>=240
  } // set_da() setter

  
} // namespace nmea2k 
