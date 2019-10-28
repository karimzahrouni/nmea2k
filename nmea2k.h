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
#define NMEA2K_VERSION "14.3.0 PT1"

#include "Frame.h"
#include "CANLayer.h"
#include "PduHeader.h"
#include "PgnData.h"

namespace nmea2k{
} // namespace nmea2k

#endif

