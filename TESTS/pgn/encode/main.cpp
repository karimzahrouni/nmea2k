/** @file TESTS/pgn/encode/main.cpp
    @brief Test generic Pgn encode method
    Dennis Evangelista, 2019
*/

#include "Pgn.h"
#include "mbed.h"
#include "stdio.h"
#include "unity.h"
#include "PduHeader.h"
#include "Pdu.h"

Serial pc(USBTX,USBRX);

nmea2k::Pgn pgn;
nmea2k::PduHeader h; 
nmea2k::Pdu pdu; 
unsigned char d[8];
unsigned char l; 

int main(void){
  //pc.printf("nmea2k version ");
  //pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nnmea2k::Pgn::encode() test\r\n");
  
  pc.printf("Default constructor\r\n");
  pgn = nmea2k::Pgn();
  pc.printf("pgn.len = %d\r\n",pgn.len);
  TEST_ASSERT_EQUAL_MESSAGE(NMEA2K_SINGLE_FRAME_MAX_LEN,
			    pgn.len,"incorrect length");
  pgn.get_data(d,&l);
  for (int i=0; i<l; i++)
    pc.printf("pgn.data[%d] = %d\r\n",i,d[i]);
  
  // create a PduHeader and Pdu to hold result in
  h = nmea2k::PduHeader();
  //h.set_p(3); 
  h.set_pgn(127245);
  h.set_sa(0x41);
  pc.printf("h.p() = %d\r\n",h.p());
  pc.printf("h.pgn() = %d\r\n",h.pgn());
  pc.printf("h.da() = %d\r\n",h.da());
  pc.printf("h.sa() = %d\r\n",h.sa()); 
  pdu = nmea2k::Pdu();
  pc.printf("Next line should throw an error as it is unimplemented\r\n"); 
  pgn.encode(&h, &pdu);

  pc.printf("Check that payload got into Pdu\r\n");
  pc.printf("pdu.len() = %d\r\n",pdu.len);
  TEST_ASSERT_EQUAL_MESSAGE(8,pdu.len,"got wrong length back");
  for (int i=0; i<pdu.len; i++)
    pc.printf("pdu.data[%d] = %d\r\n",i,pdu.data[i]);
  pc.printf("pdu.p() = %d\r\n",pdu.p());
  TEST_ASSERT_EQUAL_MESSAGE(0,pdu.p(),"got wrong priority back");
  pc.printf("pdu.pgn() = %d\r\n",pdu.pgn());
  TEST_ASSERT_EQUAL_MESSAGE(127245,pdu.pgn(),"got wrong pgn back"); 
  pc.printf("pdu.da() = %d\r\n",pdu.da());
  TEST_ASSERT_EQUAL_MESSAGE(0xff,pdu.da(),"got wrong da back");
  pc.printf("pdu.sa() = 0x%x\r\n",pdu.sa());
  TEST_ASSERT_EQUAL_MESSAGE(0x41,pdu.sa(),"got wrong sa back"); 
}
