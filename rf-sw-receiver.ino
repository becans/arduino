
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 2, 4, 5);

int lastMillis;
char *comp_word = "swtoggleonmydoorlamp";
const int SWITCH = 0;
const int LED = 15;

void setup()
{
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  
  if (!driver.init())
       Serial.println("init failed");

  pinMode(SWITCH, OUTPUT);
  pinMode(LED, OUTPUT);
}


void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if(lastMillis > millis())//millis는 주기적으로 리셋됨
    lastMillis = millis() - 1000;
    
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    //driver.printBuffer("Got:", buf, buflen);    

    if(strcmp((char*)buf, comp_word) == 0 && millis() > lastMillis + 1000){
      lastMillis = millis();
      Serial.println("toggle sw!! " + (String)lastMillis);
      int val = digitalRead(SWITCH);  
      digitalWrite(SWITCH, !val);
      digitalWrite(LED, !val);
    }
  }
}
