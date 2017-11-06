# Mechasolution PMS5003ST Arduino Library

사실 DFRobot 에서 판매되고 있는 미세먼지 센서의 라이브러리입니다.

저희 회사도 좋은 제품 발굴해서 이렇게 독자적으로 라이브러리를 만들어서 팔면 얼마나 좋을까... 하고 생각하곤 합니다.

상품 팔려고 보니까 라이브러리가 없고 제조사에서 제공하는 코드는 센서 데이터 패킷을 받아서 값을 확인하는 예제만을 재공하고 있었습니다. 하지만 해당 센서는 패킷을 보내 sleep 모드로 전환하거나, 센서 데이터를 알아서 출력할지 그러지 않을지를 고르는 기능도 가지고 있기 때문에 이를 다루지 않고 기본 설정으로만 사용하는 것은 아쉬워 이렇게 라이브러리를 만들게 되었습니다.

## Arduino Code

라이브러리를 사용하기 위해 필요한 기본 규칙이 몇가지 있습니다. 다음을 잘 읽어주시고, 하고 계신 프로젝트에 적용해 주세요.

### Basic Element

기본 사용에 필요한 헤더파일(#include...)와 Setup쪽 코드입니다.

하드웨어 시리얼을 사용할 경우
```
#include<MECHA_PMS5003ST.h>

MECHA_PMS5003ST pms(&Serial);//pms 명칭은 사용자 자유입니다.

void setup(){
  pms.begin();
}
```

소프트웨어 시리얼을 사용할 경우
```
#include<SoftwareSerial.h>
#include<MECHA_PMS5003ST.h>

SoftwareSerial mySerial(Rx,Tx)//mySerial,Rx,Tx 명칭은 사용자 자유입니다.
MECHA_PMS5003ST pms(&mySerial);

void setup(){
  pms.begin();
}
```

### Setting mode

PMS5003ST는 일정 주기마다 센서 데이터를 출력하는 ACTIVE 모드와, 요청이 있을때만 센서 데이터를 출력하는 PASSIVE 모드가 있습니다. 개발자의 기호에 따라 이를 골라서 사용할 수있습니다.

setup 함수쪽에 작성해 두는 것을 권장하며, 필요에 따라 다른 곳에 사용 될 수 있습니다.

```
void setup(){
  pms.begin();
  pms.setMode(ACTIVE);
  //또는
  pms.setMode(PASSIVE);
}
```

### Sleep & wakeUp

PMS5003ST는 내부적으로 쿨러등이 내장 되어 동작하는 제품입니다. 기본 전류 소모량이 많은 제품인데 실시간으로 측정 할 필요가 없다면 잠시 sleep 모드로 넘어가서 전류를 아끼어 보는 건 어떤가요?

다만 sleep 모드에서 깨어나면 올바른 값을 읽기 위해 30분 가량 걸린다고 합니다.

```
void loop(){
  pms.sleep();
  delay(1000);
  pms.wakeUp();
  delay(1000);
  //쿨링팬이 동작하는 소리를 들을 수 있습니다.
}
```

### Get sensor data

PMS5003ST 미세먼지 센서는 다양한 종류의 센서 데이터를 제공합니다.

* [습도](#getHumi)
* [온도](#getTemp)
* [포름알데히드](#getForm)
* [대기 미세먼지 수치](#getPmAto)
* [표준 입자 미세먼지 수치](#getPmCf1)
* []
