/** @file TESTS/pgndata/constructor/main.cpp
    @brief Test generic Pgn constructor
    Dennis Evangelista, 2019
*/

#include "PgnData.h"
#include "mbed.h"
#include "stdio.h"
#include "unity.h"

Serial pc(USBTX,USBRX);

nmea2k::PgnData p;
unsigned char d[8];
unsigned char l; 

int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nnmea2k::PgnData() constructor test\r\n");
  
  pc.printf("Default constructor\r\n");
  p = nmea2k::PgnData();
  pc.printf("p.p = %d\r\n",p.p);
  TEST_ASSERT_EQUAL_MESSAGE(7,p.p,"incorrect priority");
  pc.printf("p.pgn = %d\r\n",p.pgn);
  TEST_ASSERT_EQUAL_MESSAGE(0,p.pgn,"incorrect pgn"); 
  pc.printf("p.name = %s\r\n",p.name); 
  pc.printf("p.dlen = %d\r\n",p.dlen);
  TEST_ASSERT_EQUAL_MESSAGE(8,
			    p.dlen,"incorrect length");

  pc.printf("Trying to read data from abstract PgnData\r\n");
  pc.printf("Next line should throw an error\r\n"); 
  d = p.data();
}
