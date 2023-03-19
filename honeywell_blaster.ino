#include <Arduino.h>
#include "TinyIRSender.hpp"
#include "EspMQTTClient.h"

EspMQTTClient client(
  "",  //wifi ssid
  "",  //wifi password
  "",  // MQTT Broker server ip
  "",   // MQTTUsername
  "",   // MQTTPassword
  "",      // Client name
   // MQTT port
);

const uint16_t kIrLed = D2;


void setup() {
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}


void onConnectionEstablished() {
  
  client.subscribe("honeywell/on", [] (const String &payload)  {
    sendNECMinimal(kIrLed, 32, 2, 0); // 32 decimal is 20 hex
  });

  client.subscribe("honeywell/off", [] (const String &payload)  {
    sendNECMinimal(kIrLed, 32, 2, 0); // 32 decimal is 20 hex
    delay(2000);
    sendNECMinimal(kIrLed, 32, 2, 0); // 32 decimal is 20 hex
  });
}


void loop() {
  client.loop();
}