#include "MECHA_PMS5003ST.h"

MECHA_PMS5003ST::MECHA_PMS5003ST(SoftwareSerial *serial){
  sofSeri = serial;
  Seri = sofSeri;
}

MECHA_PMS5003ST::MECHA_PMS5003ST(HardwareSerial *serial){
  hwSeri = serial;
  Seri = hwSeri;
}

int MECHA_PMS5003ST::begin(){
  if(hwSeri){hwSeri->begin(UART_BAUD);return 0;}
  if(sofSeri){sofSeri->begin(UART_BAUD);return 0;}
  return -1;
}

void MECHA_PMS5003ST::send(byte cmd,byte dataH,byte dataL){
  Packet[2] = cmd;
  Packet[3] = dataH;
  Packet[4] = dataL;
  LRC = 0;
  foreach(Packet){
    Seri->write(row);
    LRC += row;
  }
  Seri->write((LRC >> 8) & 0xff);
  Seri->write(LRC & 0xff);
}

void MECHA_PMS5003ST::sleep(){
  send(PMS_CMD_SLEEP,0x00,PMS_CMD_SLEEP_SLEEP);
}

void MECHA_PMS5003ST::wakeUp(){
  send(PMS_CMD_SLEEP,0x00,PMS_CMD_SLEEP_WAKEUP);
}

void MECHA_PMS5003ST::setMode(byte mode){
  send(PMS_CMD_MODE,0x00,mode);
  while(Seri->available() > 0){
    Seri->read();
  }
}

void MECHA_PMS5003ST::request(){
  send(PMS_CMD_READ,0x00,0x00);
}

int MECHA_PMS5003ST::read(unsigned long timeout){
  static unsigned long start;
  static int cnt;
  static unsigned int check;
  cnt = 0;
  check = 0;
  start = millis();
  while(Seri->available() < 40){
     if(millis() - start > timeout){return;}
  }
  while(Seri->available() > 0){
    byte c = Seri->read();
    buffer[39-(cnt)] = c;
    if(cnt < 38){
      check += (unsigned int)c;
    }
    cnt++;
    cnt = cnt % 40;
  }
  if(reinterpret_cast<unsigned int *> (buffer)[19] != 0x424D ||
      reinterpret_cast<unsigned int *> (buffer)[0] != check){
    return false;
  }
  memcpy(data,buffer,sizeof(buffer));
  return true;
}

double MECHA_PMS5003ST::getHumi(){
  return data[DATA_HUMI]/10.0;
}

double MECHA_PMS5003ST::getTemp(){
  return data[DATA_TEMP]/10.0;
}

double MECHA_PMS5003ST::getForm(){
  return data[DATA_FORMALDE]/1000.0;
}

unsigned int MECHA_PMS5003ST::getPcs(double pcs){
  switch((int)(pcs*10)){
    case 100: return data[DATA_PCS100ug];
    case 50 : return data[DATA_PCS50ug];
    case 25 : return data[DATA_PCS25ug];
    case 10 : return data[DATA_PCS10ug];
    case 5  : return data[DATA_PCS05ug];
    case 3  : return data[DATA_PCS03ug];
  }
  return 0;
}

unsigned int MECHA_PMS5003ST::getPmAto(double pm){
  switch((int)(pm*10)){
    case 100: return data[DATA_PM100ATO];
    case 25 : return data[DATA_PM25ATO];
    case 10 : return data[DATA_PM10ATO];
  }
  return 0;
}

unsigned int MECHA_PMS5003ST::getPmCf1(double pm){
  switch((int)(pm*10)){
    case 100: return data[DATA_PM100CF1];
    case 25 : return data[DATA_PM25CF1];
    case 10 : return data[DATA_PM10CF1];
  }
  return 0;
}
