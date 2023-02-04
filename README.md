# ac_blaster
Turn a NodeMCU into a remote control for my Sharp portable air conditioner. The device uses MQTT to receive on/off commands, making it easy for something like Home Assistant to control.

This is a pretty simple project, and can easily be modified into a remote control for any IR-based device.

## MQTT Commands
- `ac/on` *(no payload)* - Turns the machine on, waits a couple seconds, then kicks on the full max cool mode. Because it's hot and I want it cold now!
- `ac/off` *(no payload)* - Shut it down! Shut it all down!

## Parts
- NodeMCU - https://www.amazon.com/gp/product/B010O1G1ES
- Solderable Breadboard - https://www.amazon.com/gp/product/B071R3BFNL
- USB-C to Micro adapter - https://www.amazon.com/gp/product/B07VBV1PY5
    - lol, this costs more than the computer with wifi built in
- An IR LED. I actually used a red one and it worked for my AC - https://www.amazon.com/gp/product/B077J2WJRS
- 2N2222 transistor - https://www.amazon.com/gp/product/B07222XY81
- 2 pin JST connector - https://www.amazon.com/gp/product/B07CTH46S7
- Wire, solder, shrink wrap.

## Case
- I made a simple case here: https://www.printables.com/model/389019-gikfun-breadboard-project-enclosure-box

## Assembly
- Transistor emitter to ground
- Transistor base to D2 
- Transistor collector to LED negative
- LED positive to 3.3v

## Collecting IR data
I used a Flipper Zero to record my original remote's IR data. The unedited data is in captures/ac_blaster.ir

## Reference Docs
- https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRsendDemo/IRsendDemo.ino
- https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
- https://crankyoldgit.github.io/IRremoteESP8266/doxygen/html/classIRsend.html#a2b9b84f828918f933bd1764d113b53f8
- https://github.com/plapointe6/EspMQTTClient


