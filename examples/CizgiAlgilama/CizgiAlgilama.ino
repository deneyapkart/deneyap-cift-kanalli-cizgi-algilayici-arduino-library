/*
 *   Çizgi Algılama örneği,
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Birinci sensörden gelen çizgi algılama durumu ve değerini seri port ekranına yazdırmaktadır.
 * 
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *   ---> UYARI: Algılayıcı kartınızı 2.5cm'den yukarıda konumlandırMAyınız. <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır. 
 *
 *   Bu örnek Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1 <------
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#include <Deneyap_CiftKanalliCizgiAlgilama.h>                               // Deneyap Çift Kanallı Çizgi Algılayıcı kutuphanesinin eklenmesi

LineFollower CizgiAlgilamaSensor;                                           // LineFollower için class tanımlaması

void setup() {
    Serial.begin(115200);                                                   // Seri haberleşme başlatılması
    if (!CizgiAlgilamaSensor.begin(0x07)) {                                 // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız ");                        // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
        while (1);
    }
}

void loop() {
    uint16_t Sensor1Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog1();  // 1.sensorun degerinin okunması
    Serial.print("1.Sensor Değeri: ");
    Serial.println(Sensor1Deger);                                           // 1.sensorun verisi seri port ekranına yazdırılması

    bool Sensor1Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital1();     // 1.sensorun durumu okunması
    if(Sensor1Durum == 0) {
    Serial.println("Çizgiden çıktı");                                       // Çizgiden çıkınca seri port ekranına durumun yazdırılması
    }
    delay(10);
}
