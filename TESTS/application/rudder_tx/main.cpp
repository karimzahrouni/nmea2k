/** @file TESTS/application/rudder_tx/main.cpp
    @brief Transmit rudder commands
    D Evangelista, 2019 

    This test code sends dummy 15 degree rudder angle and position to 
    check encoding and decoding of nmea2k PGN127245 rudder messages
*/

#include "mbed.h"
#include "rtos.h"
#include "nmea2k.h"
#include "pgn/Pgn126993.h" // heartbeat
#include "pgn/Pgn127245.h" // rudder

Serial pc(USBTX,USBRX);
nmea2k::CANLayer n2k(p30,p29); // used for sending nmea2k messages
unsigned char node_addr = 0x01;
DigitalOut txled(LED1);

Thread heartbeat_thread;
Thread rudder_thread;
void heartbeat_process(void);
void rudder_process(void);

int main(void){
  nmea2k::Frame f;
  nmea2k::PduHeader h;
  
  pc.printf("0x%02x:main: nmea2k version %s\r\n",node_addr,NMEA2K_VERSION);
  pc.printf("0x%02x:main: Rudder PGN 127245 tx demo\r\n",node_addr);
  
  heartbeat_thread.start(&heartbeat_process); 
  rudder_thread.start(&rudder_process); 
  while (1){
    ThisThread::sleep_for(100); 
  } // while(1)
} // int main(void)






void heartbeat_process(void){
  nmea2k::Frame m;     // holds nmea2k data frame before sending
  nmea2k::PduHeader h; // ISO11783-3 header information 
  nmea2k::Pgn126993 d(6000,0);   // for PGN data fields
  unsigned char c=0;           // heartbeat sends a heartbeat counter
  int heartbeat_interval = 60; // nominally at a 60 s interval
  
  pc.printf("0x%02x:heartbeat_process: starting Heartbeat PGN 126993 tx process\r\n", node_addr);
  while (1){

    txled = 1; 
    d = nmea2k::Pgn126993(heartbeat_interval*100,c++); // form PGN fields
    h = nmea2k::PduHeader(d.p,d.pgn,node_addr,NMEA2K_BROADCAST); // form header 
    m = nmea2k::Frame(h.id(),d.data(),d.dlen); // assemble message
    if (n2k.write(m)) // send it!
      pc.printf("0x%02x:heartbeat_process: sent %s in Frame %p\r\n",
		node_addr,d.name,&m);
    else
      pc.printf("0x%02x:heartbeat_process: failed sending %s\r\n",
		node_addr,d.name);
    txled = 0; 

    ThisThread::sleep_for(heartbeat_interval*1000); 
  } // while(1)
} // void heartbeat_thread(void)





void rudder_process(void){
  nmea2k::Frame m;     // holds nmea2k data frame before sending
  nmea2k::PduHeader h; // ISO11783-3 header information 
  nmea2k::Pgn127245 d(0,0,0,0);   // for PGN data fields
  int rudder_interval = 10; // nominally at a 10 s interval

  pc.printf("0x%02x:rudder_process: starting Rudder PGN 127245 tx process\r\n",
	    node_addr);
  while (1){

    txled = 1; 
    d = nmea2k::Pgn127245((uint8_t) 0, // instance
			  (uint8_t) PGN_127245_DIRECTION_RIGHT, // direction_order?
			  (int16_t) round(15.0/180.0*NMEA2K_PI*PGN_127245_ANGLE_RES), // angle_order
			  (int16_t) round(-15.0/180.0*NMEA2K_PI*PGN_127245_ANGLE_RES)); // position 
    h = nmea2k::PduHeader(d.p,d.pgn,node_addr,NMEA2K_BROADCAST); // form header 
    m = nmea2k::Frame(h.id(),d.data(),d.dlen); // assemble message

    for (int i=0; i<8; i++){
      pc.printf("%02x",d.data()[i]);
    }
    if (n2k.write(m)) // send it!
      pc.printf("0x%02x:rudder_process: sent %s in Frame %p\r\n",
		node_addr,d.name,&m);
    else
      pc.printf("0x%02x:rudder_process: failed sending %s\r\n",
		node_addr,d.name);
    txled = 0; 

    ThisThread::sleep_for(rudder_interval*1000); 
  } // while(1)
} // void rudder_thread(void)


