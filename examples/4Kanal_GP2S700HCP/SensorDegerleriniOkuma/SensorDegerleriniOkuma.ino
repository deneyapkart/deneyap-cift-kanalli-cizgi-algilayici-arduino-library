/*
 *   Sensör Değerlerini Okuma örneği (4 Kanal - GP2S700HCP),
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Dört sensörün ham değerlerini seri port ekranına yazdırmaktadır.
 *   Değer büyüdükçe yüzey koyulaşır (siyah çizgi), küçüldükçe yüzey açıklaşır (beyaz zemin).
 *   Bu örnek, algılayıcının çalıştığını kalibrasyon yapmadan kontrol etmek için kullanılır.
 *
 *   YAPILMASI GEREKENLER (adım adım):
 *   1. Algılayıcıyı karta I2C kablosu ile bağlayınız ve bu örneği karta yükleyiniz.
 *   2. Seri port ekranını 115200 baud ile açınız. Yazılım versiyonu ve sensör değerleri yazdırılır.
 *   3. Algılayıcıyı, sensörler aşağı bakacak şekilde beyaz zeminden 3-5 mm yükseklikte tutunuz.
 *      4 sensörün değeri de düşük olmalıdır.
 *   4. Algılayıcıyı aynı yükseklikte siyah bandın üzerine getiriniz. Bandın altındaki sensörlerin değeri
 *      yükselmelidir (en fazla zaman aşımı değeri kadar, varsayılan 1500).
 *   5. Bandı sırayla her sensörün altından geçiriniz; her sensörün ayrı ayrı tepki verdiğini kontrol ediniz.
 *   Beyaz ve siyah değerleri arasında belirgin fark yoksa algılayıcıyı zemine yaklaştırınız ve
 *   parlak olmayan (mat) bir bant kullanınız. Çizgi takibi için KalibrasyonluCizgiTakibi örneğini kullanınız.
 *
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek GP2S700HCP sensörlü Deneyap Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#include <Deneyap_CiftKanalliCizgiAlgilama.h>                       // Deneyap Çizgi Algılayıcı kütüphanesinin eklenmesi

LineFollower4Channel CizgiAlgilamaSensor;                           // 4 kanallı çizgi algılayıcı için class tanımlaması
uint16_t SensorDegerleri[LINEFOLLOWER_4CH_SENSOR_COUNT];            // Sensör değerlerinin saklanacağı dizi

void setup() {
    Serial.begin(115200);                                           // Seri haberleşme başlatılması
    if (!CizgiAlgilamaSensor.begin(0x07)) {                         // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız ");                // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
        while (1);
    }

    uint16_t FwVersiyon = CizgiAlgilamaSensor.getFwVersion();       // Modül yazılım versiyonunun okunması
    Serial.print("Yazılım versiyonu: v");
    Serial.print(FwVersiyon >> 8);
    Serial.print(".");
    Serial.println(FwVersiyon & 0xFF);

    CizgiAlgilamaSensor.SetDimmingLevel(100);                       // IR LED parlaklığının ayarlanması (0-100)
    CizgiAlgilamaSensor.SetTimeout(1500);                           // Sensör zaman aşımının ayarlanması (mikrosaniye)
}

void loop() {
    if (CizgiAlgilamaSensor.Read(SensorDegerleri, LineFollower4Channel::ON)) {  // IR LED'ler açıkken sensör değerlerinin okunması
        for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
            Serial.print(i + 1);
            Serial.print(".Sensör: ");
            Serial.print(SensorDegerleri[i]);                       // Sensör değerlerinin seri port ekranına yazdırılması
            Serial.print("\t");
        }
        Serial.println();
    }
    else {
        Serial.println("Sensör değerleri okunamadı");
    }

    delay(250);
}
