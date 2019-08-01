/** @file TESTS/pduheader/iso2pgn/main.cpp
    @brief Test of ISO11783 to PGN encoding for PDU header in nmea2k
    Dennis Evangelista, 2019

    This test checks that PduHeader is correctly
    translating between 32(29) bit CAN id and 
    the various ISO11783-3 bit fields. 

    Test cases are drawn from p5 of ISO 11783-3:1998(E) 
    Tractors and machinery for agriculture and forestry --
    serial control and communications data network -- part 3:
    data link layer.
 */

#include "PduHeader.h"

#include "mbed.h"
#include "stdio.h"
#include "unity.h"
//#include "nmea2k.h"

Serial pc(USBTX,USBRX);
nmea2k::PduHeader foo;

int main(void){
  int retval;
  
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nPduHeader ISO11783-3 to PGN test\r\n");

  // test cases from page 5 of ISO 11783-3
  pc.printf("testing PGN 0... \r\n");
  retval=foo.set_id(0);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  foo.set_p(0);
  foo.set_dp(0);
  foo.set_pf(0);
  foo.set_ps(0);
  foo.set_da(0);
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 60928... \r\n");
  foo.set_pf(238);
  TEST_ASSERT_EQUAL_MESSAGE(238,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(60928,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 61184... \r\n");
  foo.set_pf(239);
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(61184,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 61440... \r\n");
  foo.set_pf(240);
  TEST_ASSERT_EQUAL_MESSAGE(240,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(61440,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65279... \r\n");
  foo.set_pf(254);
  foo.set_ps(255); 
  TEST_ASSERT_EQUAL_MESSAGE(254,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65279,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65280... \r\n");
  foo.set_pf(255);
  foo.set_ps(0);
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65280,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65535... \r\n");
  foo.set_ps(255); 
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65535,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65536... \r\n");
  foo.set_p(1);
  foo.set_pf(0);
  foo.set_ps(0); 
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65536,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 126720... \r\n");
  foo.set_pf(239); 
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(126720,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 126976... \r\n");
  foo.set_pf(240);
  TEST_ASSERT_EQUAL_MESSAGE(240,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(126976,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 131071... \r\n");
  foo.set_pf(255);
  foo.set_ps(255); 
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(131071,foo.pgn(),"failed to decode PGN");
  
} // int main(void)

