/*
 *   Çizgi Algılama örneği (2 Kanal - TCRT5000),
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Birinci sensörden gelen çizgi algılama durumu ve değerini seri port ekranına yazdırmaktadır.
 *
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *   ---> UYARI: Algılayıcı kartınızı 2.5cm'den yukarıda konumlandırMAyınız. <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek TCRT5000 sensörlü Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1 <------
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#include <Deneyap_CiftKanalliCizgiAlgilama.h>                               // Deneyap Çizgi Algılayıcı kütüphanesinin eklenmesi

LineFollower2Channel CizgiAlgilamaSensor;                                   // 2 kanallı çizgi algılayıcı için class tanımlaması

void setup() {
    Serial.begin(115200);                                                   // Seri haberleşme başlatılması
    if (!CizgiAlgilamaSensor.begin(0x07)) {                                 // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız ");                        // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
        while (1);
    }
}

void loop() {
    uint16_t Sensor1Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog1();  // 1.sensörün değerinin okunması
    Serial.print("1.Sensör Değeri: ");
    Serial.println(Sensor1Deger);                                           // 1.sensörün verisi seri port ekranına yazdırılması

    bool Sensor1Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital1();     // 1.sensörün durumu okunması
    if (Sensor1Durum == 0) {
        Serial.println("Çizgiden çıktı");                                   // Çizgiden çıkınca seri port ekranına durumun yazdırılması
    }
    delay(10);
}
