/*
 *   Çizgi Algılama örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   İki sensörden gelen çizgi algılama durumları ve değerleri yazdırmaktadır. 
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır. 
 *
 *   Bu örnek Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> www.....com <------ //docs
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
 *
*/
#include <Deneyap_CiftKanalliCizgiAlgilama.h>                               // Deneyap_CiftKanalliCizgiAlgilama kutuphanesi eklenmesi

LineFollower CizgiAlgilamaSensor;                                           // LineFollower için class tanımlaması

void setup() {
    Serial.begin(115200);                                                   // Seri haberleşme başlatılması
    if (!CizgiAlgilamaSensor.begin(0x07)) {                                 // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız ");                        // I2C bağlantısı başarısız olursa seri monitore yazdırılması
        while (1);
    }
}

void loop() {
    bool Sensor1Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital1();     // 1.sensorun durumu okunması
    Serial.print("\n1.Sensor Durumu: ");
    Serial.print(Sensor1Durum);                                             // 1.sensorun durumu seri monitore yazdırılması

    uint16_t Sensor1Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog1();  // 1.sensorun degerinin okunması
    Serial.print("\t1.Sensor Değeri: ");
    Serial.println(Sensor1Deger);                                           // 1.sensorun verisi seri monitore yazdırılması

    delay(10);

    bool Sensor2Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital2();     // 2.sensorun durumu okunması
    Serial.print("2.Sensor Durumu: ");
    Serial.print(Sensor2Durum);                                             // 2.sensorun durumu seri monitore yazdırılması

    uint16_t Sensor2Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog2();  // 2.sensorun degerinin okunması
    Serial.print("\t2.Sensor Değeri: ");
    Serial.println(Sensor2Deger);                                           // 2.sensorun verisi seri monitore yazdırılması

    delay(10);
}
