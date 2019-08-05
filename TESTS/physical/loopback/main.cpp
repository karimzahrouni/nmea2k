/**
   TESTS/physical/loopback/main.cpp
   Loopback test
   D Evangelista, 2019

   This test checks the physical connections and CAN bus function
   on the device under test and is a pretty straight copy of the 
   mbed handbook CAN hello world program. 
   See: <https://os.mbed.com/handbook/CAN>

   I don't run this test much because we don't have the boards
   rigged to do loopback easily. 
 */

#include "mbed.h"
#include "stdio.h"
#include "unity.h"
#include "nmea2k.h"

Serial pc(USBTX,USBRX);
Ticker ticker;
DigitalOut txled(LED1);
DigitalOut rxled(LED2);
nmea2k::CanLayer n2k1(p9,p10);
nmea2k::CanLayer n2k2(p30,p29);
char counter=0; 



void send() {
  pc.printf("send()\r\n");
  if(n2k1.write(nmea2k::Frame(1337, &counter, 1))) {
    counter++;
    pc.printf("send(): sent %d\n", counter);
  }
  txled = !txled;
}



int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nLoopback test\r\n");

  ticker.attach(&send,1);
  Nmea2kFrame frame;
  while(1) {
    pc.printf("loop()\n");
    if(n2k2.read(frame)){
      pc.printf("main(): received %d\n",frame.data[0]);
      rxled=!rxled;
    }
    wait(0.2);
  }
} // int main()

