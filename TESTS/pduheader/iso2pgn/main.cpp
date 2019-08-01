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
  retval = foo.set_pgn(0);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 60928... \r\n");
  retval=foo.set_pgn(60928);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(238,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(60928,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 61184... \r\n");
  retval=foo.set_pgn(61184);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(61184,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 61440... \r\n");
  retval=foo.set_pgn(61440);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(240,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(61440,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65279... \r\n");
  retval=foo.set_pgn(65279);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(254,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65279,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65280... \r\n");
  retval=foo.set_pgn(65280);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65280,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65535... \r\n");
  retval=foo.set_pgn(65535);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65535,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 65536... \r\n");
  retval=foo.set_pgn(65536);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(65536,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 126720... \r\n");
  retval=foo.set_pgn(126720);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(126720,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 126976... \r\n");
  retval=foo.set_pgn(126976);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(240,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(126976,foo.pgn(),"failed to decode PGN");

  pc.printf("testing PGN 131071... \r\n");
  retval=foo.set_pgn(131071);
  TEST_ASSERT_EQUAL_MESSAGE(MBED_SUCCESS,retval,"got odd retval");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ignore(),"failed to decode ignore bits");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed to decode priority");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to decode data page");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"failed to decode PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.ps(),"failed to decode PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(131071,foo.pgn(),"failed to decode PGN");

  pc.printf("testing invalid PGN 0x200ff, should return warnings or errors\r\n");
  retval = foo.set_pgn(0x300ff);
  TEST_ASSERT_MESSAGE(retval!=MBED_SUCCESS,"got unexpected retval 0, should have failed");
  TEST_ASSERT_MESSAGE(foo.pf()!=0x00,"it set PF?");
  TEST_ASSERT_MESSAGE(foo.ps()!=0xff,"it set PS?");
} // int main(void)

