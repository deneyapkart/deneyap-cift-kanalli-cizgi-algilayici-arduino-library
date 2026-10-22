# Deneyap Line Follower Arduino Library
[FOR TURKISH VERSION](docs/README_tr.md) ![trflag](https://github.com/deneyapkart/deneyapkart-arduino-core/blob/master/docs/tr.png)

Arduino library for Deneyap Line Follower modules. Both module versions are supported:

| Module | Sensor | Channels | Class |
| :--- | :--- | :--- | :--- |
| Deneyap Dual Channel Line Follower (first version) | TCRT5000 | 2 | `LineFollower2Channel` |
| Deneyap Line Follower (new version) | GP2S700HCP | 4 | `LineFollower4Channel` |

You can tell the modules apart by the sensors on the bottom side: the first version has 2 TCRT5000 sensors, the new version has 4 GP2S700HCP sensors.

## :mag_right:Specifications 
- `Product ID` **M18**, **mpv1.0**
- `MCU` TCRT5000, LM393DT, STM8S003F3 (first version), GP2S700HCP (new version)
- `Module Dimension` 25,4 mm x 38,1 mm (first version)
- `I2C address` 0x07, 0x08, 0x03, 0x04

| Address |  | 
| :---      | :---     |
| 0x07 | default address |
| 0x08 | address when ADR1 pad is shorted |
| 0x03 | address when ADR2 pad is shorted |
| 0x04 | address when ADR1 and ADR2 pads are shorted |

## :closed_book:Documentation 
[Deneyap Dual Channel Line Follower Sensor](https://docs.deneyapkart.org/en/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1)

[Deneyap Dual Channel Line Follower Sensor Shematic](https://cdn.deneyapkart.org/media/upload/userFormUpload/sjMExv6JWsdFVlhcrSr5FXOlkkzHKnVl.pdf)

[Deneyap Dual Channel Line Follower Mechanical Drawing](https://cdn.deneyapkart.org/media/upload/userFormUpload/JgzkeR2l2A2fUW8mSSvYlXg4xHXhp3iU.pdf)

[TCRT5000-datasheet](https://www.vishay.com/docs/83760/tcrt5000.pdf)

[LM393DT-datasheet](https://www.st.com/resource/en/datasheet/lm393.pdf)

[How to install a Arduino Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Line Follower
This Arduino library allows you to use Deneyap Line Follower modules with I2C peripheral. You can use this library in your projects with any Arduino compatible board with I2C peripheral.

```cpp
#include <Deneyap_CiftKanalliCizgiAlgilama.h>

LineFollower2Channel Sensor2Kanal; // first version, TCRT5000 (2 channels)
LineFollower4Channel Sensor4Kanal; // new version, GP2S700HCP (4 channels)
```

Sketches written for v1.0.x that use the `LineFollower` class still work; `LineFollower` is the same class as `LineFollower2Channel`.

The 4 channel module also provides IR emitter control, dimming, calibration and line position functions (`Calibrate`, `ReadCalibrated`, `ReadLineBlack`, `ReadLineWhite`). See the examples in `examples/4Kanal_GP2S700HCP`.

### Calibration (4 channel module)
Each sensor reads the white surface and the black line differently depending on ambient light and the surface. During calibration the lightest (white) and darkest (black) value seen by each sensor is recorded. `ReadCalibrated`, `ReadLineBlack` and `ReadLineWhite` scale the readings to 0 (white) - 1000 (black) using this range. These functions do not work before calibration.

1. Hold the module over the line with the sensors facing down, 3-5 mm above the surface. Keep the same height during calibration and use; if the height changes, the white surface reads gray instead of 0 and the line position shifts. Calibrating with the module mounted on the robot, or resting on a fixed spacer, is recommended.
2. Call `Calibrate()` repeatedly for a few seconds (the `KalibrasyonluCizgiTakibi` example calls it for 10 seconds and turns the built-in LED on during that time).
3. Meanwhile, slowly sweep the module left and right across the line. Each of the 4 sensors must pass over both the white surface and the black line. If the module is mounted on a robot, you can rotate the robot left and right in place over the line.
4. After calibration, check `calibrationOn.minimum[]` and `calibrationOn.maximum[]`. If the minimum and maximum of a sensor are very close, that sensor did not see the line; repeat the calibration.

Calibration values are not stored permanently; calibrate every time the board starts, and again if the lighting or the surface changes.

## :globe_with_meridians:Repository Contents
- `/docs ` README_tr.md and product photos
- `/examples/2Kanal_TCRT5000 ` Examples for the 2 channel (TCRT5000) module
- `/examples/4Kanal_GP2S700HCP ` Examples for the 4 channel (GP2S700HCP) module
- `/src ` Source files (.cpp .h)
- `keywords.txt ` Keywords from this library that will be highlighted in the Arduino IDE
- `library.properties ` General library properties for the Arduino package manager

## Version History
1.1.0 - added 4 channel line follower (GP2S700HCP) support with `LineFollower4Channel` class, renamed `LineFollower` class to `LineFollower2Channel` (`LineFollower` is still available), `getFwVersion()` returns the version instead of printing it (high byte major, low byte minor), `begin()` uses the given I2C port, I2C address macros corrected, examples fixed, calibration guide and step-by-step instructions added to the examples

1.0.2 - library.properties update

1.0.1 - update comment line and function(I2C_ReadFirmwareData16bit)

1.0.0 - initial release

## :rocket:Hardware Connections
- Deneyap Line Follower and Board can be connected with I2C cable
- or 3V3, GND, SDA and SCL pins can be connected with jumper cables

Pins of the first version (TCRT5000) module:

|Dual Channel Line Follower| Function | Board pins | 
|:--- |   :---  | :---|
|3.3V | Power   |3.3V |      
|GND  | Ground  | GND | 
|SDA  | I2C Data  | SDA pin |
|SCL  | I2C Clock | SCL pin |
|SWIM | Debug | no connection |
|RES  | Debug | no connection |
|A1|IN1+|any Analog pin|
|A2|IN2+|any Analog pin|
|D1|OUT1|any GPIO pin|
|D2|OUT2|any GPIO pin|
|AN01|ANODE2||
|AN02|ANODE1||

## :bookmark_tabs:License Information
Please review the [LICENSE](https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library/blob/master/LICENSE) file for license information.

Calibration and line position functions of `LineFollower4Channel` are adapted from [Pololu QTRSensors](https://github.com/pololu/qtr-sensors-arduino) library (MIT License).
