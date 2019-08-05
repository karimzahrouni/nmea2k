/** @file TESTS/application/vomit_rx/main.cpp
    @brief Listen for rudder commands addressed to us
    D Evangelista, 2019 
*/

#include "mbed.h"
#include "rtos.h"
#include "nmea2k.h"
#include "pgn/Pgn126993.h" 

Serial pc(USBTX,USBRX);
nmea2k::CANLayer n2k(p30,p29); // used for sending nmea2k messages
DigitalOut txled(LED1);
DigitalOut rxled(LED2); 
unsigned char node_addr = 0x03;
Thread heartbeat_thread;

void heartbeat_process(void);

int main(void){
  nmea2k::Frame f;
  nmea2k::PduHeader h;
  
  pc.printf("nmea2k version %s\r\n",NMEA2K_VERSION);
  pc.printf("PGN vomit test\r\n");
  
  heartbeat_thread.start(&heartbeat_process); 
  pc.printf("0x%02x:main: listening for any pgn\r\n",node_addr);
  while (1){

    if (n2k.read(f)){
      rxled = 1; 
      h = nmea2k::PduHeader(f.id);
      pc.printf("0x%02x:main: recieved priority %d, pgn %d, sa 0x%02x, da 0x%02x: 0x",node_addr,h.p(), h.pgn(), h.sa(), h.da());
      for (int i=0; i<f.len; i++)
	pc.printf("%02x",f.data[i]);
      pc.printf("\r\n");
      rxled = 0; 
    } // if (n2k.read(f))
    ThisThread::sleep_for(10); 
  } // while(1)
} // int main(void)






void heartbeat_process(void){
  nmea2k::Frame m;     // holds nmea2k data frame before sending
  nmea2k::PduHeader h; // ISO11783-3 header information 
  nmea2k::Pgn126993 d(6000,0);   // for PGN data fields
  unsigned int heartbeat_interval=60;
  unsigned char c=0;           // heartbeat sends a heartbeat counter

  pc.printf("0x%02x:heartbeat_thread: starting heartbeat_process\r\n",
	    node_addr); 
  while (1){
    h = nmea2k::PduHeader(d.p,d.pgn,node_addr,NMEA2K_BROADCAST); // form header 
    d = nmea2k::Pgn126993(heartbeat_interval*100,c++); // form PGN fields
    m = nmea2k::Frame(h.id(),d.data(),d.dlen); // assemble message
    if (n2k.write(m)) // send it!
      txled = 1; 
      pc.printf("0x%02x:heartbeat_thread: sent %s, %0.0f s, count %d\r\n",
		node_addr,
		d.name,
		(float) d.update_rate()/100.0,
		d.heartbeat_sequence_counter());
      txled = 0;
    else
      pc.printf("0x%02x:heartbeat_thread: failed sending %s\r\n",
		node_addr,
		d.name); 
    ThisThread::sleep_for(heartbeat_interval*1000); 
  } // while(1)
} // void heartbeat_thread(void)


