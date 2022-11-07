# Deneyap Dual Channel Line Follower TCRT5000 Arduino Library
[FOR TURKISH VERSION](docs/README_tr.md) ![trflag](https://github.com/deneyapkart/deneyapkart-arduino-core/blob/master/docs/tr.png)

***** Add photo ****

Arduino library for Deneyap Dual Channel Line Follower TCRT5000 

## :mag_right:Specifications 
- `Product ID` **M18**, **mpv1.0**
- `MCU` TCRT5000, LM393DT, STM8S003F3
- `Weight` 
- `Module Dimension` 25,4 mm x 38,1 mm
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

## :pushpin:Deneyap Dual Channel Line Follower
This Arduino library allows you to use Deneyap Dual Channel Line Follower with I2C peripheral. You can use this library in your projects with any Arduino compatible board with I2C peripheral.

## :globe_with_meridians:Repository Contents
- `/docs ` README_tr.md and product photos
- `/examples ` Examples with .ino extension sketches
- `/src ` Source files (.cpp .h)
- `keywords.txt ` Keywords from this library that will be highlighted in the Arduino IDE
- `library.properties ` General library properties for the Arduino package manager

## Version History
1.0.1 - update comment line and function(I2C_ReadFirmwareData16bit)

1.0.0 - initial release

## :rocket:Hardware Connections
- Deneyap Dual Channel Line Follower and Board can be connected with I2C cable
- or 3V3, GND, SDA and SCL pins can be connected with jumper cables

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