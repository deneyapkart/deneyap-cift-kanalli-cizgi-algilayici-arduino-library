/*
 *   Çift Kanallı Çizgi Algılama örneği (2 Kanal - TCRT5000),
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   İki sensörden gelen çizgi algılama durumları ve değerleri seri port ekranına yazdırmaktadır.
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

    uint16_t FwVersiyon = CizgiAlgilamaSensor.getFwVersion();               // Modül yazılım versiyonunun okunması
    Serial.print("Yazılım versiyonu: v");
    Serial.print(FwVersiyon >> 8);
    Serial.print(".");
    Serial.println(FwVersiyon & 0xFF);
}

void loop() {
    uint16_t Sensor1Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog1();  // 1.sensörün değerinin okunması
    Serial.print("1.Sensör Değeri: ");
    Serial.println(Sensor1Deger);                                           // 1.sensörün verisi seri port ekranına yazdırılması

    bool Sensor1Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital1();     // 1.sensörün durumu okunması
    if (Sensor1Durum == 0) {
        Serial.println("1. sensör çizgiden çıktı");                         // 1.sensör çizgiden çıkınca seri port ekranına durumun yazdırılması
    }
    delay(10);

    uint16_t Sensor2Deger = CizgiAlgilamaSensor.ReadLineFollowerAnalog2();  // 2.sensörün değerinin okunması
    Serial.print("2.Sensör Değeri: ");
    Serial.println(Sensor2Deger);                                           // 2.sensörün verisi seri port ekranına yazdırılması

    bool Sensor2Durum = CizgiAlgilamaSensor.ReadLineFollowerDigital2();     // 2.sensörün durumu okunması
    if (Sensor2Durum == 0) {
        Serial.println("2. sensör çizgiden çıktı");                         // 2.sensör çizgiden çıkınca seri port ekranına durumun yazdırılması
    }
    delay(10);

    delay(250);
}
