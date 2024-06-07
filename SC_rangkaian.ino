#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//relay
const int relayPin = 3;

// Pin sensor jarak
#define trigPin 9
#define echoPin 8
long durasi;
int jarak = 0;

// Pin sensor suhu
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int derajat;

// Pin sensor cahaya
int ldr = A1;

//Pin LED
int led = 3;

void setup() {
  pinMode(relayPin, OUTPUT); 
  digitalWrite(relayPin, HIGH);  
  lcd.backlight();
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.init();
  int positionCounter;
  lcd.begin(16, 2); 
  lcd.clear();

  // Inisialisasi pin
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldr, INPUT);

  // Inisialisasi DHT
  dht.begin();

  delay(4000);
}

void loop() {
  // Sensor suhu
  int baselineTemp = 29;
  derajat = dht.readTemperature();  // Membaca suhu dalam derajat Celsius

  lcd.setCursor(0, 1);
  lcd.print("Suhu = ");
  lcd.print(derajat);
  lcd.print("C");
  delay(1000);
  
  // Sensor jarak
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = durasi * 0.034 / 2;

  lcd.setCursor(0, 0);
  lcd.print("Jarak = ");
  lcd.print(jarak);
  lcd.print("cm");
  delay(1000);
  
  // Sensor cahaya
  int ldrStatus = analogRead(ldr);

  //Penentuan apakah ruang tersebut ideal
  if (derajat < baselineTemp && jarak >= 5 && ldrStatus >= 5) {
    digitalWrite(led, HIGH); 
    Serial.print("Ruangan Cocok Dijadikan Ruang Belajar !!\n");
  }
  else {
    digitalWrite(led, LOW);
    Serial.print("Ruangan Tidak Cocok Dijadikan Ruang Belajar !!\n");
  }
delay(1000);
}