/**
   TESTS/physical/threaded-loopback/main.cpp
   Threaded loopback test for mbed OS 5 with RTOS
   D Evangelista, 2019

   This test checks the physical connections and CAN bus function
   on the device under test and is modified from the 
   mbed handbook CAN hello world program to use RTOS

   I don't use this test much because we don't have the boards rigged
   to do loopback easily... 
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
DigitalOut rxled(LED2); // indicates incoming receive
nmea2k::CANLayer n2k1(p9,p10); // one of two CAN ports on LPC1768
nmea2k::CANLayer n2k2(p30,p29); // other CAN port on LPC1768

Thread send_thread;



void send_callback() {
  char counter=0;
  
  pc.printf("send_thread() started\r\n");
  while(1){
    if(n2k1.write(nmea2k::Frame(1337, &counter, 1))) {
      counter++;
      pc.printf("send_thread(): sent %d\r\n", counter);
      txled = !txled; // blink light
    } // if
    else {
      pc.printf("send_thread(): couldn't send %d\r\n",counter);
      counter++;
    }
    
    ThisThread::sleep_for(1000); // nonblocking sleep for 1 s
  } // while(1)
} // send_callback



int main(void){
  nmea2k::Frame frame;
  
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nThreaded loopback test\r\n");

  send_thread.start(send_callback);
  pc.printf("main() thread started\r\n");
  while(1) {
    if(n2k2.read(frame)){
      pc.printf("main(): received %d\n",frame.data[0]);
      rxled=!rxled;
    } // if
    ThisThread::sleep_for(200); 
  } // while(1)
} // int main()

