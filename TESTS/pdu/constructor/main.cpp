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
  pc.printf("contained in PduHeader _header:\r\n");
  pc.printf("  p = %d\r\n",foo.p());
  pc.printf("  r = %d\r\n",foo.r());
  pc.printf("  dp = %d\r\n",foo.dp());
  pc.printf("  pf = %d\r\n",foo.pf());
  pc.printf("  ps = %d\r\n",foo.ps());
  pc.printf("  sa = %d\r\n",foo.sa());
  pc.printf("  id = %d, should match\r\n",foo.get_id());
  pc.printf("  pgn = %d\r\n",foo.pgn());
  pc.printf("  da = %d\r\n",foo.da());
  TEST_ASSERT_EQUAL_MESSAGE(CANData,foo.type,"incorrect nmea2k::Frame type");
  TEST_ASSERT_EQUAL_MESSAGE(CANExtended,foo.format,"incorrect nmea2k::Frame format");



  
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
  pc.printf("contained in PduHeader _header:\r\n");
  pc.printf("  p = %d\r\n",foo.p());
  pc.printf("  r = %d\r\n",foo.r());
  pc.printf("  dp = %d\r\n",foo.dp());
  pc.printf("  pf = %d\r\n",foo.pf());
  pc.printf("  ps = %d\r\n",foo.ps());
  pc.printf("  sa = %d\r\n",foo.sa());
  pc.printf("  id = %d, should match\r\n",foo.get_id());
  pc.printf("  pgn = %d\r\n",foo.pgn());
  pc.printf("  da = %d\r\n",foo.da());
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"bad priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.r(),"bad reserved");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"bad data page");
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"bad PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.ps(),"bad PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.sa(),"bad source address");
  TEST_ASSERT_EQUAL_MESSAGE(126720,foo.pgn(),"bad pgn");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.da(),"bad da"); 


  pc.printf("Pdu(id,data,len) with char data\r\n");
  char bar[]={1,8,4,5}; 
  foo = nmea2k::Pdu(0x01ff41ff,&bar[0],4);
  TEST_ASSERT_EQUAL_MESSAGE(0x01ff41ff,foo.get_id(),"bad id"); 
    pc.printf("inherited from CANMessage via Frame:\r\n"); 
  pc.printf("  id = %d\r\n",foo.get_id());
  for (int i=0; i<8; i++)
    pc.printf("  data[%d] = %d\r\n",i,foo.data[i]);
  pc.printf("  len = %d\r\n",foo.len);
  pc.printf("  type = %d, %d = CANData\r\n",foo.type,CANData);
  pc.printf("  format = %d, %d = CANExtended\r\n",foo.format,CANExtended);
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.data[0],"bad data");
  TEST_ASSERT_EQUAL_MESSAGE(8,foo.data[1],"bad data");
  TEST_ASSERT_EQUAL_MESSAGE(4,foo.data[2],"bad data");
  TEST_ASSERT_EQUAL_MESSAGE(5,foo.data[3],"bad data");
  TEST_ASSERT_EQUAL_MESSAGE(4,foo.len,"bad length");
  TEST_ASSERT_EQUAL_MESSAGE(CANData,foo.type,"bad Frame type");
  TEST_ASSERT_EQUAL_MESSAGE(CANExtended,foo.format,"bad Frame format");
  pc.printf("contained in PduHeader _header:\r\n");
  pc.printf("  p = %d\r\n",foo.p());
  pc.printf("  r = %d\r\n",foo.r());
  pc.printf("  dp = %d\r\n",foo.dp());
  pc.printf("  pf = %d\r\n",foo.pf());
  pc.printf("  ps = %d\r\n",foo.ps());
  pc.printf("  sa = %d\r\n",foo.sa());
  pc.printf("  id = %d, should match\r\n",foo.get_id());
  pc.printf("  pgn = %d\r\n",foo.pgn());
  pc.printf("  da = %d\r\n",foo.da());
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"bad priority");
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.r(),"bad reserved");
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"bad data page");
  TEST_ASSERT_EQUAL_MESSAGE(255,foo.pf(),"bad PDU format");
  TEST_ASSERT_EQUAL_MESSAGE(0x41,foo.ps(),"bad PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.sa(),"bad source address");
  TEST_ASSERT_EQUAL_MESSAGE(0x1ff41,foo.pgn(),"bad pgn");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.da(),"bad da"); 

  
} // int main(void) 
