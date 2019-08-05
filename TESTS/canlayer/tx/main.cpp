/**
   TESTS/canlayer/tx/main.cpp
   tx CAN test for mbed OS 5 with RTOS
   D Evangelista, 2019

   This test checks the physical connections and CAN bus function
   on the device under test and is modified from the 
   mbed handbook CAN hello world program to use RTOS. 

   This test does not really check data link layer stuff above the
   CAN bus level, e.g. it does NOT use PduHeader. 
 */

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "unity.h"
#include "nmea2k.h"

#define LEN 8
#define PGNISH 0x0041
#define TXADDR 0x00
#define RXADDR 0x01


// Note: I like to do hardware as global variables since there aren't
// more of these other than what hardware is installed... so we have to
// either be sure they are thread safe or be careful who writes to them. 
Serial pc(USBTX,USBRX); // serial RS232 link to host computer
DigitalOut txled(LED1); // indicated outgoing transmit
nmea2k::CANLayer n2k(p30,p29);
Thread receive_thread;





int main(void){
  unsigned int id; // for constructing a CAN id
  char data[LEN];  // for sending LEN bytes of dummy data
  nmea2k::Frame m; 
  
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\ntx CAN test\r\n");

  // Note when layers above PDU are implemented, we will need
  // nice ways to encode and decode PGN and addresses. Currently
  // this is done either with union struct, or probably for real
  // ought to be done with some private attributes, getters, and
  // setters. 
  id = (PGNISH << 16) + (RXADDR << 8) + TXADDR; 
  
  pc.printf("main: running tx process\r\n");
  while(1) {
    // make dummy data
    for (int i=0; i<LEN; i++)
      data[i] = rand()/256;

    // create message
    m = nmea2k::Frame(id,data,LEN);

    // send the message
    if (n2k.write(m)){
      txled = 1;
      pc.printf("main: tx sent id %d: 0x",m.id);
      for (int i=0; i<m.len; i++)
	pc.printf("%02x",m.data[i]);
      pc.printf("\r\n");
      txled = 0;
    }

    // main loop sleeps to allow other stuff to be done
    ThisThread::sleep_for(1000); 
  } // while(1)
  
} // int main(void)

