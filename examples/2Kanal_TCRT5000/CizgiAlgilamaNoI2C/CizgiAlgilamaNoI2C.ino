/*
 *   I2C haberleşme protokolü kullanılmadan Çizgi Algılama örneği (2 Kanal - TCRT5000),
 *   Bu örnekte temel konfigürasyon ayarları yapılmaktadır.
 *   Birinci sensörden gelen çizgi algılama durumu ve değerini seri port ekranına yazdırmaktadır.
 *
 *   ---> UYARI: Çizgileri siyah(elektrik) bant ile yapınız.  <--------
 *   ---> UYARI: Algılayıcı kartınızı 2.5cm'den yukarıda konumlandırMAyınız. <--------
 *
 *   Bu algılayıcı I2C haberleşme protokolü ile çalışmaktadır.
 *   Bu örnek I2C haberleşme protokolü kullanılmadan, modül üzerindeki A1 ve D1 pinleri ile yazılmıştır.
 *
 *   Bu örnek TCRT5000 sensörlü Deneyap Çift Kanallı Çizgi Algılayıcı için oluşturulmuştur
 *      ------> https://docs.deneyapkart.org/tr/content/contentDetail/deneyap-modul-deneyap-cift-kanall-cizgi-alglayc-m1 <------
 *      ------> https://github.com/deneyapkart/deneyap-cift-kanalli-cizgi-algilayici-arduino-library <------
*/
#define DOUTPIN D0                                   // Çizgi Algılayıcı kartındaki D1 pini D0 pinine bağlanmalıdır
#define AOUTPIN A0                                   // Çizgi Algılayıcı kartındaki A1 pini A0 pinine bağlanmalıdır

void setup() {
    Serial.begin(115200);                            // Seri haberleşme başlatılması
    pinMode(DOUTPIN, INPUT);                         // Dijital pinin giriş olarak ayarlanması
}

void loop() {
    bool Sensor1Durum = digitalRead(DOUTPIN);        // 1.sensörün durumu okunması
    Serial.print("1.Sensör Durumu: ");
    Serial.print(Sensor1Durum);                      // 1.sensörün durumu seri port ekranına yazdırılması

    uint16_t Sensor1Deger = analogRead(AOUTPIN);     // 1.sensörün değerinin okunması
    Serial.print("\t1.Sensör Değeri: ");
    Serial.println(Sensor1Deger);                    // 1.sensörün verisi seri port ekranına yazdırılması

    delay(10);
}
