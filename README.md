# Data_Transfer_Using_UART
Bu projede temelde UART iletişim protokolünün impelementasyonu arduino kullanılarak örnek bir projeyle ortaya koyulmuştur.

## Projede Kullanılan Sensörler ve Mikrodenetleyiciler
```
- DALLAS18B20
- KY-003 HALL EFFECT SENSOR
- LoRa 400T30D
- SD CARD MODULE
- Arduino Mega 2560
- Arduino Uno
```

## Proje Tanıtımı
Proje temelde alıcı ve verici devrelerinden oluşmaktadır. Tüm sensör ve modüller verici devresine bağlıdır. Projede sıcaklık okuma, manyetik alandan faydalanarak hız okuma, okunan verileri bir sd karta kaydetme ve verileri uzak bir mikrodenetleyici gönderme operasyonları kurgulanmıştır.

### Sıcaklık Okumak
![sicaklik](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/bbfcfec5-0db7-4fc0-bfbb-26b5d0fc4d0b)
<br/>
<br/>
`getTemperatures.h` isimli oluşturulan kütüphanede sıcaklık okuma işlemleri DALLAS18B20 modülü kullanılarak gerçekleştirilmektedir. Sıcaklık değerini okumak işlemi asıl proje dosyasının loop kısmında `getTemps()` fonksiyonu çağırılarak gerçekleştirilir. Modül ile arduino arasında veri akışı UART ile sağlanmıştır.
<br/>
<br/>

### Manyetik Alan Kullanarak Hız Hesaplamak
![hiz](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/164e8748-e3ec-4018-831e-4dde74b4d6f1)
<br/>
<br/>
Modül tarafından her manyetik alan algılandığında bir interrupt oluşturulur ve sayac değeri 1 arttırılır. Her geçen bir saniyenin sonunda yine bir interrupt oluşturulur ve sayac değerine bakılarak yazılan algoritmayla hız hesaplaması yapılır. Modül ile arduino arasında veri akışı UART ile sağlanmıştır.
<br/>
<br/>

### Verileri SD Card Modülüne Kaydetmek
Proje ana dosyasında setup kısmının SD kart ile ilgili olan bölümünde SD kart ile bağlantı kurulmaya çalışılır. Bağlantı kurulduktan sonra daha önceden belirlenen dosya ismi kart içerisinde aranır ve kaç adet bu dosyadan olduğu tespit edilir. Yeni oluşturulacak veri kayıtları için yeni bir dosya adı belirlenir. Loop kısmında `saveSDCard()` fonksiyonu çağırılarak gelen veriler belirlenen desene göre kart içerisine yazılır. Modül ile arduino arasında veri akışı UART ile sağlanmıştır.
<br/>
<br/>

### Verileri Uzak Mikrodenetleyiciye Göndermek
`LoRa 400T30D` haberleşme modülü kullanılarak belirlenen adres ve kanala veri gönderme işlemi gerçekleştiriliyor. Gönderme işlemleri `Lora.h` kütüphanesinde yapılmaktadır. Gönderilmek istenen veriler bir struct yapısına `initValues()` fonksiyonuyla gömülür. `sendLora()` fonksiyonu çalıştırılarak gönderme işlemi başlatılır. Alıcı kısmında aynı struct yapısı korunarak veriler karşılanmalıdır.
<br/>
![lora](https://github.com/0mustafa/Data_Transfer_Using_UART/assets/78226423/b0325217-9b29-42ab-be40-7dcb1b72070b)

