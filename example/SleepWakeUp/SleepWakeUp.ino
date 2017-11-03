#include <MECHA_PMS5003ST.h>
#include <SoftwareSerial.h>

SoftwareSerial dust(2,3);

MECHA_PMS5003ST pms(&dust);

void setup() {
  Serial.begin(115200);
  pms.begin();
}

void loop() {
  pms.sleep();
  delay(1000);
  pms.wakeUp();
  delay(1000);
}
