/*
 *   I2C haberleşme protokolü kullanılmadan ile Çizgi Algılama örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   İki sensörden gelen çizgi algılama durumları ve değerleri yazdırmaktadır. 
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır. 
 *   Bu örnek I2C haberleşme protokolü kullanılmadan yazılmıştır.
 *
 *   Bu örnek Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------ 
 *
*/
#define DOUTPIN1 D0                                  // Çift Kanallı Çizgi Algılayıcı kartındaki D1 pininin D0 pinine baglanmalıdır
#define AOUTPIN1 A0                                  // Çift Kanallı Çizgi Algılayıcı kartındaki A1 pininin A0 pinine baglanmalıdır
#define DOUTPIN2 D1                                  // Çift Kanallı Çizgi Algılayıcı kartındaki D1 pininin D1 pinine baglanmalıdır
#define AOUTPIN2 A1                                  // Çift Kanallı Çizgi Algılayıcı kartındaki A1 pininin A2 pinine baglanmalıdır

void setup() {
    Serial.begin(115200);                            // Seri haberleşme başlatılması
}

void loop() {
    bool Sensor1Durum = digitalRead(DOUTPIN1);       // 1.sensorun durumu okunması
    Serial.print("\n1.Sensor Durumu: ");
    Serial.print(Sensor1Durum);                      // 1.sensorun durumu seri monitore yazdırılması
    
    uint16_t Sensor1Deger = analogRead(AOUTPIN1);    // 1.sensorun degerinin okunması
    Serial.print("\t1.Sensor Değeri: ");
    Serial.println(Sensor1Deger);                    // 1.sensorun verisi seri monitore yazdırılması

    delay(100);

    bool Sensor2Durum = digitalRead(DOUTPIN2);       // 2.sensorun durumu okunması
    Serial.print("2.Sensor Durumu: ");
    Serial.print(Sensor2Durum);                      // 2.sensorun durumu seri monitore yazdırılması
    
    uint16_t Sensor2Deger = analogRead(AOUTPIN2);    // 2.sensorun degerinin okunması
    Serial.print("\t2.Sensor Değeri: ");
    Serial.println(Sensor2Deger);                    // 2.sensorun verisi seri monitore yazdırılması

    delay(100);
}
