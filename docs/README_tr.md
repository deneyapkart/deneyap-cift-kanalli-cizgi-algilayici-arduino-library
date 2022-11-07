# Deneyap Çift Kanallı Çizgi Algılayıcı Arduino Kütüphanesi

***** Fotoğraf eklenecek ****

Deneyap Çift Kanallı Çizgi Algılayıcı TCRT5000 için Arduino kütüphanesidir.

## :mag_right:Özellikler 
- `Ürün ID` **M18**, **mpv1.0**
- `MCU` TCRT5000, LM393DT, STM8S003F3
- `Ağırlık`
- `Modul Boyutları` 25,4 mm x 38,1 mm
- `I2C Adres` 0x07, 0x08, 0x03, 0x04

| Adres |  | 
| :---  | :---     |
| 0x07 | varsayılan adres |
| 0x08 | ADR1 kısa devre yapıldığındaki adres |
| 0x03 | ADR1 kısa devre yapıldığındaki adres |
| 0x04 | ADR1 ve ADR2 kısa devre yapıldığındaki adres |

## :closed_book:Dokümanlar
[Deneyap Çift Kanallı Çizgi Algılayıcı](https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1)

[Deneyap Çift Kanallı Çizgi Algılayıcı Şematik](https://cdn.deneyapkart.org/media/upload/userFormUpload/sjMExv6JWsdFVlhcrSr5FXOlkkzHKnVl.pdf)

[Deneyap Çift Kanallı Çizgi Algılayıcı Teknik Çizim](https://cdn.deneyapkart.org/media/upload/userFormUpload/JgzkeR2l2A2fUW8mSSvYlXg4xHXhp3iU.pdf)

[TCRT5000-datasheet](https://www.vishay.com/docs/83760/tcrt5000.pdf)

[LM393DT-datasheet](https://www.st.com/resource/en/datasheet/lm393.pdf)

[How to install a Arduino Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Çift Kanallı Çizgi Algılayıcı
Bu Arduino kütüphanesi Deneyap Çift Kanallı Çizgi Algılayıcı I2C çevre birimi ile kullanılmasını sağlar. Arduino ile uyumlu, I2C çevre birimine sahip herhangi bir geliştirme kartı ile bu kütüphaneyi projelerinizde kullanabilirsiniz.

## :globe_with_meridians:Repo İçeriği
- `/docs` README_tr.md ve ürün fotoğrafları
- `/examples` .ino uzantılı örnek uygulamalar
- `/src` kütüphane için .cpp ve .h uzantılı dosyalar
- `keywords.txt` Arduino IDE'de vurgulanacak anahtar kelimeler
- `library.properties` Arduino yöneticisi için genel kütüphane özellikleri

## Sürüm Geçmişi
1.0.1 - yorum satırları ve fonksiyon(I2C_ReadFirmwareData16bit) güncellendi

1.0.0 - ilk sürüm

## :rocket:Donanım Bağlantıları
- Deneyap Çift Kanallı Çizgi Algılayıcı ile kullanılan geliştirme kartı I2C kablosu ile bağlanabilir
- veya jumper kablolar ile 3V3, GND, SDA ve SCL bağlantıları yapılabilir. 

|Çift Kanallı Çizgi Algılayıcı| Fonksiyon| Kart pinleri |
| :---     | :---   |   :---  |
| 3.3V     |3.3V Besleme Gerilimi| 3.3V    |
| GND      | Toprak |GND      |
| SDA      |Çift Yönlü Veri Hattı| SDA pini |
| SCL      |Veri Hattı Zaman Senkronizasyon İşareti|
|SWIM | Debug | bağlantı yok |
|RES  | Debug | bağlantı yok |
|A1|TCRT5000 Kolektör (Alttaki)|herhangi Analog pini|
|A2|TCRT5000 Kolektör (Üstteki)|herhangi Analog pini|
|D1|TCRT5000 Dijtal Çıkış (Alttaki)|herhangi GPIO pini|
|D2|TCRT5000 Dijtal Çıkış (Üstteki)|herhangi GPIO pini|
|AN01|TCRT5000 Anot (Üstteki)| | 
|AN02|TCRT5000 Anot (Alttaki)| |

## :bookmark_tabs:Lisans Bilgisi 
Lisans bilgileri için [LICENSE](https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library/blob/master/LICENSE) dosyasını inceleyin.