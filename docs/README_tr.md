# Deneyap Çizgi Algılayıcı Arduino Kütüphanesi

Deneyap Çizgi Algılayıcı modülleri için Arduino kütüphanesidir. İki modül sürümü de desteklenmektedir:

| Modül | Sensör | Kanal | Sınıf |
| :--- | :--- | :--- | :--- |
| Deneyap Çift Kanallı Çizgi Algılayıcı (ilk sürüm) | TCRT5000 | 2 | `LineFollower2Channel` |
| Deneyap Çizgi Algılayıcı (yeni sürüm) | GP2S700HCP | 4 | `LineFollower4Channel` |

Modüller alt yüzlerindeki sensörlerden ayırt edilebilir: ilk sürümde 2 adet TCRT5000, yeni sürümde 4 adet GP2S700HCP sensör bulunur.

## :mag_right:Özellikler 
- `Ürün ID` **M18**, **mpv1.0**
- `MCU` TCRT5000, LM393DT, STM8S003F3 (ilk sürüm), GP2S700HCP (yeni sürüm)
- `Modul Boyutları` 25,4 mm x 38,1 mm (ilk sürüm)
- `I2C Adres` 0x07, 0x08, 0x03, 0x04

| Adres |  | 
| :---  | :---     |
| 0x07 | varsayılan adres |
| 0x08 | ADR1 kısa devre yapıldığındaki adres |
| 0x03 | ADR2 kısa devre yapıldığındaki adres |
| 0x04 | ADR1 ve ADR2 kısa devre yapıldığındaki adres |

## :closed_book:Dokümanlar
[Deneyap Çift Kanallı Çizgi Algılayıcı](https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1)

[Deneyap Çift Kanallı Çizgi Algılayıcı Şematik](https://cdn.deneyapkart.org/media/upload/userFormUpload/sjMExv6JWsdFVlhcrSr5FXOlkkzHKnVl.pdf)

[Deneyap Çift Kanallı Çizgi Algılayıcı Teknik Çizim](https://cdn.deneyapkart.org/media/upload/userFormUpload/JgzkeR2l2A2fUW8mSSvYlXg4xHXhp3iU.pdf)

[TCRT5000-datasheet](https://www.vishay.com/docs/83760/tcrt5000.pdf)

[LM393DT-datasheet](https://www.st.com/resource/en/datasheet/lm393.pdf)

[How to install a Arduino Library](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries)

## :pushpin:Deneyap Çizgi Algılayıcı
Bu Arduino kütüphanesi Deneyap Çizgi Algılayıcı modüllerinin I2C çevre birimi ile kullanılmasını sağlar. Arduino ile uyumlu, I2C çevre birimine sahip herhangi bir geliştirme kartı ile bu kütüphaneyi projelerinizde kullanabilirsiniz.

```cpp
#include <Deneyap_CiftKanalliCizgiAlgilama.h>

LineFollower2Channel Sensor2Kanal; // ilk sürüm, TCRT5000 (2 kanal)
LineFollower4Channel Sensor4Kanal; // yeni sürüm, GP2S700HCP (4 kanal)
```

v1.0.x için yazılmış ve `LineFollower` sınıfını kullanan kodlar çalışmaya devam eder; `LineFollower`, `LineFollower2Channel` ile aynı sınıftır.

4 kanallı modülde ayrıca IR LED kontrolü, parlaklık ayarı, kalibrasyon ve çizgi konumu fonksiyonları (`Calibrate`, `ReadCalibrated`, `ReadLineBlack`, `ReadLineWhite`) bulunur. Örnekler için `examples/4Kanal_GP2S700HCP` klasörüne bakınız.

### Kalibrasyon (4 kanallı modül)
Her sensör beyaz zemini ve siyah çizgiyi ortamın ışığına ve yüzeye göre farklı değerlerle görür. Kalibrasyon sırasında her sensörün gördüğü en açık (beyaz) ve en koyu (siyah) değer kaydedilir. `ReadCalibrated`, `ReadLineBlack` ve `ReadLineWhite` fonksiyonları sensör değerlerini bu aralığa göre 0 (beyaz) ile 1000 (siyah) arasına ölçekler. Bu fonksiyonlar kalibrasyon yapılmadan kullanılamaz.

1. Algılayıcıyı, sensörler aşağı bakacak şekilde zeminden 3-5 mm yükseklikte çizginin üzerine tutun. Yükseklik kalibrasyon ve kullanım sırasında aynı kalmalıdır; yükseklik değişirse beyaz zemin 0 yerine gri gibi okunur ve çizgi konumu kayar. Algılayıcıyı robota takarak ya da altına sabit bir parça koyarak kalibre etmeniz önerilir.
2. `Calibrate()` fonksiyonunu birkaç saniye boyunca tekrar tekrar çağırın (`KalibrasyonluCizgiTakibi` örneği 10 saniye boyunca çağırır ve bu sürede dahili LED'i yakar).
3. Bu sürede algılayıcıyı çizgiye dik yönde sağa sola yavaşça gezdirin. 4 sensörün her biri hem beyaz zeminin hem siyah çizginin üzerinden geçmelidir. Algılayıcı robota takılıysa robotu çizginin üzerinde kendi ekseni etrafında sağa sola döndürebilirsiniz.
4. Kalibrasyondan sonra `calibrationOn.minimum[]` ve `calibrationOn.maximum[]` dizilerindeki değerlere bakın. Bir sensörün en küçük ve en büyük değerleri birbirine çok yakınsa o sensör çizgiyi görmemiştir; kalibrasyonu tekrarlayın.

Kalibrasyon değerleri kalıcı olarak saklanmaz, kart her başladığında kalibrasyon tekrar yapılmalıdır. Ortamın ışığı ya da zemin değişirse de kalibrasyonu tekrarlayın.

## :globe_with_meridians:Repo İçeriği
- `/docs` README_tr.md ve ürün fotoğrafları
- `/examples/2Kanal_TCRT5000` 2 kanallı (TCRT5000) modül için örnek uygulamalar
- `/examples/4Kanal_GP2S700HCP` 4 kanallı (GP2S700HCP) modül için örnek uygulamalar
- `/src` kütüphane için .cpp ve .h uzantılı dosyalar
- `keywords.txt` Arduino IDE'de vurgulanacak anahtar kelimeler
- `library.properties` Arduino yöneticisi için genel kütüphane özellikleri

## Sürüm Geçmişi
1.1.0 - `LineFollower4Channel` sınıfı ile 4 kanallı çizgi algılayıcı (GP2S700HCP) desteği eklendi, `LineFollower` sınıfının adı `LineFollower2Channel` oldu (`LineFollower` kullanılmaya devam edilebilir), `getFwVersion()` versiyonu yazdırmak yerine döndürüyor (üst byte major, alt byte minor), `begin()` verilen I2C portunu kullanıyor, I2C adres makroları düzeltildi, örnekler düzeltildi, kalibrasyon rehberi ve örneklere adım adım kullanım talimatları eklendi

1.0.2 - library.properties güncellendi

1.0.1 - yorum satırları ve fonksiyon(I2C_ReadFirmwareData16bit) güncellendi

1.0.0 - ilk sürüm

## :rocket:Donanım Bağlantıları
- Deneyap Çizgi Algılayıcı ile kullanılan geliştirme kartı I2C kablosu ile bağlanabilir
- veya jumper kablolar ile 3V3, GND, SDA ve SCL bağlantıları yapılabilir. 

İlk sürüm (TCRT5000) modülün pinleri:

|Çift Kanallı Çizgi Algılayıcı| Fonksiyon| Kart pinleri |
| :---     | :---   |   :---  |
| 3.3V     |3.3V Besleme Gerilimi| 3.3V    |
| GND      | Toprak |GND      |
| SDA      |Çift Yönlü Veri Hattı| SDA pini |
| SCL      |Veri Hattı Zaman Senkronizasyon İşareti| SCL pini |
|SWIM | Debug | bağlantı yok |
|RES  | Debug | bağlantı yok |
|A1|TCRT5000 Kolektör (Alttaki)|herhangi Analog pini|
|A2|TCRT5000 Kolektör (Üstteki)|herhangi Analog pini|
|D1|TCRT5000 Dijital Çıkış (Alttaki)|herhangi GPIO pini|
|D2|TCRT5000 Dijital Çıkış (Üstteki)|herhangi GPIO pini|
|AN01|TCRT5000 Anot (Üstteki)| | 
|AN02|TCRT5000 Anot (Alttaki)| |

## :bookmark_tabs:Lisans Bilgisi 
Lisans bilgileri için [LICENSE](https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library/blob/master/LICENSE) dosyasını inceleyin.

`LineFollower4Channel` sınıfının kalibrasyon ve çizgi konumu fonksiyonları [Pololu QTRSensors](https://github.com/pololu/qtr-sensors-arduino) kütüphanesinden (MIT Lisansı) uyarlanmıştır.
