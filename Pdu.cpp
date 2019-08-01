#include "Pdu.h"

#include "mbed.h"
//#include "nmea2k.h"
//#include "Frame.h"
//#include "PduHeader.h"


namespace nmea2k{

  Pdu::Pdu() :
    Frame(){
    debug("Pdu() constructor called %p\r\n",this);
    Pdu::header = PduHeader(); 
  }

  Pdu::Pdu(unsigned int id, const unsigned char *data, unsigned char len) :
    Frame(id,data,len){
    debug("Pdu(id,data,len) constructor called with unsigned char data %p\r\n",this);
    Pdu::header = PduHeader(id); 
  }

  Pdu::Pdu(unsigned int id, const char *data, unsigned char len) :
    Frame(id,data,len){
    debug("Pdu(id,data,len) constructor called with char data %p\r\n",this);
    Pdu::header = PduHeader(id);
  }

  Pdu::Pdu(PduHeader h, const unsigned char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    debug("Pdu(h,data,len) constructor called with unsigned char data %p\r\n",this);
    Pdu::header = h;
  }

  Pdu::Pdu(PduHeader h, const char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    debug("Pdu(h,data,len) constructor called with char data %p\r\n",this);
    Pdu::header=h;
  }

  Pdu::~Pdu(){
    debug("~Pdu() destructor called %p\r\n",this);
  }

  unsigned int Pdu::get_id(){
    return Pdu::header.get_id();
  }

  int Pdu::set_id(unsigned int x){
    int result = Pdu::header.set_id(x);
    if (result == MBED_SUCCESS)
      Frame::set_id(x); 
    return result;
  }

  int Pdu::set_header(PduHeader h){
    int result = Frame::set_id(h.get_id());
    if (result == MBED_SUCCESS)
      Pdu::header = h;
    return result; 
  }
    
} // namespace nmea2k
