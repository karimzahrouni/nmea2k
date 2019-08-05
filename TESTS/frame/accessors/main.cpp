/** @file TESTS/frame/accessors/main.cpp
    @brief Test of nmea2k::Frame() 
    Dennis Evangelista, 2019
*/

#include "Frame.h"
#include "mbed.h"
#include "stdio.h"
#include "unity.h"

Serial pc(USBTX,USBRX); 
nmea2k::Frame f; 

int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nTest of nmea2k::Frame() accessors\r\n");
  pc.printf("f.id = %08x should be rando junk\r\n",f.id);
  for (int i=0; i<f.len; i++)
    pc.printf("f.data[i] = %02x should be rando junk\r\n",f.data[i]);
  pc.printf("f.len = %d should be 8\r\n",f.len);
  
  pc.printf("Testing access to public members\r\n");

  pc.printf("Setting id=0x000000ff\r\n");
  f.id = 0x000000ff; 
  TEST_ASSERT_EQUAL_MESSAGE(0x000000ff,f.id,"failed to set id");

  pc.printf("Setting data[0]=0x41\r\n");
  f.data[0] = 0x41;
  TEST_ASSERT_EQUAL_MESSAGE(0x41,f.data[0],"failed to set data[0]");

  pc.printf("Setting len=7\r\n");
  f.len = 7;
  TEST_ASSERT_EQUAL_MESSAGE(7,f.len,"failed to set length");
  
} // int main(void)
