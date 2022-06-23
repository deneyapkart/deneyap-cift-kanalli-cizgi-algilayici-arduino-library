/*
 *   TCRT5000 sensörü ile Çizgi Algılama örneği,
 *
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Birinci sensörden gelen çizgi algılama durumu ve değerini yazdırmaktadır. 
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
    Serial.print("1.Sensor Durumu: ");
    Serial.print(Sensor1Durum);                                             // 1.sensorun durumu seri monitore yazdırılması

    uint16_t Sensor1Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog1();  // 1.sensorun degerinin okunması
    Serial.print("\t1.Sensor Değeri: ");
    Serial.println(Sensor1Deger);                                           // 1.sensorun verisi seri monitore yazdırılması

    delay(10);
}
