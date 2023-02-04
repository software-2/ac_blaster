#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = D2;

const uint16_t kHz = 38; //From AC.ir
IRsend irsend(kIrLed); 

uint16_t acOn[211] = {3834, 1874, 484, 426, 513, 1395, 483, 455, 484, 1396, 484, 
                      455, 484, 1396, 484, 457, 484, 1396, 484, 455, 484, 1395, 
                      484, 455, 485, 1394, 484, 1396, 483, 457, 483, 1395, 483, 
                      456, 484, 1395, 484, 1396, 485, 1394, 485, 1394, 486, 454, 
                      486, 453, 486, 1394, 485, 1394, 485, 455, 509, 430, 509, 
                      430, 509, 429, 509, 1371, 509, 431, 509, 432, 507, 432, 
                      507, 1374, 506, 434, 506, 434, 506, 432, 506, 433, 506, 
                      433, 505, 434, 506, 433, 505, 1374, 505, 434, 505, 433, 
                      506, 433, 505, 1398, 481, 435, 505, 459, 481, 435, 505, 
                      458, 481, 1399, 481, 459, 481, 459, 481, 458, 482, 1400, 
                      480, 459, 481, 459, 481, 458, 481, 459, 481, 459, 481, 459, 
                      481, 459, 481, 459, 481, 457, 481, 458, 481, 459, 481, 459, 
                      481, 458, 481, 1399, 480, 459, 481, 459, 481, 459, 481, 459, 
                      481, 460, 480, 458, 481, 459, 481, 459, 481, 459, 481, 460, 
                      480, 458, 481, 1400, 480, 459, 480, 459, 481, 459, 481, 458, 
                      480, 459, 481, 460, 480, 460, 480, 459, 481, 459, 481, 460, 
                      480, 458, 480, 460, 481, 1399, 481, 1400, 481, 1401, 480, 1398, 
                      480, 1400, 481, 460, 480, 459, 481, 460, 480, 459, 480, 1400, 
                      481, 459, 480, 459, 480};

void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {

  irsend.sendRaw(acOn, 211, kHz);
  delay(5000);

}