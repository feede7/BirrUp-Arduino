#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
#define LED_PIN 14
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Iniciamos la comunicación  serial
  SPI.begin();          // Iniciamos el Bus SPI
  mfrc522.PCD_Init();   // Iniciamos  el MFRC522
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,HIGH);
  Serial.println("Lectura del UID");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (mfrc522.PICC_IsNewCardPresent()) {
    //Seleccionamos una tarjeta
    digitalWrite(LED_PIN,LOW);
    if (mfrc522.PICC_ReadCardSerial()) {
      // Enviamos serialemente su UID
      Serial.print("Card UID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);   
      } 
      Serial.println();
      // Terminamos la lectura de la tarjeta  actual
      mfrc522.PICC_HaltA();         
    }      
  } else digitalWrite(LED_PIN,HIGH);
}
