/** @file nmea2k_constants.h
    @brief nmea2k library for CAN-based navigational network "nmea2k-like"
    Dennis Evangelista, 2019
*/

#ifndef NMEA2K_CONSTANTS_H
#define NMEA2K_CONSTANTS_H

/** @def NMEA2K_VERSION
    @brief nmea2k version for Sailbot Hull 14 mod 3 */
/** @def NMEA2K_FREQUENCY
    @brief CAN bus frequency for nmea2k is 250000 Hz */
/** @def NMEA2K_BROADCAST
    @brief address used for broadcast messages is 255 (0xff) */
#define NMEA2K_VERSION "14.3.0"
#define NMEA2K_FREQUENCY 250000
#define NMEA2K_BROADCAST 255 

#endif
