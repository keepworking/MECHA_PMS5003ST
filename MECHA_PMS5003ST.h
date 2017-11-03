#ifndef MECHA_PMS5003ST_H
#define MECHA_PMS5003ST_H

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

#include <SoftwareSerial.h>


#define foreach(x)  for(int i=0,row = x[i],size = sizeof(x)/sizeof(x[0]);i < size;row=x[++i])

#define UART_BAUD             9600

#define PMS_HEAD1             0x42
#define PMS_HEAD2             0x4d



/* CMD parameters */
#define PMS_CMD_READ          0xe2
//only works in passive mode

#define PMS_CMD_MODE          0xe1
#define PMS_CMD_MODE_PASSIVE  0x00
#define PASSIVE               0x00
#define PMS_CMD_MODE_ACTIVE   0x01
#define ACTIVE                0x01
#define PMS_CMD_SLEEP         0xe4
#define PMS_CMD_SLEEP_SLEEP   0x00
#define PMS_CMD_SLEEP_WAKEUP  0x01

/* receive packet prameters */

#define DATA_HUMI             3
#define DATA_TEMP             4
#define DATA_FORMALDE         5
#define DATA_PCS100ug         6
#define DATA_PCS50ug          7
#define DATA_PCS25ug          8
#define DATA_PCS10ug          9
#define DATA_PCS05ug          10
#define DATA_PCS03ug          11
#define DATA_PM100ATO         12
#define DATA_PM25ATO          13
#define DATA_PM10ATO          14
#define DATA_PM100CF1         15
#define DATA_PM25CF1          16
#define DATA_PM10CF1          17

/* class */

class MECHA_PMS5003ST {
public:
  unsigned int data[20];

  MECHA_PMS5003ST(SoftwareSerial *);
  MECHA_PMS5003ST(HardwareSerial *);

  //Setup
  int begin();
  void sleep();
  void wakeUp();
  void setMode(byte);
  void request();
  int read(unsigned long = 900);

  //Get the parameters
  double getHumi();
  double getTemp();
  unsigned int getForm();
  unsigned int getPcs(double);
  unsigned int getPmAto(double);
  unsigned int getPmCf1(double);

private:
  byte Packet[5] = {0x42,0x4d,0,};
  byte buffer[40];

  SoftwareSerial *sofSeri;
  HardwareSerial *hwSeri;
  Stream *Seri;
  int LRC = 0;
  void send(byte,byte,byte);
};

#endif
