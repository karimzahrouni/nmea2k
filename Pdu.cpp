#include "mbed.h"
#include "nmea2k.h"
#include "Frame.h"
#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{

  Pdu::Pdu() :
    Frame(){
    debug("Pdu() constructor called\r\n");
    header = PduHeader(); 
  }

  Pdu::Pdu(unsigned int id, const unsigned char *data, unsigned char len) :
    Frame(id,data,len){
    debug("Pdu(id,data,len) constructor called with unsigned char data\r\n");
    header = PduHeader(id,data,len); 
  }

  Pdu::Pdu(unsigned int id, const char *data, unsigned char len) :
    Frame(id,data,len){
    debug("Pdu(id,data,len) constructor called with char data\r\n");
    header = PduHeader(id,data,len);
  }

  Pdu::Pdu(PduHeader h, const unsigned char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    debug("Pdu(h,data,len) constructor called with unsigned char data\r\n");
    header = h;
  }

  Pdu::Pdu(PduHeader h, const char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    debug("Pdu(h,data,len) constructor called with char data\r\n");
    header=h;
  }

  Pdu::~Pdu(){
    debug("~Pdu() destructor called\r\n");
  }

  unsigned int Pdu::get_id(){
    return header.get_id();
  }

  int set_id(unsigned int x){
    int result = header.set_id(x);
    if (result == MBED_SUCCESS)
      Frame::set_id(x); 
    return result;
  }

  int set_header(PduHeader h){
    int result = Frame::set_id(h.get_id());
    if (result == MBED_SUCCESS)
      header = h;
    return result; 
  }
    
} // namespace nmea2k
