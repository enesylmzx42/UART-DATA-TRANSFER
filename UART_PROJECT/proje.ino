/*
*
*
* Projenin Verici Kodları Burada Yer Almaktadır.
* Bu Proje Gomulu Sistemler Dersi icin Hazirlanmistir.
* Son Degistirilme Zamani: 30.05.2023
*
*/


#include <SD.h>
#include "getTemperatures.h"
#include "calcSpeed.h"
#include "Lora.h"

#define HALL_EFFECT_PIN 3
#define SD_CS 8

int sdFileCount = 0;
String sdFileName = "";
SdFile root;
uint32_t time = 0;


void setup() {
  Serial.begin(9600); // bilgisisayar ile haberleşme

  //SDCARD ADD TITLE
  Serial.println("SD kart baslatiliyor...");

  if (!SD.begin(SD_CS)) {
    Serial.println("SD karta baglanilamadi!");
  } else {
    Serial.println("SD karta baglanildi.");

    File root = SD.open("/");
    while (true) {
      File saveFile = root.openNextFile();
      if (!saveFile) {
        break;
      }
      String fileName = saveFile.name();
      if (fileName.startsWith("DATAS_") && fileName.endsWith(".TXT")) {
        int num = fileName.substring(6, fileName.length() - 4).toInt();
        if (num >= sdFileCount) {
          sdFileCount = num + 1;
        }
      }
      saveFile.close();
    }
    root.close();

    sdFileName = "DATAS_" + String(sdFileCount) + ".TXT";
    File file = SD.open(sdFileName, FILE_WRITE);
    if (!file)
      Serial.println("dosyaya baglanilamadi");
    file.println("zaman_ms ; hiz_kmh ; sicaklik1");
    file.close();
  }

  sensors.begin();

  //LORA INITIALIZE
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  LoRa.begin();

  LoraE22Ayarlar();

  digitalWrite(M0, LOW); //0
  digitalWrite(M1, LOW); //0

  // HALL INITIALIZE
  pinMode(HALL_EFFECT_PIN, INPUT_PULLUP);
  Timer1.initialize();                                                        // kesme varsayılan olarak 1 saniye sayar
  Timer1.attachInterrupt(speedCal);                                           // bu fonksiyon taşmadan sonra çağrılır
  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT_PIN), speedInc, RISING);  // hall effect yükselen kenarsa
  //HALL END
}

void saveSDCard() {
  File file = SD.open(sdFileName, FILE_WRITE);
  time = millis();  //çalışmaya başladığından bir itibar o anki milisaniye


  if (!file) {
    Serial.println("Dosya acilamadi!");
  } else {
    file.print(time);
    file.print(", ");
    file.print(speed);
    file.print(", ");
    file.print(temp1);
    file.print("\n");
    file.close();
  }
}

void loop() {
  getTemps();  // Sicakliklar
  Serial.print("Hiz: ");
  Serial.print(speed);
  Serial.println();
  sendLora();
  saveSDCard();
  delay(100);
}
