/**
   @file TESTS/canlayer/interrupt-rx/main.cpp
   @brief Interrupt vomit test (rx only) for mbed OS 5 with RTOS
   D Evangelista, 2019

   This test checks the physical connections and CAN bus function
   on the device under test and is modified from the 
   mbed handbook CAN hello world program to use RTOS. It waits for
   a CAN::RxIrq interrupt then handles the message vomits it out.

   This test will fail if line 77 of mbed-os/drivers/CAN.cpp is not
   edited to comment out the lock() and unlock() Mutex bits; it's
   an oddity of mbed CAN attach and read() - the mutex normally 
   won't allow calling read() in the ISR, but calling read() is necessary
   to clear the CAN::RxIrq interrupt. 
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
nmea2k::Frame rxframe;
EventQueue rx_queue(32*EVENTS_EVENT_SIZE);
Thread rx_isr_thread; 

// function prototypes
void inside_can_irq(void);
void outside_can_irq(void); 


void inside_can_irq(void){
  n2k.read(rxframe); // clear interrupt
  // TO MAKE THIS WORK MUST COMMENT OUT lock() AND unlock() lines
  // in CAN::read() definition in mbed-os/drivers/CAN.cpp

  // outside of interrupt context, toggle lights and handle message
  rx_queue.call(&outside_can_irq); 
} // inside_can_irq()

void outside_can_irq(void){
  rxled = 1;
  pc.printf("rx_isr_thread: received id 0x%08x: 0x",rxframe.id);
  for (int i=0; i<rxframe.len; i++)
    pc.printf("%02x",rxframe.data[i]);
  pc.printf("\r\n");
  rxled = 0; 
} // outside_can_irq()




int main(void){
  pc.printf("nmea2k version ");
  pc.printf(NMEA2K_VERSION);
  pc.printf("\r\nListen and vomit test, interrupt version\r\n");

  rx_isr_thread.start(callback(&rx_queue, &EventQueue::dispatch_forever));
  n2k.attach(&inside_can_irq,CAN::RxIrq);
  
  pc.printf("main: main thread not doing much\r\n");
  while(1) {
    ThisThread::sleep_for(1000); 
  } // while(1)
} // int main()

