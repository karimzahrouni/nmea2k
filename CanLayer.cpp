/** @file CanLayer.cpp
    @brief nmea2k::CanLayer implementation
    Dennis Evnagelista, 2019
*/

#include "mbed.h"
#include "nmea2k.h"

namespace nmea2k{

  
  CanLayer::CanLayer(mbed::PinName tx,
		     mbed::PinName rx) : 
    CAN::CAN(tx,rx,NMEA2K_FREQUENCY){
    debug("nmea2k::CanLayer(tx,rx) constructor called\r\n");
  } // nmea2k::CanLayer() constructor implementation

  
  CanLayer::~CanLayer(){
    debug("nmea2k::~CanLayer() destructor called\r\n");
    // N.B. super class destructors are automatically called,
    // base class last, so do not call super class destructor. 
  } // nmea2k::~CanLayer() destructor implementation

  
  int CanLayer::write(Frame frame){
    return CAN::write(frame);
  } // nmea2k::CanLayer::write(frame) implementation

  /*
    This has been modified from the definition of CAN::read() around
    line 77 of mbed-os/drivers/CAN.cpp, hopefully I did it right. I think
    can_read and _can should be known things since CanLayer inherits from 
    CAN inherits from private NonCopyable<CAN>? 

    Either I have to modify it to inherit protected NonCopyable<CAN> 
    or comment out the locks. Hrm. Commenting out the locks seems more
    straightforward. 
   */
  int CanLayer::read(Frame &frame, int handle){
    return CAN::read(frame, handle); 
  } // nmea2k::CanLayer::read(frame,handle) implementation

  void CanLayer::attach(mbed::Callback<void()> func, CAN::IrqType type){
    debug("Warning: CAN.read() has a Mutex that leads to odd behavior in ISRs.\r\n");
    // Have to edit mbed-os/drivers/CAN.cpp to remove lock() and unlock() lines
    // to allow using can.read() inside ISR. see here:
    // https://os.mbed.com/questions/76892/How-to-clear-CAN-bus-interrupt-flag-Miss/
    CAN::attach(func,type); 
  } // nmea2k::CanLayer::attach(func,type) implementation

} // namespace nmea2k
