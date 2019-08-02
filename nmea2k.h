/** @file nmea2k.h
    @brief nmea2k library for CAN-based navigational network like "nmea2k"

    nmea2k.h header file
    CAN-based navigational network like "nmea2k" for USNA Sailbot use
    Dennis Evangelista, 2019
*/


#ifndef NMEA2K_H
#define NMEA2K_H

/** @def NMEA2K_VERSION
    @brief nmea2k version for Sailbot Hull 14 mod 3 */
/** @def NMEA2K_FREQUENCY
    @brief CAN bus frequency for nmea2k is 250000 Hz */
/** @def NMEA2K_BROADCAST
    @brief address used for broadcast messages is 255 (0xff) */
#define NMEA2K_VERSION "14.3.0"
#define NMEA2K_FREQUENCY 250000
#define NMEA2K_BROADCAST 255 

#include "mbed.h"
#include "Frame.h"
#include "PduHeader.h"
#include "Pdu.h"
#include "Pgn.h"

namespace nmea2k{

  
} // namespace nmea2k

#endif

