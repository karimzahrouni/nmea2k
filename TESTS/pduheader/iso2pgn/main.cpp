/** 
    TESTS/pduheader/iso2pgn/main.cpp
    Test of ISO11783 to PGN encoding for PDU header in nmea2k
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
  pc.printf("\r\nPduHeader ISO11783-3 to PGN test\r\n");

  // test cases from page 5 of ISO 11783-3
  pc.printf("testing PGN 0... \r\n");
  foo.set_pgn(0);
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pgn(),"failed to decode PGN");

  

} // int main(void)

