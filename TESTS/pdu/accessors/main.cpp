/** @file TESTS/pdu/constructor/main.cpp
    @brief Test of Pdu object constructor flavors

    Dennis Evangelista, 2019
*/

#include "Pdu.h"

#include "mbed.h"
#include "stdio.h"
#include "unity.h"

#include "PduHeader.h"

Serial pc(USBTX,USBRX);
nmea2k::Pdu foo;
nmea2k::PduHeader h; 



int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nnmea2k::Pdu() accessors tests\r\n");

  pc.printf("Empty constructor\r\n");
  foo = nmea2k::Pdu();
  pc.printf("inherited from CANMessage via Frame:\r\n"); 
  pc.printf("  id = %d\r\n",foo.get_id());
  for (int i=0; i<8; i++)
    pc.printf("  data[%d] = %d\r\n",i,foo.data[i]);
  pc.printf("  len = %d\r\n",foo.len);
  pc.printf("  type = %d, %d = CANData\r\n",foo.type,CANData);
  pc.printf("  format = %d, %d = CANExtended\r\n",foo.format,CANExtended);
  pc.printf("contained in PduHeader header:\r\n");
  pc.printf("  p = %d\r\n",foo.header.p());
  pc.printf("  r = %d\r\n",foo.header.r());
  pc.printf("  dp = %d\r\n",foo.header.dp());
  pc.printf("  pf = %d\r\n",foo.header.pf());
  pc.printf("  ps = %d\r\n",foo.header.ps());
  pc.printf("  sa = %d\r\n",foo.header.sa());
  pc.printf("  id = %d, should match\r\n",foo.header.get_id());
  pc.printf("  pgn = %d\r\n",foo.header.pgn());
  pc.printf("  da = %d\r\n",foo.header.da());
  TEST_ASSERT_EQUAL_MESSAGE(CANData,foo.type,"incorrect nmea2k::Frame type");
  TEST_ASSERT_EQUAL_MESSAGE(CANExtended,foo.format,"incorrect nmea2k::Frame format");
  TEST_ASSERT_EQUAL_MESSAGE(foo.get_id(),foo.header.get_id(),"id does not match");

  pc.printf("set_id(), get_id()\r\n");
  foo.set_id(0x01fedcba);
  TEST_ASSERT_EQUAL_MESSAGE(0x01fedcba,foo.get_id(),"failed id via get_id");
  TEST_ASSERT_EQUAL_MESSAGE(0x01fedcba,foo.header.get_id(),"failed id via header");
  TEST_ASSERT_EQUAL_MESSAGE(0x01fedcba,foo.id,"failed id via CANMessage");
  pc.printf("inherited from CANMessage via Frame:\r\n"); 
  pc.printf("  id = %d\r\n",foo.get_id());
  for (int i=0; i<8; i++)
    pc.printf("  data[%d] = %d\r\n",i,foo.data[i]);
  pc.printf("  len = %d\r\n",foo.len);
  pc.printf("  type = %d, %d = CANData\r\n",foo.type,CANData);
  pc.printf("  format = %d, %d = CANExtended\r\n",foo.format,CANExtended);
  pc.printf("contained in PduHeader header:\r\n");
  pc.printf("  p = %d\r\n",foo.header.p());
  pc.printf("  r = %d\r\n",foo.header.r());
  pc.printf("  dp = %d\r\n",foo.header.dp());
  pc.printf("  pf = %d\r\n",foo.header.pf());
  pc.printf("  ps = %d\r\n",foo.header.ps());
  pc.printf("  sa = %d\r\n",foo.header.sa());
  pc.printf("  id = %d, should match\r\n",foo.header.get_id());
  pc.printf("  pgn = %d\r\n",foo.header.pgn());
  pc.printf("  da = %d\r\n",foo.header.da());
  

  
} // int main(void) 
