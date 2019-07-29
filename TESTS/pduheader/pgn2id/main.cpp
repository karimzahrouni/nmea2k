/** 
    TESTS/pduheader/pgn2id/main.cpp
    Test of PGN to CAN ID encoding for PDU header in nmea2k
    Dennis Evangelista, 2019

    This test checks that PduHeader is correctly
    translating between 32(29) bit CAN id and 
    the various ISO11783-3 bit fields. 

    Test cases are drawn from p5 of ISO 11783-3:1998(E) 
    Tractors and machinery for agriculture and forestry --
    serial control and communications data network -- part 3:
    data link layer.
 */

#include "mbed.h"
#include "stdio.h"
#include "unity.h"
#include "nmea2k.h"

Serial pc(USBTX,USBRX);
nmea2k::PduHeader foo; 

int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nPduHeader PGN to ISO11783-3 test\r\n");

  foo.set_id(0);
  foo.set_pgn(127245);
  TEST_ASSERT_EQUAL_MESSAGE(0x01f10d00,foo.id(),"failed to decode id");
  
} // int main(void)

