/** @file nmea2k.h
    @brief nmea2k library for CAN-based navigational network like "NM2K"

    nmea2k.h header file
    Header file for "NM2K"-like navigational network for USNA Sailbot use
    Dennis Evangelista, 2019
*/

#ifndef NMEA2K_H
#define NMEA2K_H
#define NMEA2K_VERSION "14.3.0" //!< nmea2k version for Sailbot Hull 14 mod 3
#define NMEA2K_FREQUENCY 250000 //!< CAN bus frequency for NM2K is 250000 Hz
#define NMEA2K_BROADCAST 255

#include "mbed.h"

namespace nmea2k {

class Frame:public CAN::CANMessage {
public:
    Frame();
    Frame(unsigned int _id, const unsigned char * _data, unsigned char _len=8);
    Frame(unsigned int _id, const char * _data, unsigned char _len=8);
    ~Frame();
};

class CanLayer:public CAN::CAN {
public:
    CanLayer(mbed::PinName rd, mbed::PinName td);
    ~CanLayer();
    int write(Frame frame);
    int read(Frame frame, int handle=0);
    void attach(mbed::Callback<void()> func, mbed::IrqType type=CAN::RxIrq);
};















/** Iso11783Header_t is ued for encoding and decoding CAN extended
    32(29) bit id into stuff used by Nmea2k. These are defined here
    from LSB to MSB.
*/
typedef struct Iso11783Header_t {
    unsigned char sa, //<! source address
             ps,     //<! PDU specific e.g. dest addr, grp ext, proprietary
             pf,     //<! PDU format
             dp : 1, //<! data page
             r : 1,  //<! reserved (= 0) by ISO 11783-3
             p : 3,  //<! priority, used only by CAN hardware layer
             ignore: 3;    //<! ignore first three bits, named so they can be set
} Iso11783Header_t; // Iso11783Header_t

/** PduHeader_t is a union for easy translation between CAN 32(29) bit id
    and ISO11783-3 header fields
*/
typedef union PduHeader_t {
    unsigned int id; //!< CAN extended 32(29) bit address id
    Iso11783Header_t iso; //!< equivalent ISO 11783-3 header fields
} PduHeader_t; // PduHeader_t

/** Pdu contains a Protocol Data Unit, which is a single frame that has
    priority, data page, PDU format, PDU specific, and source address.
    A Pdu has a PGN, and may have a destination address; these can be
    found and used in routing the Pdu to the correct place.
 */
class Pdu:public Frame {
public:
    PduHeader_t header; //<! Used to translate CAN id <-> PGN etc.
    unsigned int pgn; //<! need to be able to get this on receipt for dispatch
    unsigned char da; //<! need to get this on receipt to decide if handling
    Pdu();
    Pdu(unsigned int _id, const unsigned char * _data, unsigned char len=8);
    Pdu(unsigned int _id, const char * data, unsigned char len=8);
    Pdu(unsigned char, unsigned char,
        unsigned char, unsigned char, unsigned char,
        const unsigned char *, unsigned char);
    Pdu(unsigned char, unsigned char,
        unsigned char, unsigned char, unsigned char,
        const char *, unsigned char);
    ~Pdu();
};








class Nmea2k {
public:
    Nmea2k();
    ~Nmea2k();

    // send
    // send_fast LATER
    // send_multi LATER

    // attach
    // hook for user context receipt handling

private:
    // _send_queue
    // _send_thread
    // _SendCallback
};


} // namespace nmea2k

#endif // NMEA2K_H


