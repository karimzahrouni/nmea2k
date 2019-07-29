/** 
    TESTS/pduheader/pgn2iso/main.cpp
    Test of PGN to ISO11783 encoding for PDU header in nmea2k
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

  // test cases from page 5 of ISO 11783-3
  pc.printf("testing PGN 0... ");
  foo.set_id(0);
  TEST_ASSERT_EQUAL(0,foo.id())
  foo.set_pgn(0);
  TEST_ASSERT_EQUAL(0,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore())
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(0,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");

  pc.printf("testing PGN 60928... ");
  foo.set_pgn(60928);
  TEST_ASSERT_EQUAL(60928,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(238,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");

  pc.printf("testing PGN 61184... ");
  foo.set_pgn(61184);
  TEST_ASSERT_EQUAL(61184,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(239,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 61440... ");
  foo.set_pgn(61440);
  TEST_ASSERT_EQUAL(61440,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(240,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 65279... ");
  foo.set_pgn(65279);
  TEST_ASSERT_EQUAL(65279,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(254,foo.pf());
  TEST_ASSERT_EQUAL(255,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 65280... ");
  foo.set_pgn(65280);
  TEST_ASSERT_EQUAL(65280,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(255,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 65535... ");
  foo.set_pgn(65535);
  TEST_ASSERT_EQUAL(65535,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(255,foo.pf());
  TEST_ASSERT_EQUAL(255,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 65536... ");
  foo.set_pgn(65536);
  TEST_ASSERT_EQUAL(65536,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(1,foo.dp());
  TEST_ASSERT_EQUAL(0,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 126720... ");
  foo.set_pgn(126720);
  TEST_ASSERT_EQUAL(126720,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(1,foo.dp());
  TEST_ASSERT_EQUAL(239,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 126976... ");
  foo.set_pgn(126976);
  TEST_ASSERT_EQUAL(126976,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(1,foo.dp());
  TEST_ASSERT_EQUAL(240,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  pc.printf("testing PGN 131071... ");
  foo.set_pgn(131071);
  TEST_ASSERT_EQUAL(131071,foo.pgn())
  TEST_ASSERT_EQUAL(0,foo.ignore());
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(1,foo.dp());
  TEST_ASSERT_EQUAL(255,foo.pf());
  TEST_ASSERT_EQUAL(255,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());
  pc.printf("passed!\r\n");
  
  //pc.printf("testing in hex\r\n");
} // int main(void)

