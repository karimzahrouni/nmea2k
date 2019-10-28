#ifndef PGN_60928_H
#define PGN_60928_H

#include "PgnData.h"

#define PGN_60928_PRIORITY 6
#define PGN_60928_DLEN 8

#define PGN_60928_MANUFACTURER_ACTISENSE 273
#define PGN_60928_MANUFACTURER_AIRMAR 135
#define PGN_60928_MANUFACTURER_AMPHENOL_LTW 274
#define PGN_60928_MANUFACTURER_GARMIN 229
#define PGN_60928_MANUFACTURER_MARETRON 137
#define PGN_60928_MANUFACTURER_RAYMARINE 1851
#define PGN_60928_MANUFACTURER_SIMRAD 1857
#define PGN_60928_MANUFACTURER_US_COAST_GUARD 591
#define PGN_60928_MANUFACTURER_US_NAVY 1775
#define PGN_60928_MANUFACTURER_US_NAVAL_ACADEMY 1845

#define PGN_60928_DEVICE_CLASS_RESERVED 0
#define PGN_60928_DEVICE_CLASS_SYSTEM_TOOLS 1
#define PGN_60928_DEVICE_CLASS_SAFETY_SYSTEMS 20
#define PGN_60928_DEVICE_CLASS_INTERNETWORK_DEVICE 25
#define PGN_60928_DEVICE_CLASS_ELECTRICAL_DISTRIBUTION 30
#define PGN_60928_DEVICE_CLASS_ELECTRICAL_GENERATION 35
#define PGN_60928_DEVICE_CLASS_STEERING_AND_CONTROL_SURFACES 40
#define PGN_60928_DEVICE_CLASS_PROPULSION 50
#define PGN_60928_DEVICE_CLASS_NAVIGATION 60
#define PGN_60928_DEVICE_CLASS_COMMUNICATION 70
#define PGN_60928_DEVICE_CLASS_SENSOR_COMM_INTERFACE 75
#define PGN_60928_DEVICE_CLASS_INSTRUMENTATION_GENERAL 80
#define PGN_60928_DEVICE_CLASS_EXTERNAL_ENVIRONMENT 85
#define PGN_60928_DEVICE_CLASS_INTERNAL_ENVIRONMENT 90
#define PGN_60928_DEVICE_CLASS_DECK_CARGO_FISHING_EQPT 100
#define PGN_60928_DEVICE_CLASS_DISPLAY 120
#define PGN_60928_DEVICE_CLASS_ENTERTAINMENT 125

#define PGN_60928_INDUSTRY_CODE_GLOBAL 0
#define PGN_60928_INDUSTRY_CODE_HIGHWAY 1
#define PGN_60928_INDUSTRY_CODE_AGRICULTURE 2
#define PGN_60928_INDUSTRY_CODE_CONSTRUCTION 3
#define PGN_60928_INDUSTRY_CODE_MARINE 4
#define PGN_60928_INDUSTRY_CODE_INDUSTRIAL 1

namespace nmea2k{

class Pgn60928:public PgnData{
public:
  
 Pgn60928(uint32_t name,
	  uint32_t manufacturer_code,
	  uint8_t device_instance_lower,
	  uint8_t device_instance_upper,
	  uint8_t device_function,
	  uint8_t device_class,
	  uint8_t system_instance,
	  uint8_t industry_group,
	  uint8_t address_capable):
  PgnData(PGN_60928_PRIORITY,
          60928,
          "ISO Address Claim PGN 60928",
          PGN_60928_DLEN){
    set_name(name);
    set_manufacturer_code(manufacturer_code);
    set_device_instance_lower(device_instance_lower);
    set_device_function(device_function);
    set_system_instance(system_instance);
    set_industry_group(industry_group);
    set_address_capable(address_capable);
  };
  
  unsigned char* data(){return &_translation.data[0];}

  // getters
  inline uint32_t name(){return _translation.fields.name;}
  inline uint32_t manufacturer_code(){
    return _translation.fields.manufacturer_code;
  }
  inline uint8_t device_instance_lower(){
    return _translation.fields.device_instance_lower;
  }
  inline uint8_t device_instance_upper(){
    return _translation.fields.device_instance_upper; 
  }
  inline uint8_t device_function(){
    return _translation.fields.device_function;
  }
  inline uint8_t device_class(){
    return _translation.fields.device_class;
  }
  inline uint8_t system_instance(){
    return _translation.fields.system_instance;
  }
  inline uint8_t industry_group(){
    return _translation.fields.industry_group;
  }
  inline uint8_t address_capable(){
    return _translation.fields.address_capable;
  }

  // setters
  void set_name(uint32_t x){_translation.fields.name = x & 0x001fffff;}
  void set_manufacturer_code(uint32_t x){
    _translation.fields.manufacturer_code = x & 0x7ff;
  }
  void set_device_instance_lower(uint8_t x){
    _translation.fields.device_instance_lower = x & 0x7;
  }
  void set_device_instance_upper(uint8_t x){
    _translation.fields.device_instance_upper = x & 0x1f;
  }
  void set_device_function(uint8_t x){
    _translation.fields.device_function = x;
  }
  void set_device_class(uint8_t x){
    _translation.fields.device_class = x & 0x7f;
  }
  void set_system_instance(uint8_t x){
    _translation.fields.system_instance = x & 0xf;
  }
  void set_industry_group(uint8_t x){
    _translation.fields.industry_group = x & 0x7;
  }
  void set_address_capable(uint8_t x){
    _translation.fields.address_capable = x & 0x1;
  }
  
private:
  union{
    unsigned char data[8] = {0xff,0xff,0xff,0xff,
			     0xff,0xff,0xff,0xff};
    struct{
      uint32_t name : 21,
	manufacturer_code : 11;
      uint8_t device_instance_lower : 3, //<! aka ECU instance
	device_instance_upper : 5, //<! aka Function Instance
	device_function, //<! aka Function
	reserved : 1,
	device_class : 7,
	system_instance : 4, //<! aka device class instance
	industry_group : 3,
	address_capable : 1; //<! aka arbitary address capable
    } fields;
  } _translation;
};

} // namespace nmea2k

#endif
