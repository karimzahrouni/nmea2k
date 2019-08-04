/** @file TESTS/pgn/constructor/main.cpp
    @brief Test generic Pgn constructor
    Dennis Evangelista, 2019
*/

#include "Pgn.h"
#include "mbed.h"
#include "stdio.h"
#include "unity.h"

Serial pc(USBTX,USBRX);

nmea2k::Pgn p;
unsigned char d[8];
unsigned char l; 

int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nnmea2k::Pgn() constructor test\r\n");
  
  pc.printf("Default constructor\r\n");
  p = nmea2k::Pgn();
  pc.printf("p.len = %d\r\n",p.len);
  TEST_ASSERT_EQUAL_MESSAGE(NMEA2K_SINGLE_FRAME_MAX_LEN,
			    p.len,"incorrect length");
  p.get_data(d,&l);
  for (int i=0; i<l; i++)
    pc.printf("p.data[%d] = %d\r\n",i,d[i]);
  
  // can't do much else 
}
