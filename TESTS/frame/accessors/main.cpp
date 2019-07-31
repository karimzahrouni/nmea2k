/** @file TESTS/frame/accessors/main.cpp
    @brief Test of nmea2k::Frame() getters and setters
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
  
  pc.printf("Testing nmea2k::Frame.set_id() and get_id()\r\n");
  f.set_id(0x000000ff);
  TEST_ASSERT_EQUAL_MESSAGE(0x000000ff,f.get_id(),"failed to set id");
  f.set_id(0x0000ff00);
  TEST_ASSERT_EQUAL_MESSAGE(0x0000ff00,f.get_id(),"failed to set id");
  f.set_id(0x00ffffff);
  TEST_ASSERT_EQUAL_MESSAGE(0x00ffffff,f.get_id(),"failed to set id");
  f.set_id(0x01ffffff);
  TEST_ASSERT_EQUAL_MESSAGE(0x01ffffff,f.get_id(),"failed to set id");
  f.set_id(0x1dffffff);
  TEST_ASSERT_EQUAL_MESSAGE(0x1dffffff,f.get_id(),"failed to set id");

  pc.printf("Setting R to 1, may throw warnings or errors\r\n");
  f.set_id(0x1fffffff);
  TEST_ASSERT_EQUAL_MESSAGE(0x1fffffff,f.get_id(),"failed to set id");

  pc.printf("Setting ignored bits to 1, may throw warnings or errors\r\n");
  f.set_id(0xffffffff);
  TEST_ASSERT_EQUAL_MESSAGE(0xffffffff,f.get_id(),"failed to set id");
} // int main(void)
