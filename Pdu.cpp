/** @file Pdu.cpp
    @brief Pdu implementation file
    Dennis Evangelista, 2019
*/

#include "Pdu.h"
#include "mbed.h"

namespace nmea2k{

  Pdu::Pdu() :
    Frame(),_header(){
    debug("Pdu() constructor called %p\r\n",this);
  } // Pdu() constructor

  Pdu::Pdu(unsigned int id, const unsigned char *data, unsigned char len) :
    Frame(id,data,len),_header(id){
    debug("Pdu(id,data,len) constructor called with unsigned char data %p\r\n",this);
  } // Pdu(id,data,len) constructor with unsigned char data

  Pdu::Pdu(unsigned int id, const char *data, unsigned char len) :
    Frame(id,data,len),_header(id){
    debug("Pdu(id,data,len) constructor called with char data %p\r\n",this);
  } // Pdu(id,data,len) constructor with char data

  Pdu::Pdu(PduHeader h, const unsigned char *data, unsigned char len) :
    Frame(h.get_id(),data,len),_header(h){
    debug("Pdu(h,data,len) constructor called with unsigned char data %p\r\n",this);
    //Pdu::_header = h;
  } // Pdu(h,data,len) constructor with unsigned char data

  Pdu::Pdu(PduHeader h, const char *data, unsigned char len) :
    Frame(h.get_id(),data,len),_header(h){
    debug("Pdu(h,data,len) constructor called with char data %p\r\n",this);
    //Pdu::_header=h;
  } // Pdu(h,data,len) constructor with char data 

  /* Commenting out destructor - rule of 3 would also need copy constructor
     and operator, but this is just a trivial destructor... 
  Pdu::~Pdu(){
    debug("~Pdu() destructor called %p\r\n",this);
  }
  */

  int Pdu::set_id(unsigned int x){
    int result = Pdu::_header.set_id(x);
    if (result == MBED_SUCCESS) // id is valid 
      Frame::set_id(x); // also set super (Frame, CANMessage) id
    return result;
  } // int set_id(x)

  int Pdu::set_header(PduHeader h){
    int result = Frame::set_id(h.get_id());
    if (result == MBED_SUCCESS) // id is valid
      Pdu::_header = h; // also set contained header
    return result; 
  } //int set_header(h)

  int Pdu::set_pgn(unsigned int x){
    int result = Pdu::_header.set_pgn(x);
    if (result == MBED_SUCCESS) // pgn is valid
      Frame::set_id(Pdu::_header.get_id());
      // also set super (Frame, CANMessage) id
    return result;
    } // int set_pgn(x)

  int Pdu::set_da(unsigned char x){
    int result = Pdu::_header.set_da(x); 
    if (result == MBED_SUCCESS) // da is valid
      Frame::set_id(Pdu::_header.get_id());
      // also set super (Frame, CANMessage) id
    return result;
  } // int set_da(x)
    
} // namespace nmea2k
