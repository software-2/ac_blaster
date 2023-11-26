#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
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
const uint16_t kHz = 38; // Taken from the raw recording
IRsend irsend(kIrLed); 

// Okay, why am I using raw recordings when this is NEC?
// It's "Extended" NEC, which uses the parity bits for more data (though here it looks like they're just 0 filling?)
// The IR library doesn't have a quick & easy (non-compile it yourself) option for this. Onkyo is close, but
// it gave  the turntable problems, and sending malformed IR codes crashes the microcontroller, requiring a power cycle.
// So simple and annoying to format raw it is!
uint16_t startstop[71] = {9032, 4436, 614, 513, 613, 513, 613, 513, 613, 512, 614, 537, 589, 538, 588, 538, 588, 537, 589, 1664, 588, 1664, 588, 1664, 588, 1664, 613, 1638, 614, 512, 613, 1639, 612, 1640, 611, 515, 611, 1643, 609, 516, 610, 516, 610, 517, 609, 517, 609, 1643, 609, 517, 609, 1643, 609, 517, 609, 1643, 609, 1643, 609, 1643, 609, 1643, 609, 517, 609, 1643, 609, 40620, 9025, 2214, 609};
uint16_t faster[71] = {9038, 4461, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 589, 538, 588, 1664, 588, 1664, 588, 1665, 587, 1664, 588, 1664, 588, 537, 589, 1664, 589, 1664, 589, 537, 589, 1664, 614, 513, 613, 1640, 613, 513, 613, 514, 612, 514, 612, 515, 611, 1642, 611, 515, 611, 1642, 610, 516, 610, 1642, 611, 1642, 611, 1642, 611, 1642, 610, 40626, 9033, 2211, 612};
uint16_t slower[71] = {9040, 4432, 617, 509, 617, 509, 617, 510, 616, 509, 617, 510, 616, 510, 616, 537, 589, 537, 589, 1664, 589, 1664, 588, 1664, 588, 1663, 589, 1663, 589, 537, 589, 1663, 589, 1664, 613, 1639, 613, 1639, 613, 513, 612, 514, 612, 515, 611, 515, 611, 1642, 610, 516, 610, 516, 610, 516, 610, 1642, 610, 1642, 610, 1642, 610, 1642, 610, 516, 610, 1642, 610, 40621, 9030, 2210, 612};
uint16_t clockwise[71] = {9036, 4433, 616, 510, 616, 510, 616, 511, 615, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 1664, 589, 1664, 589, 1663, 589, 1663, 589, 1663, 614, 511, 615, 1638, 614, 1639, 613, 513, 612, 515, 611, 1642, 610, 516, 610, 516, 610, 516, 610, 1643, 610, 516, 610, 1642, 610, 1642, 610, 516, 610, 1642, 610, 1643, 609, 1642, 610, 516, 610, 1643, 609, 40621, 9029, 2212, 610};
uint16_t counterclockwise[71] = {9033, 4435, 615, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 1663, 589, 1663, 589, 1663, 589, 1663, 614, 1638, 614, 511, 615, 1638, 614, 1639, 612, 1640, 611, 515, 611, 516, 610, 516, 610, 516, 610, 516, 610, 1643, 609, 516, 610, 516, 610, 1643, 610, 1643, 609, 1643, 609, 1643, 609, 1643, 609, 516, 610, 1643, 609, 40621, 9028, 2213, 610};
uint16_t setorigin[71] = {9035, 4435, 615, 511, 615, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 1664, 588, 1663, 589, 1663, 589, 1663, 589, 1663, 614, 512, 614, 1638, 614, 1639, 612, 513, 613, 514, 612, 515, 611, 1642, 610, 516, 610, 516, 610, 1642, 610, 516, 610, 1642, 610, 1642, 610, 1642, 610, 516, 610, 1642, 610, 1642, 610, 516, 610, 1642, 610, 40623, 9030, 2212, 611};
uint16_t returnorigin[71] = {9008, 4432, 617, 509, 617, 509, 617, 537, 589, 537, 589, 511, 615, 537, 589, 510, 616, 537, 589, 1663, 589, 1663, 589, 1663, 589, 1663, 589, 1663, 589, 536, 590, 1663, 614, 1638, 614, 1638, 614, 513, 612, 513, 612, 514, 612, 515, 611, 515, 611, 516, 610, 516, 610, 516, 610, 1642, 610, 1642, 610, 1642, 610, 1642, 610, 1642, 610, 1642, 610, 1642, 610, 40619, 9028, 2211, 611};
uint16_t rotate_01[71] = {9008, 4461, 588, 537, 589, 538, 588, 538, 589, 538, 588, 537, 589, 538, 588, 538, 588, 537, 589, 1663, 590, 1663, 589, 1663, 589, 1663, 589, 1663, 612, 513, 614, 1639, 613, 1639, 613, 1640, 612, 514, 612, 515, 611, 515, 611, 1642, 611, 516, 610, 1642, 610, 516, 610, 516, 610, 1642, 610, 1642, 610, 1642, 610, 516, 610, 1642, 610, 516, 610, 1642, 610, 40625, 9030, 2210, 613};
uint16_t rotate_05[75] = {9031, 4436, 614, 512, 614, 511, 615, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 537, 589, 1663, 589, 1664, 588, 1663, 589, 1664, 614, 1638, 614, 511, 614, 1639, 613, 1640, 611, 1641, 611, 1642, 610, 1642, 610, 1643, 609, 516, 610, 516, 610, 1642, 610, 517, 609, 516, 610, 516, 610, 517, 609, 517, 609, 1643, 609, 1643, 609, 517, 609, 1643, 609, 40621, 9025, 2213, 610, 95743, 9023, 2212, 611};
uint16_t rotate_164[75] = {9033, 4462, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 538, 588, 1664, 588, 1664, 588, 1664, 588, 1664, 588, 1664, 588, 537, 589, 1664, 588, 1663, 589, 537, 589, 1664, 588, 1664, 613, 1639, 613, 513, 613, 513, 613, 1640, 612, 514, 612, 1641, 611, 515, 611, 515, 611, 515, 611, 1642, 610, 1642, 610, 515, 611, 1641, 611, 40624, 9027, 2210, 613, 95744, 8999, 2235, 613};
uint16_t rotate_148[71] = {9033, 4437, 614, 512, 614, 513, 614, 512, 614, 512, 614, 512, 614, 512, 614, 513, 613, 513, 613, 1638, 614, 1638, 614, 1639, 639, 1614, 639, 1638, 614, 512, 613, 1639, 612, 1641, 610, 1642, 610, 516, 610, 1643, 610, 1643, 610, 516, 610, 516, 610, 1643, 610, 516, 610, 516, 610, 1643, 609, 516, 610, 516, 610, 1643, 610, 1643, 609, 517, 609, 1643, 610, 40627, 9026, 2214, 610};
uint16_t rotate_132[75] = {9034, 4461, 589, 508, 618, 508, 618, 509, 617, 510, 616, 510, 616, 511, 615, 537, 589, 537, 589, 1664, 589, 1664, 588, 1663, 589, 1663, 589, 1663, 589, 536, 590, 1663, 614, 1638, 614, 1638, 614, 1639, 613, 1640, 612, 514, 612, 515, 611, 515, 611, 1642, 610, 516, 610, 516, 610, 516, 610, 516, 610, 1642, 610, 1642, 610, 1642, 610, 515, 611, 1642, 610, 40621, 9029, 2211, 612, 95745, 9026, 2210, 613};
uint16_t rotate_116[75] = {9039, 4430, 616, 510, 616, 510, 616, 510, 616, 510, 644, 481, 645, 481, 645, 481, 645, 482, 644, 1608, 644, 1609, 643, 1610, 642, 1611, 641, 1635, 617, 509, 616, 1636, 616, 1638, 614, 1639, 613, 1639, 613, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 1641, 612, 1641, 611, 1641, 611, 1641, 611, 1641, 611, 1641, 611, 40626, 9033, 2206, 612, 95729, 9055, 2207, 612};
uint16_t rotate_18[71] = {9039, 4430, 616, 510, 616, 510, 616, 510, 616, 510, 616, 510, 616, 510, 644, 482, 644, 482, 644, 1609, 643, 1609, 643, 1609, 643, 1610, 642, 1611, 641, 509, 616, 1636, 615, 1637, 615, 512, 613, 1639, 613, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 514, 612, 1641, 612, 514, 612, 1641, 612, 1641, 611, 1641, 612, 1640, 612, 1641, 611, 1640, 612, 40623, 9033, 2206, 612};
uint16_t rotate_14[71] = {9010, 4460, 587, 538, 589, 537, 589, 537, 589, 510, 617, 537, 589, 538, 588, 538, 588, 538, 588, 1664, 588, 1664, 588, 1664, 588, 1664, 588, 1664, 588, 537, 589, 1664, 589, 1663, 589, 1663, 589, 1663, 589, 536, 590, 1662, 590, 1662, 590, 536, 590, 536, 590, 536, 590, 536, 590, 536, 590, 1663, 615, 512, 614, 512, 613, 1639, 613, 1639, 613, 1639, 613, 40624, 9030, 2209, 613};


void setup() {
  irsend.begin();
}

// Custom mode managed on the device so I don't have to send out MQTT commands once a second.
bool slowmo = false;
const uint16_t slowmointerval = 1000; // Time in MS

void onConnectionEstablished() {
  
  client.subscribe("turntable/on", [] (const String &payload)  {
    slowmo = false;
    irsend.sendRaw(startstop, 71, kHz);
  });

  client.subscribe("turntable/on", [] (const String &payload)  {
    slowmo = false;
    irsend.sendRaw(startstop, 71, kHz);
  });

  client.subscribe("turntable/faster", [] (const String &payload)  {
    irsend.sendRaw(faster, 71, kHz);
  });

  client.subscribe("turntable/slower", [] (const String &payload)  {
    irsend.sendRaw(slower, 71, kHz);
  });

  client.subscribe("turntable/clockwise", [] (const String &payload)  {
    irsend.sendRaw(clockwise, 71, kHz);
  });

  client.subscribe("turntable/counterclockwise", [] (const String &payload)  {
    irsend.sendRaw(counterclockwise, 71, kHz);
  });

  client.subscribe("turntable/setorigin", [] (const String &payload)  {
    irsend.sendRaw(setorigin, 71, kHz);
  });

  client.subscribe("turntable/returnorigin", [] (const String &payload)  {
    irsend.sendRaw(returnorigin, 71, kHz);
  });
  client.subscribe("turntable/rotate_01", [] (const String &payload)  {
    irsend.sendRaw(rotate_01, 71, kHz);
  });
  client.subscribe("turntable/rotate_05", [] (const String &payload)  {
    irsend.sendRaw(rotate_05, 75, kHz);
  });
  client.subscribe("turntable/rotate_164", [] (const String &payload)  {
    irsend.sendRaw(rotate_164, 75, kHz);
  });
  client.subscribe("turntable/rotate_148", [] (const String &payload)  {
    irsend.sendRaw(rotate_148, 71, kHz);
  });
  client.subscribe("turntable/rotate_132", [] (const String &payload)  {
    irsend.sendRaw(rotate_132, 75, kHz);
  });
  client.subscribe("turntable/rotate_116", [] (const String &payload)  {
    irsend.sendRaw(rotate_116, 75, kHz);
  });
  client.subscribe("turntable/rotate_18", [] (const String &payload)  {
    irsend.sendRaw(rotate_18, 71, kHz);
  });
  client.subscribe("turntable/rotate_14", [] (const String &payload)  {
    irsend.sendRaw(rotate_14, 71, kHz);
  });
  
  client.subscribe("turntable/slowmo_on", [] (const String &payload)  {
    slowmo = true;
  });
  client.subscribe("turntable/slowmo_off", [] (const String &payload)  {
    slowmo = false;
  });
}


void loop() {
  client.loop();

  if (slowmo) {
    delay(slowmointerval); // Maybe use millis() if I ever want to get fancy, or find this delay interferes with MQTT receipts
    irsend.sendRaw(rotate_01, 71, kHz);
  }
}