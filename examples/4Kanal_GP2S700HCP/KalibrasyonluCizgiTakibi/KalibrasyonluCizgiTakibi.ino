/*
 *   Kalibrasyonlu Çizgi Takibi örneği (4 Kanal - GP2S700HCP),
 *   Bu örnekte sensörler kalibre edildikten sonra çizginin konumu hesaplanmaktadır.
 *   Kalibre edilmiş sensör değerleri (0-1000) ve çizgi konumu seri port ekranına yazdırılmaktadır.
 *
 *   KALİBRASYON NEDİR?
 *   Her sensör beyaz zemini ve siyah çizgiyi ortamın ışığına ve yüzeye göre farklı değerlerle görür.
 *   Kalibrasyon sırasında her sensörün gördüğü en açık (beyaz) ve en koyu (siyah) değer kaydedilir.
 *   Sonrasında okunan değerler bu aralığa göre 0 (beyaz) ile 1000 (siyah) arasına ölçeklenir.
 *
 *   YAPILMASI GEREKENLER (adım adım):
 *   1. Beyaz bir zemin üzerine siyah elektrik bandı ile bir çizgi yapıştırınız.
 *   2. Algılayıcıyı karta I2C kablosu ile bağlayınız ve bu örneği karta yükleyiniz.
 *   3. Seri port ekranını 115200 baud ile açınız ve kartın RESET butonuna basınız.
 *   4. "Algılayıcıyı çizginin üzerine tutunuz" yazısını görünce algılayıcıyı, sensörler aşağı bakacak
 *      şekilde çizginin üzerine yerleştiriniz. Algılayıcıyı zeminden 3-5 mm yükseklikte tutunuz.
 *      ÖNEMLİ: Yükseklik kalibrasyon ve kullanım sırasında aynı kalmalıdır. Algılayıcıyı elde tutmak yerine
 *      robota takmanız ya da altına 3-5 mm'lik bir parça koyup zemin üzerinde kaydırmanız önerilir.
 *   5. Geri sayım bitip dahili LED yandığında algılayıcıyı 10 saniye boyunca çizgiye dik yönde
 *      sağa sola yavaşça gezdiriniz. Her 4 sensör de hem beyaz zeminin hem siyah çizginin üzerinden geçmelidir.
 *      (Algılayıcı robota takılıysa robotu çizginin üzerinde kendi ekseni etrafında sağa sola döndürebilirsiniz.)
 *   6. LED söndüğünde kalibrasyon biter ve her sensörün en küçük (beyaz) ve en büyük (siyah) değeri yazdırılır.
 *      Çizgiyi göremeyen sensör için uyarı çıkarsa RESET butonuna basıp kalibrasyonu tekrarlayınız.
 *   7. Algılayıcıyı çizginin üzerinde yavaşça kaydırınız ve seri port ekranındaki değerleri kontrol ediniz.
 *   Kalibrasyon değerleri kalıcı olarak saklanmaz, kart her başladığında kalibrasyon tekrar yapılır.
 *   Ortamın ışığı ya da zemin değişirse kalibrasyonu tekrarlayınız.
 *
 *   BEKLENEN DEĞERLER:
 *   Kalibre edilmiş sensör değerleri: 0 --> beyaz zemin, 1000 --> siyah çizgi
 *   Çizgi konumu:    0 --> çizgi 1. sensörün altında
 *                 1000 --> çizgi 2. sensörün altında
 *                 2000 --> çizgi 3. sensörün altında
 *                 3000 --> çizgi 4. sensörün altında
 *   - Çizgi 1. sensörden 4. sensöre kaydırıldığında konum 0'dan 3000'e düzgünce artmalıdır.
 *   - Bant tüm sensörleri kapatıyorsa 4 değer de 1000 olur ve konum 1500 (orta) okunur.
 *   - Çizgi görülmüyorsa (tamamen beyaz zemin) konum, çizginin en son görüldüğü tarafa göre 0 ya da 3000 olur.
 *   - Beyaz zeminde değerler 0'a inmiyorsa algılayıcının yüksekliği kalibrasyondakinden farklıdır;
 *     yüksekliği sabitleyip kalibrasyonu tekrarlayınız.
 *
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *
 *   Bu örnek GP2S700HCP sensörlü Deneyap Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#include <Deneyap_CiftKanalliCizgiAlgilama.h>                       // Deneyap Çizgi Algılayıcı kütüphanesinin eklenmesi

#define KALIBRASYON_SURESI 10000                                    // Kalibrasyon süresi (milisaniye)
#define MIN_KALIBRASYON_FARKI 100                                   // Sensörün çizgiyi gördüğünü kabul etmek için en küçük/en büyük değer farkı

LineFollower4Channel CizgiAlgilamaSensor;                           // 4 kanallı çizgi algılayıcı için class tanımlaması
uint16_t SensorDegerleri[LINEFOLLOWER_4CH_SENSOR_COUNT];            // Sensör değerlerinin saklanacağı dizi

void setup() {
    Serial.begin(115200);                                           // Seri haberleşme başlatılması
    if (!CizgiAlgilamaSensor.begin(0x07)) {                         // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız ");                // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
        while (1);
    }

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("Algılayıcıyı çizginin üzerine tutunuz.");       // Kalibrasyon öncesi kullanıcının hazırlanması
    for (uint8_t i = 3; i > 0; i--) {
        Serial.print("Kalibrasyon ");
        Serial.print(i);
        Serial.println(" saniye sonra başlayacak...");
        delay(1000);
    }

    digitalWrite(LED_BUILTIN, HIGH);                                // Kalibrasyon süresince dahili LED'in yakılması
    Serial.println("Kalibrasyon başladı, algılayıcıyı çizginin üzerinde sağa sola gezdiriniz...");

    unsigned long baslangicZamani = millis();
    uint8_t sonYuzde = 0;
    while (millis() - baslangicZamani < KALIBRASYON_SURESI) {       // Kalibrasyon yapılması
        CizgiAlgilamaSensor.Calibrate();

        uint8_t yuzde = (millis() - baslangicZamani) * 100 / KALIBRASYON_SURESI;
        if (yuzde >= sonYuzde + 20) {                               // İlerlemenin %20 adımlarla yazdırılması
            sonYuzde = yuzde - yuzde % 20;
            Serial.print("%");
            Serial.println(sonYuzde);
        }
    }

    digitalWrite(LED_BUILTIN, LOW);                                 // Kalibrasyon bitince dahili LED'in söndürülmesi
    Serial.println("Kalibrasyon tamamlandı");

    Serial.println("Sensör\tEn küçük (beyaz)\tEn büyük (siyah)");   // Kalibrasyonda ölçülen değerlerin yazdırılması
    bool kalibrasyonBasarili = true;
    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {
        uint16_t enKucuk = CizgiAlgilamaSensor.calibrationOn.minimum[i];
        uint16_t enBuyuk = CizgiAlgilamaSensor.calibrationOn.maximum[i];
        Serial.print(i + 1);
        Serial.print("\t");
        Serial.print(enKucuk);
        Serial.print("\t\t\t");
        Serial.println(enBuyuk);

        if (enBuyuk < enKucuk + MIN_KALIBRASYON_FARKI) {            // Beyaz ve siyah arasında fark yoksa sensör çizgiyi görmemiştir
            Serial.print("UYARI: ");
            Serial.print(i + 1);
            Serial.println(". sensör çizgiyi görmedi.");
            kalibrasyonBasarili = false;
        }
    }

    if (!kalibrasyonBasarili) {
        Serial.println("RESET butonuna basıp kalibrasyonu tekrarlayınız.");
        Serial.println("Algılayıcıyı daha geniş sağa sola gezdiriniz ve zemine 3-5 mm yükseklikte tutunuz.");
    }
    delay(2000);
}

void loop() {
    uint16_t CizgiKonumu = CizgiAlgilamaSensor.ReadLineBlack(SensorDegerleri);  // Siyah çizginin konumunun okunması
                                                                                // (Beyaz çizgi için ReadLineWhite fonksiyonu kullanılmalıdır)

    for (uint8_t i = 0; i < LINEFOLLOWER_4CH_SENSOR_COUNT; i++) {  // Kalibre edilmiş sensör değerlerinin yazdırılması (0-1000)
        Serial.print(SensorDegerleri[i]);
        Serial.print("\t");
    }
    Serial.print("Çizgi Konumu: ");
    Serial.println(CizgiKonumu);                                    // Çizgi konumunun seri port ekranına yazdırılması

    delay(250);
}
