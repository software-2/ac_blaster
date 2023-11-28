# ac_blaster
Turn a NodeMCU into a remote control for my Sharp & Honeywell portable air conditioners. The devices use MQTT to receive on/off commands, making it easy for something like Home Assistant to control.

This is a pretty simple project, and can easily be modified into a remote control for any IR-based device.

![Behold! A project box and breadboard way too big for what's basically a glorified LED blinker.](https://github.com/software-2/ac_blaster/blob/master/photo.jpg?raw=true)

## MQTT Commands
### Sharp
- `ac/on` *(no payload)* - Turns the machine on, waits a couple seconds, then kicks on the full max cool mode. Because it's hot and I want it cold now!
- `ac/off` *(no payload)* - Shut it down! Shut it all down!
### Honeywell
- `honeywell/on` *(no payload)* - Turns the machine on.
- `honeywell/off` *(no payload)* - Same command as on, but presses it twice because the AC only turns the LEDs on after the first press when the AC is already running.

## Parts
- NodeMCU - https://www.amazon.com/gp/product/B010O1G1ES
- Solderable Breadboard - https://www.amazon.com/gp/product/B071R3BFNL
- USB-C to Micro adapter - https://www.amazon.com/gp/product/B07VBV1PY5
    - lol, this costs more than the computer with wifi built in
- An IR LED. I actually used a red one and it worked for my AC - https://www.amazon.com/gp/product/B077J2WJRS
- 100 ohm resistor.
- 2N2222 transistor - https://www.amazon.com/gp/product/B07222XY81
- 2 pin JST connector - https://www.amazon.com/gp/product/B07CTH46S7
- Wire, solder, shrink wrap.

## Case
- Small case for just a wide NodeMCU: https://www.printables.com/model/659576-small-project-box-for-lol1n-esp8266-nodemcu-lolin-
- Larger case for holdikng a breadboard too: https://www.printables.com/model/389019-gikfun-breadboard-project-enclosure-box


## Assembly
- Transistor emitter to ground (Flat on top, pins pointed down, left to right, pinout is: Emitter, Base, Collector)
- Transistor base to D2 
- Transistor collector to LED negative
- LED positive to resistor to 3.3v

Since I wanted the LED to sit right next to the AC's IR receiver, I extended the LED out with some extra wire and a JST connector.

## Collecting IR data
I used a Flipper Zero to record my original remote's IR data. The unedited data is in the captures folder.

## Reference Docs
- https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRsendDemo/IRsendDemo.ino
- https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
- https://crankyoldgit.github.io/IRremoteESP8266/doxygen/html/classIRsend.html#a2b9b84f828918f933bd1764d113b53f8
- https://www.arduino.cc/reference/en/libraries/irremote/
- https://arduino-irremote.github.io/Arduino-IRremote/group__TinyReceiver.html#gaf94078156f2df01c4883c7633e9a707b
- https://github.com/plapointe6/EspMQTTClient


