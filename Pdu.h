/** @file Pdu.h
    @brief Protocol Data Unit header file for nmea2k library

    Dennis Evangelista, 2019

    TODO Make header private and provide accessors and a setter that
    takes a pointer to a PduHeader. 
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
  */
  class Pdu:public Frame{
  public:
    PduHeader header; //<! used to translate CAN id <-> PGN etc. 

    /** Creates empty PDU */
    Pdu();

    Pdu(unsigned int id, const unsigned char *data, unsigned char len=8);
    Pdu(unsigned int id, const char *data, unsigned char len=8); 
    Pdu(PduHeader h, const unsigned char *data, unsigned char len=8);
    Pdu(PduHeader h, const char *data, unsigned char len=8); 

    /** Destructor for Pdu class */
    ~Pdu();

    unsigned int get_id();
    int set_id(unsigned int x);
    int set_header(PduHeader h); 

    // members inherited from CANMessage via Frame are
    // unsigned int id; // which we should NOT use, but can't hide it
    // unsigned char len; // which is OK to access
    // unsigned char data[8] // which is OK to access
  }; // class Pdu

} // namespace nmea2k

#endif
