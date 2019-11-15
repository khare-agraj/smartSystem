#include <SoftwareSerial.h>
#include<SPI.h>
SoftwareSerial s(4, 7); //Rx, Tx
#include<MQ2.h>//we have to download MQ2 library where we have inbuilt function like readCO2()....

const int gasPin = A1;
int smoke;
MQ2 mq2(gasPin);

typedef struct {
  int pollution_level;
  double gps_coordinate_la;
  double gps_coordinate_lo;
} Data;

Data data[10];

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  mq2.begin();
}


void loop() {


  for (int i = 0; i < 10; i++) {
    smoke = analogRead(gasPin);
    Serial.print("Smoke: ");
    Serial.println(smoke);
    data[i].pollution_level = smoke;
    data[i].gps_coordinate_la = 0;
    data[i].gps_coordinate_lo = 0;
    s.write(data[i].gps_coordinate_la);
    s.write(data[i].gps_coordinate_lo);
    s.write(data[i].pollution_level);
    delay(5000);
  }

}
