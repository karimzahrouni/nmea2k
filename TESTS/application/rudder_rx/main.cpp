/** @file TESTS/application/rudder_rx/main.cpp
    @brief Listen for rudder commands addressed to us
    D Evangelista, 2019 
*/

#include "mbed.h"
#include "rtos.h"
#include "platform/SharedPtr.h"
#include "nmea2k.h"
#include "pgn/Pgn126993.h"
#include "pgn/Pgn127245.h"

Serial pc(USBTX,USBRX);
nmea2k::CANLayer n2k(p30,p29); // used for sending nmea2k messages
unsigned char node_addr = 0x02;
Thread heartbeat_thread;

void heartbeat_process(void);

int main(void){
  nmea2k::Frame f;
  nmea2k::PduHeader h;
  SharedPtr<nmea2k::PgnData> d;
  //  nmea2k::PgnParser127245 RudderParser(); 
  
  pc.printf("0x%02x:main: nmea2k version %s\r\n",node_addr,NMEA2K_VERSION);
  pc.printf("0x%02x:main: PGN 127245 receive demo\r\n",node_addr);
  
  heartbeat_thread.start(&heartbeat_process); 
  pc.printf("0x%02x:main: listening for Rudder PGN 127245\r\n", node_addr);
  while (1){

    if (n2k.read(f)){
      h = nmea2k::PduHeader(f.id);
      if ((h.da() == NMEA2K_BROADCAST) || (h.da() == node_addr))
        switch(h.pgn()){
          case 127245:
            debug("0x%02x:main: handling Rudder PGN 127245\r\n", node_addr);
            //d = PgnParser127245(f.data,f.len);
            if (d)
              pc.printf("0x%02x:main: successfully parsed?\r\n", node_addr);
            else
              pc.printf("0x%02x:main: did not parse successfully\r\n", node_addr);
            break;
          default:
            pc.printf("0x%02x:main: received unhandled PGN %d\r\n",
		      node_addr,h.pgn());
        } // switch(h.pgn())
    } // if addressed to us
    
    ThisThread::sleep_for(10); 
  } // while(1)
} // int main(void)






void heartbeat_process(void){
  nmea2k::Frame m;     // holds nmea2k data frame before sending
  nmea2k::PduHeader h; // ISO11783-3 header information 
  nmea2k::PgnData d;   // for PGN data fields
  unsigned char c=0;           // heartbeat sends a heartbeat counter
  int heartbeat_interval = 60; // nominally at a 60 s interval
  
  pc.printf("0x%02x:heartbeat_process: starting Heartbeat PGN 126993 tx process\r\n",node_addr); 
  while (1){
    
    d = nmea2k::Pgn126993(heartbeat_interval*100,c++); // form PGN fields
    h = nmea2k::PduHeader(d.p,d.pgn,node_addr,NMEA2K_BROADCAST); // form header 
    m = nmea2k::Frame(h.id(),d.data(),d.dlen); // assemble message
    if (n2k.write(m)) // send it!
      pc.printf("0x%02x:heartbeat_process: sent %s in Frame %p\r\n",
		node_addr,d.name,&m);
    else
      pc.printf("0x%02x:heartbeat_process: failed sending %s\r\n",
		node_addr,d.name); 

    ThisThread::sleep_for(heartbeat_interval*1000); 
  } // while(1)
} // void heartbeat_thread(void)


