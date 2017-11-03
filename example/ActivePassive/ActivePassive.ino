#include <MECHA_PMS5003ST.h>
#include <SoftwareSerial.h>

SoftwareSerial dust(2,3);

MECHA_PMS5003ST pms(&dust);

void setup() {
  Serial.begin(115200);
  pms.begin();
  pms.wakeUp();
}

void loop() {
  pms.setMode(PASSIVE);
  Serial.println("PASSIVE MODE");
  for(int i = 0;i < 10; i++){
    pms.request();
    pms.read();
    Serial.print("TEMP : ");
    Serial.println(pms.getTemp());
    delay(100);
  }
  Serial.println();

  pms.setMode(ACTIVE);
  Serial.println("ACTIVE MODE");
  unsigned long start = millis();
  while(millis() - start < 5000){
    pms.read();
    Serial.print("TEMP : ");
    Serial.println(pms.getTemp());
  }
  Serial.println();
}
