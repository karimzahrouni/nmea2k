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

  pc.printf("set_id(), get_id()\r\n");
  foo.set_id(0x01fedcba);
  TEST_ASSERT_EQUAL_MESSAGE(0x01fedcba,foo.get_id(),"failed id via get_id");
  TEST_ASSERT_EQUAL_MESSAGE(0x01fedcba,foo.id,"failed id via CANMessage");
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

  pc.printf("set_header()\r\n"); 
  h = nmea2k::PduHeader(0,127245,0x41);
  foo.set_header(h);
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
  TEST_ASSERT_EQUAL_MESSAGE(0,foo.p(),"failed priority");
  TEST_ASSERT_EQUAL_MESSAGE(127245,foo.pgn(),"failed pgn");
  TEST_ASSERT_EQUAL_MESSAGE(0x41,foo.sa(),"failed source address");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.da(),"failed destination address");
  
  pc.printf("Test setters and getters\r\n");
  foo = nmea2k::Pdu();
  foo.set_p(7);
  TEST_ASSERT_EQUAL_MESSAGE(7,foo.p(),"failed to set priority");
  foo.set_dp(1);
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to set data page");
  foo.set_pf(240);
  TEST_ASSERT_EQUAL_MESSAGE(240,foo.pf(),"failed to set PDU format");
  foo.set_ps(128);
  TEST_ASSERT_EQUAL_MESSAGE(128,foo.ps(),"failed to set PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(0xff,foo.da(),"failed to set DA for PF>=240"); 
  foo.set_sa(41);
  TEST_ASSERT_EQUAL_MESSAGE(41,foo.sa(),"failed to set source address"); 
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

  pc.printf("Test setters and getters, case 2\r\n");
  foo = nmea2k::Pdu();
  foo.set_p(7);
  TEST_ASSERT_EQUAL_MESSAGE(7,foo.p(),"failed to set priority");
  foo.set_dp(1);
  TEST_ASSERT_EQUAL_MESSAGE(1,foo.dp(),"failed to set data page");
  foo.set_pf(239);
  TEST_ASSERT_EQUAL_MESSAGE(239,foo.pf(),"failed to set PDU format");
  foo.set_ps(128);
  TEST_ASSERT_EQUAL_MESSAGE(128,foo.ps(),"failed to set PDU specific");
  TEST_ASSERT_EQUAL_MESSAGE(128,foo.da(),"failed to set DA for PF<240"); 
  foo.set_sa(41);
  TEST_ASSERT_EQUAL_MESSAGE(41,foo.sa(),"failed to set source address"); 
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
  
  
} // int main(void) 
