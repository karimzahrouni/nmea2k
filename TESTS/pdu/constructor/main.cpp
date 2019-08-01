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
  pc.printf("\r\nnmea2k::Pdu() constructor tests\r\n");

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


  
  pc.printf("Pdu(id,data,len) with unsigned char data\r\n");
  unsigned char counter=0; 
  foo = nmea2k::Pdu(0x01ef00ff,&counter,1);
  TEST_ASSERT_EQUAL_MESSAGE(0x01ef00ff,foo.get_id(),"bad id"); 
    pc.printf("inherited from CANMessage via Frame:\r\n"); 
  pc.printf("  id = %d\r\n",foo.get_id());
  for (int i=0; i<8; i++)
    pc.printf("  data[%d] = %d\r\n",i,foo.data[i]);
  pc.printf("  len = %d\r\n",foo.len);
  pc.printf("  type = %d, %d = CANData\r\n",foo.type,CANData);
  pc.printf("  format = %d, %d = CANExtended\r\n",foo.format,CANExtended);
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.data[0],"bad data");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.len,"bad length");
  TEST_ASSERT_EQUAL_MESSAGE(CANData,foo.type,"bad Frame type");
  TEST_ASSERT_EQUAL_MESSAGE(CANExtended,foo.format,"bad Frame format");
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
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.header.p(),"bad priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.header.r(),"bad reserved");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.header.dp(),"bad data page");
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.header.pf(),"bad PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.header.ps(),"bad PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.header.sa(),"bad source address");
  TEST_ASSERT_EQUAL_MESSAGE(126720,foo.header.pgn(),"bad pgn");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.header.da(),"bad da"); 

  
} // int main(void) 
