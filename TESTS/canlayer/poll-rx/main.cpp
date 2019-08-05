/** @file TESTS/canlayer/poll-rx/main.cpp
    @brief Polling version of rx CAN test for mbed OS 5 with RTOS
    D Evangelista, 2019

    This test checks the physical connections and CAN bus function
    on the device under test and is modified from the 
    mbed handbook CAN hello world program to use RTOS. It listens
    for NMEA2K CAN messages and vomits them out if it sees them. 
    
    This test uses a thread to periodically poll for messages. It does 
    not use nmea2k PDU and higher level stuff and is mainly checking 
    CAN bus functionality. 
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "unity.h"
#include "nmea2k.h"


// Note: I like to do hardware as global variables since there aren't
// more of these other than what hardware is installed... so we have to
// either be sure they are thread safe or be careful who writes to them. 
Serial pc(USBTX,USBRX); // serial RS232 link to host computer
DigitalOut rxled(LED2); // indicates incoming receive
nmea2k::CANLayer n2k(p30,p29);
Thread receive_thread;



void receive_process(){
  nmea2k::Frame rxframe;
  
  pc.printf("receive_thread: receive_process() running, polling\r\n");
  while(1){
    if(n2k.read(rxframe)){
      rxled = 1; 
      // here you would dispatch based on message PGN and DA. 
      pc.printf("receive_thread: received id %d: 0x",rxframe.id);
      for(int i=0;i<rxframe.len;i++)
	pc.printf("%02x",rxframe.data[i]);
      pc.printf("\r\n");
      rxled = 0;
    }
    // here you could use a semaphore wait? 
    ThisThread::sleep_for(10); 
  } // while(1)
} // receive_process()





int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nListen and vomit test, polled version\r\n");

  receive_thread.start(receive_process);
  pc.printf("main: main thread not doing much\r\n");
  while(1) {
    ThisThread::sleep_for(1000); 
  } // while(1)
} // int main()

