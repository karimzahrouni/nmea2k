/** @file CANLayer.cpp
    @brief implementation file for CANLayer
    Dennis Evangelista, 2019
*/

#include "CANLayer.h"
#include "mbed.h"
#include "Frame.h"

namespace nmea2k{

CANLayer::CANLayer(mbed::PinName rd, mbed::PinName td) :
    mbed::CAN(rd, td, NMEA2K_FREQUENCY){
  debug("nmea2k::CANLayer(rd, td) constructor called %p\r\n",this); 
} // CANLayer(rd,td);

int CANLayer::write(Frame f){
  return CAN::write(f); 
}

int CANLayer::read(Frame &f, int handle){
  return CAN::read(&f, handle); 
}

void CANLayer::attach(mbed::Callback<void()> func, CAN::IrqType type){
  CAN::attach(&func, type);
  return; 
}


} //namespace nmea2k
