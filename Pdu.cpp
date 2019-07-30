#include "mbed.h"
#include "nmea2k.h"
#include "Frame.h"
#include "PduHeader.h"
#include "Pdu.h"

namespace nmea2k{

  Pdu::Pdu() :
    Frame(){
    header = PduHeader(); 
  }

  Pdu::Pdu(unsigned int id, const unsigned char *data, unsigned char len) :
    Frame(id,data,len){
    header = PduHeader(id,data,len); 
  }

  Pdu::Pdu(unsigned int id, const char *data, unsigned char len) :
    Frame(id,data,len){
    header = PduHeader(id,data,len);
  }

  Pdu::Pdu(PduHeader h, const unsigned char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    header = h;
  }

  Pdu::Pdu(PduHeader h, const char *data, unsigned char len) :
    Frame(h.get_id(),data,len){
    header=h;
  }

  Pdu::~Pdu(){
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
