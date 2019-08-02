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
unsigned char *d;
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
  d = malloc(8,sizeof(unsigned char)); 
  pgn.get_data(d,&l);
  for (int i=0; i<l; i++)
    pc.printf("pgn.data[%d] = %d\r\n",i,d[i]);
  
  // create a PduHeader and Pdu to hold result in
  h = nmea2k::PduHeader();
  h.set_pgn(127245);
  h.set_sa(0x41);
  pdu = nmea2k::Pdu();
  pc.printf("Next line should throw an error as it is unimplemented\r\n"); 
  pgn.encode(&h, &pdu);
  
}
