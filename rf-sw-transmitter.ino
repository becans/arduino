#include <RH_ASK.h>
#include <SPI.h>

#define Threshold 50 /* Greater the value, more the sensitivity */

RH_ASK driver(2000, 4, 2, 5);

int retry = 3;
const char *msg = "toggle-s01";

void setup()
{
  Serial.begin(115200);

  if(!driver.init())
    Serial.println("init failed");

  //Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callback, Threshold);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();
  
}

void callback(){
  //placeholder callback function
}

void loop()
{
  if(retry > 0){
    retry--;
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(200);
  } else{
    esp_deep_sleep_start();
  }
    
}
