/**
   TESTS/physical/threaded-txonly/main.cpp
   Threaded loopback test (tx only) for mbed OS 5 with RTOS
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
DigitalOut txled(LED1); // indicates outgoing transmit
nmea2k::CanLayer n2k(p30,p29); // one of two CAN ports on LPC1768
Thread send_thread;



void send_callback() {
  char counter=0;
  nmea2k::Frame txframe; 
  
  pc.printf("send_callback() running in send_thread\r\n");
  while(1){
    txframe = nmea2k::Frame(1337, &counter, 1); 
    if(n2k.write(txframe)) {
      counter++;
      pc.printf("send_thread: sent id %d: 0x",txframe.id);
      for (int i=0; i<txframe.len; i++)
	pc.printf("%02x",txframe.data[i]);
      pc.printf("\r\n");
      txled = !txled; // blink light
    } // if
    else {
      pc.printf("send_thread: failed sending id %d: 0x",txframe.id);
      for (int i=0; i<txframe.len; i++)
	pc.printf("%02x",txframe.data[i]);
      pc.printf("\r\n");
      counter++;
    }
    
    ThisThread::sleep_for(1000); // nonblocking sleep for 1 s
  } // while(1)
} // send_callback



int main(void){ 
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nThreaded loopback test\r\n");

  send_thread.start(send_callback);
  pc.printf("main() thread started, not doing much\r\n");
  while(1) {
    ThisThread::sleep_for(1000); 
  } // while(1)
} // int main()

