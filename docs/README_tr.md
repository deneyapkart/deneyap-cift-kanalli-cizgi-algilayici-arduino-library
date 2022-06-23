# Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000 Arduino Kütüphanesi

***** Fotoğraf eklenecek ****

Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000 için Arduino kütüphanesidir.

## :mag_right:Özellikler 
- `Ürün ID` **M18**, **mpv1.0**
- `MCU` TCRT5000, STM8S003F3
- `Ağırlık`
- `Modul Boyutları`
- `I2C Adres` 0x07, 0x08, 0x03, 0x04

| Adres |  | 
| :---  | :---     |
| 0x07 | varsayılan adres |
| 0x08 | ADR1 kısa devre yapıldığındaki adres |
| 0x03 | ADR1 kısa devre yapıldığındaki adres |
| 0x04 | ADR1 ve ADR2 kısa devre yapıldığındaki adres |

## :closed_book:Dokümanlar
Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000

[TCRT5000-datasheet](https://cdn.ozdisan.com/ETicaret_Dosya/6185_5182930.pdf)

[Arduino Kütüphanesi Nasıl İndirilir](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000
Bu Arduino kütüphanesi Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000nin I2C çevre birimi ile kullanılmasını sağlar. Arduino ile uyumlu, I2C çevre birimine sahip herhangi bir geliştirme kartı ile bu kütüphaneyi projelerinizde kullanabilirsiniz.

## :globe_with_meridians:Repo İçeriği
- `/docs` README_tr.md ve ürün fotoğrafları
- `/examples` .ino uzantılı örnek uygulamalar
- `/src` kütüphane için .cpp ve .h uzantılı dosyalar
- `keywords.txt` Arduino IDE'de vurgulanacak anahtar kelimeler
- `library.properties` Arduino yöneticisi için genel kütüphane özellikleri

## Sürüm Geçmişi
1.0.0 - ilk sürüm

## :rocket:Donanım Bağlantıları
- Deneyap Çift Kanallı Çizgi Algılayıcı ile kullanılan geliştirme kartı I2C kablosu ile bağlanabilir
- veya jumper kablolar ile ile 3V3, GND, SDA ve SCL bağlantıları yapılabilir. 

|Çift Kanallı Çizgi Algılayıcı| Fonksiyon| Kart pinleri |
| :---     | :---   |   :---  |
| 3.3V     | Güç    | 3.3V    |
| GND      | Toprak |GND      |
| SDA      | I2C Data  | SDA pini |
| SCL      | I2C Clock | SCL pini|
|SWIM | Debug | bağlantı yok |
|RES  | Debug | bağlantı yok |
|A1|IN1+|herhangi Analog pini|
|A2|IN2+|herhangi Analog pini|
|D1|OUT1|herhangi GPIO pini|
|D2|OUT2|herhangi GPIO pini|
|AN01|ANODE2| | 
|AN02|ANODE1| |

## :bookmark_tabs:Lisans Bilgisi 
Lisans bilgileri için [LICENSE](https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library/blob/master/LICENSE) dosyasını inceleyin.