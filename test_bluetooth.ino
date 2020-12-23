#include<SoftwareSerial.h>
SoftwareSerial BT(51, 50);  //RX = 51; TX = 50

char c = ' ';

void setup()
{
  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  if (BT.available())  //check character/data is coming from Android
  {
    c = BT.read();    //data has come from Android and read it
    Serial.write(c);         //show the received character on Serial Monitor
    BT.println("Am primit!");
  }
}
