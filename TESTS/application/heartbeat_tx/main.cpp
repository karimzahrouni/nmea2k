/** @file TESTS/application/heartbeat_tx/main.cpp
    @brief Periodically sends nmea2k heartbeat 
    D Evangelista, 2019 

    This code is an example of a simple node that only sends the required
    nmea2k heartbeat (PGN 126993). 
*/

#include "mbed.h"
#include "rtos.h"
#include "nmea2k.h"
#include "pgn/Pgn126993.h" 

Serial pc(USBTX,USBRX);
nmea2k::CANLayer n2k(p30,p29); // used for sending nmea2k messages



int main(void){
  unsigned char c=0;           // heartbeat sends a heartbeat counter
  int heartbeat_interval = 10; // nominally at a 60 s interval
  unsigned char node_addr = 0x01; // will need our own address
  
  nmea2k::Frame m;     // holds nmea2k data frame before sending
  nmea2k::PduHeader h; // ISO11783-3 header information 
  nmea2k::Pgn126993 d(heartbeat_interval*100,c);   // for PGN data fields
  

  pc.printf("nmea2k version %s\r\n",NMEA2K_VERSION);
  pc.printf("Simple Heartbeat PGN 126993 demo\r\n");
  pc.printf("Heartbeat interval %d s\r\n",heartbeat_interval);
  

  pc.printf("main: Heartbeat PGN 126993 send process starting\r\n"); 
  while (1){
    h = nmea2k::PduHeader(d.p,d.pgn,node_addr,NMEA2K_BROADCAST); // form header 
    m = nmea2k::Frame(h.id(),d.data(),d.dlen); // assemble message
    d = nmea2k::Pgn126993(heartbeat_interval*100,c++); // form PGN fields
    if (n2k.write(m)) // send it!
      pc.printf("main: sent %s, %0.0f s, count %d\r\n",
		d.name,
		(float) d.update_rate()/100.0,
		d.heartbeat_sequence_counter());
    else
      pc.printf("main: failed sending %s\r\n",d.name); 

    ThisThread::sleep_for(heartbeat_interval*1000); 
  } // while(1)
  
} // int main(void)


