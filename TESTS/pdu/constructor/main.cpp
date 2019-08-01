/** @file TESTS/pdu/constructor/main.cpp
    @brief Test of Pdu object constructor flavors

    Dennis Evangelista, 2019
*/

#include "Pdu.h"
#include "mbed.h"
#include "stdio.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
nmea2k::Pdu foo;

int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nnmea2k::Pdu() constructor tests\r\n");

  pc.printf("Empty constructor\r\n");
  foo = nmea2k::Pdu();
  pc.printf("inherited from CANMessage via Frame:\r\n"); 
  pc.printf("id = %d\r\n",foo.get_id());
  for (int i=0; i<8; i++)
    pc.printf("data[%d] = %d\r\n",id,foo.data[i]);
  pc.printf("len = %d\r\n",foo.len);
  pc.printf("type = %d, %d = CANData\r\n",foo.type,CANData);
  pc.printf("format = %d, %d = CANExtended\r\n",foo.format,CANExtended);
  pc.printf("contained in PduHeader header:\r\n");
  pc.printf("p = %d",foo.header.p());
  pc.printf("r = %d",foo.header.r());
  pc.printf("dp = %d",foo.header.dp());
  pc.printf("pf = %d",foo.header.pf());
  pc.printf("ps = %d",foo.header.ps());
  pc.printf("sa = %d",foo.header.sa());
  pc.printf("id = %d",foo.header.get_id());
  pc.printf("pgn = %d",foo.header.pgn());
  pc.printf("da = %d",foo.header.da());

  
}
