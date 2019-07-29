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
  pc.printf("testing PGN 0\r\n");
  foo.set_id(0);
  foo.set_pgn(0);
  TEST_ASSERT_EQUAL(0,foo.p());
  TEST_ASSERT_EQUAL(0,foo.dp());
  TEST_ASSERT_EQUAL(0,foo.pf());
  TEST_ASSERT_EQUAL(0,foo.ps());
  TEST_ASSERT_EQUAL(0,foo.sa());

  /**  pc.printf("testing PGN 60928\r\n");
  foo.set_pgn(60928);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(238,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 61184\r\n");
  foo.set_pgn(61184);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(239,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 61440\r\n");
  foo.set_pgn(61440);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(240,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65279\r\n");
  foo.set_pgn(65279);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(254,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65280\r\n");
  foo.set_pgn(65280);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65535\r\n");
  foo.set_pgn(65535);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65536\r\n");
  foo.set_pgn(65536);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(0,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 126720\r\n");
  foo.set_pgn(126720);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(239,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 126976\r\n");
  foo.set_pgn(126976);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(240,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 131071\r\n");
  foo.set_pgn(131071);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing in hex\r\n");
  pc.printf("testing PGN 0\r\n");
  foo.id = 0;
  foo.set_pgn(0x0);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(0,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 60928\r\n");
  foo.set_pgn(0x00ee00);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(238,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 61184\r\n");
  foo.set_pgn(0x00ef00);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(239,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 61440\r\n");
  foo.set_pgn(0x00f000);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(240,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65279\r\n");
  foo.set_pgn(0x00feff);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(254,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65280\r\n");
  foo.set_pgn(0x00ff00);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65535\r\n");
  foo.set_pgn(0x00ffff);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(0,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 65536\r\n");
  foo.set_pgn(0x010000);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(0,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 126720\r\n");
  foo.set_pgn(0x01ef00);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(239,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 126976\r\n");
  foo.set_pgn(0x01f000);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(240,foo.iso.pf);
  TEST_ASSERT_EQUAL(0,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);

  pc.printf("testing PGN 131071\r\n");
  foo.set_pgn(0x01ffff);
  TEST_ASSERT_EQUAL(0,foo.iso.ignore);
  TEST_ASSERT_EQUAL(0,foo.iso.p);
  TEST_ASSERT_EQUAL(1,foo.iso.dp);
  TEST_ASSERT_EQUAL(255,foo.iso.pf);
  TEST_ASSERT_EQUAL(255,foo.iso.ps);
  TEST_ASSERT_EQUAL(0,foo.iso.sa);*/
} // int main(void)

