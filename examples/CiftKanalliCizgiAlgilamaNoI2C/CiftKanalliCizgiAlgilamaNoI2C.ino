/*
 *   I2C haberleşme protokolü kullanılmadan Çizgi Algılama örneği,
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Birinci sensörden gelen çizgi algılama durumu ve değerini seri port ekranına yazdırmaktadır. 
 * 
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *   ---> UYARI: Algılayıcı kartınızı 2.5cm'den yukarıda konumlandırMAyınız. <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır. 
 *   Bu örnek I2C haberleşme protokolü kullanılmadan yazılmıştır.
 *
 *   Bu örnek Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1 <------
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#define DOUTPIN D0                                   // Çift Kanallı Çizgi Algılayıcı kartındaki D1 pininin D0 pinine baglanmalıdır
#define AOUTPIN A0                                   // Çift Kanallı Çizgi Algılayıcı kartındaki A1 pininin A0 pinine baglanmalıdır

void setup() {
    Serial.begin(115200);                            // Seri haberleşme başlatılması
}

void loop() {
    bool Sensor1Durum = digitalRead(DOUTPIN);        // 1.sensorun durumu okunması
    Serial.print("1.Sensor Durumu: ");
    Serial.print(Sensor1Durum);                      // 1.sensorun durumu seri monitore yazdırılması
    
    uint16_t Sensor1Deger = analogRead(AOUTPIN);     // 1.sensorun degerinin okunması
    Serial.print("\t1.Sensor Değeri: ");
    Serial.println(Sensor1Deger);                    // 1.sensorun verisi seri monitore yazdırılması

    delay(10);
}
