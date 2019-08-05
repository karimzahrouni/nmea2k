/**
   TESTS/physical/threaded-rxonly/main.cpp
   Threaded loopback test (rx only) for mbed OS 5 with RTOS
   D Evangelista, 2019

   This test checks the physical connections and CAN bus function
   on the device under test and is modified from the 
   mbed handbook CAN hello world program to use RTOS
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



void receive_callback(){
  nmea2k::Frame rxframe;
  
  pc.printf("receive_callback() running in receive_thread\r\n");
  while(1){
    if(n2k.read(rxframe)){
      pc.printf("receive_thread(): received id %d: 0x",rxframe.id);
      for (int i=0; i<rxframe.len; i++)
	pc.printf("%02x",rxframe.data[i]);
      pc.printf("\r\n");
      rxled=!rxled;
    }
    ThisThread::sleep_for(10); 
  } // while(1)
} // receive_callback()





int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nThreaded loopback test\r\n");

  receive_thread.start(receive_callback);
  pc.printf("main() thread started\r\n");
  while(1) {
    pc.printf("main(): I'm asleep and doing nothing\r\n");
    ThisThread::sleep_for(1000); 
  } // while(1)
} // int main()

