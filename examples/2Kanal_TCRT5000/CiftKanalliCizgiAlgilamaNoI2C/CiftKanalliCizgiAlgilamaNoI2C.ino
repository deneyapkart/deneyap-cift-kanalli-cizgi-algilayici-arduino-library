/*
 *   I2C haberleşme protokolü kullanılmadan Çift Kanallı Çizgi Algılama örneği (2 Kanal - TCRT5000),
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   İki sensörden gelen çizgi algılama durumları ve değerleri seri port ekranına yazdırmaktadır.
 *
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *   ---> UYARI: Algılayıcı kartınızı 2.5cm'den yukarıda konumlandırMAyınız. <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *   Bu örnek I2C haberleşme protokolü kullanılmadan, modül üzerindeki A1, A2, D1 ve D2 pinleri ile yazılmıştır.
 *
 *   Bu örnek TCRT5000 sensörlü Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1 <------
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#define DOUTPIN1 D0                                  // Çizgi Algılayıcı kartındaki D1 pini D0 pinine bağlanmalıdır
#define AOUTPIN1 A0                                  // Çizgi Algılayıcı kartındaki A1 pini A0 pinine bağlanmalıdır
#define DOUTPIN2 D1                                  // Çizgi Algılayıcı kartındaki D2 pini D1 pinine bağlanmalıdır
#define AOUTPIN2 A1                                  // Çizgi Algılayıcı kartındaki A2 pini A1 pinine bağlanmalıdır

void setup() {
    Serial.begin(115200);                            // Seri haberleşme başlatılması
    pinMode(DOUTPIN1, INPUT);                        // Dijital pinlerin giriş olarak ayarlanması
    pinMode(DOUTPIN2, INPUT);
}

void loop() {
    bool Sensor1Durum = digitalRead(DOUTPIN1);       // 1.sensörün durumu okunması
    Serial.print("\n1.Sensör Durumu: ");
    Serial.print(Sensor1Durum);                      // 1.sensörün durumu seri port ekranına yazdırılması

    uint16_t Sensor1Deger = analogRead(AOUTPIN1);    // 1.sensörün değerinin okunması
    Serial.print("\t1.Sensör Değeri: ");
    Serial.println(Sensor1Deger);                    // 1.sensörün verisi seri port ekranına yazdırılması

    delay(100);

    bool Sensor2Durum = digitalRead(DOUTPIN2);       // 2.sensörün durumu okunması
    Serial.print("2.Sensör Durumu: ");
    Serial.print(Sensor2Durum);                      // 2.sensörün durumu seri port ekranına yazdırılması

    uint16_t Sensor2Deger = analogRead(AOUTPIN2);    // 2.sensörün değerinin okunması
    Serial.print("\t2.Sensör Değeri: ");
    Serial.println(Sensor2Deger);                    // 2.sensörün verisi seri port ekranına yazdırılması

    delay(100);
}
