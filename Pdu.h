/** @file Pdu.h
    @brief Protocol Data Unit header file for nmea2k library
    Dennis Evangelista, 2019
*/
#ifndef PDU_H
#define PDU_H

#include "Frame.h"
#include "PduHeader.h"

namespace nmea2k{

  /** @brief Protocol Data Unit (PDU) 
      nmea2k::Pdu contains a Protocol Data Unit, which is a single Frame
      with ISO11783-3 header information (priority, data page, PDU format, 
      PDU specific, and source address). A Pdu has a PGN, and may have a 
      destination address; these are used to route the Pdu to the correct 
      place during processing. 

      In addition to the members immediately visible, Pdu inherits
      a few from mbed::CANMessage via nmea2k::Frame that are important to
      note:

      unsigned int id; // which we should NOT use, but can't hide it
      unsigned char len; // which is OK to access directly
      unsigned char data[8] // which is OK to access directly

      Instead of directly accessing id, please use the get_id() and set_id()
      accessors so that the corresponding ISO11783-3 header data is 
      properly handled. 
  */
  class Pdu:public Frame{
  public:
    /** Creates empty PDU */
    Pdu();

    /** Creates Pdu with specific data
	@param id, message id (for CAN purposes)
	@param data, message data
	@param len, message length
    */
    Pdu(unsigned int id, const unsigned char *data, unsigned char len=8);

    /** Creates Pdu with specific data
	@param id, message id (for CAN purposes)
	@param data, message data
	@param len, message length
    */ 
    Pdu(unsigned int id, const char *data, unsigned char len=8);

    /** Creates Pdu with specific data using header
	@param h, PduHeader for message
	@param data, message data
	@param len, message length 
    */
    Pdu(PduHeader h, const unsigned char *data, unsigned char len=8);

    /** Creates Pdu with specific data using header
	@param h, PduHeader for message
	@param data, message data
	@param len, message length
    */
    Pdu(PduHeader h, const char *data, unsigned char len=8); 

    /** Destructor for Pdu class */
    //~Pdu();
    // Commenting out destructor - this is a trivial destructor,
    // by rule of 3 would also need copy constructor and operator. 



    // Setters and getters for members
    
    /** @brief Set id
	@param x, desired id
	@returns 
	  MBED_SUCCESS if successful
	  negative error code if not, and may throw warnings
	Fancy setter needed in case id results in a funny bad message
	and to also set id for mbed::CANMessage inherited via nmea2k::Frame 
    */
    int set_id(unsigned int x);
    
    /** Returns id */ 
    inline unsigned int get_id(){return _header.get_id();}

    /** @brief Set header
	@param h, desired PduHeader for Pdu
	@returns
	  MBED_SUCCESS if it worked
	  negative error code if it failed
	Fancy setter needed to also set corresponding id for
	mbed::CANMessage inherited via nmea2k::Frame. 

	Not sure if we need this, provided for convenience of setting
	whole header at once as might be needed in a node that always 
	sends one particular pgn. 
    */
    int set_header(PduHeader h); 
   
    /** Set priority, P */ 
    inline void set_p(unsigned char x){
      _header.set_p(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } // void set_p(x)
    
    /** Get priority, P */ 
    inline unsigned char p(){return _header.p();}
    
    /** Set reserved, R */
    inline void set_r(unsigned char x){
      MBED_ASSERT(x==0); 
      _header.set_r(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } // void set_r(x)

    /** Get reserved, R*/
    inline unsigned char r(){return _header.r();}
    
    /** Set data page, DP */
    inline void set_dp(unsigned char x){
      _header.set_dp(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } // void set_dp(x)
    
    /** Get data page, DP*/ 
    inline unsigned char dp(){return _header.dp();}
    
    /** Set PDU format, PF*/ 
    inline void set_pf(unsigned char x){
      _header.set_pf(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } //void set_pf(x)
    
    /** Get PDU format, PF*/
    inline unsigned char pf(){return _header.pf();}
    
    /** Set PDU specific, PS*/ 
    inline void set_ps(unsigned char x){
      _header.set_ps(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } // void set_ps(x)
    
    /** Get PDU specific, PS*/ 
    inline unsigned char ps(){return _header.ps();}
    
    /** Set source address, SA*/ 
    inline void set_sa(unsigned char x){
      _header.set_sa(x);
      Frame::set_id(_header.get_id()); // also set super (Frame, CANMessage) id
    } // void set_sa(x)
    
    /** Get source address, SA*/ 
    inline unsigned char sa(){ return _header.sa();}
    
    /** Get parameter group number, PGN*/
    inline unsigned int pgn(){return _header.pgn();}
    
    /** @brief Set parameter group number, PGN
	@param x, desired PGN
	@returns
	  MBED_SUCCESS if it worked
	  negative error code if it didnae and may throw warnings
	Fancy setter needed to also set id inherited from mbed::CANMessage
	via nmea2k::Frame
     */
    int set_pgn(unsigned int x);
    
    /** Get destination address, DA*/
    inline unsigned char da(){return _header.da();}
    
    /** @brief Set destination address, DA
	@param x, desired destination address
	@returns
	  MBED_SUCCESS if it worked
	  negative error code if it didn't, and may throw warnings
	Fancy setter needed to also set id inherited from mbed::CANMessage
	via nmea2k::Frame. 
     */
    int set_da(unsigned char x);

  private:
    PduHeader _header; //<! used to translate CAN id <-> PGN etc. 
  }; // class Pdu

} // namespace nmea2k

#endif
