#include <AFMotor.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h" 

AF_DCMotor motorX(1);
AF_DCMotor motorY(2);
AF_DCMotor motorZ(3);
AF_DCMotor motorD(4);

const int btnXPin = 5; // Pin untuk tombol kontrol sumbu X
const int btnYPin = 6; // Pin untuk tombol kontrol sumbu Y
const int btnZPin = 7; // Pin untuk tombol kontrol sumbu Z
const int btnDPin = 8; // Pin untuk tombol kontrol sumbu D
const int btnResetPin = 9; // Pin untuk tombol reset
const int btnSafetyPin = 10; // Pin untuk tombol keselamatan

const int encoderPin = 2; // Pin encoder untuk mengukur RPM
const unsigned long interval = 1000; // Interval untuk menghitung RPM (ms)

volatile unsigned long pulseCount = 0;
unsigned long lastCount = 0;
unsigned long rpm = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD dengan alamat I2C 0x27

const int speakerPin = 11; // Pin speaker
const int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4}; // Melodi saat RPM 0
const int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4}; // Durasi nada

void setup() {
  // Pembersihan jalur saat pertama kali dinyalakan
  cleanPath();
  
  // Setup pin dan interrupt
  pinMode(encoderPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPin), countPulse, RISING); // Menghubungkan fungsi countPulse() dengan interrupt
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menyalakan backlight LCD
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  pinMode(speakerPin, OUTPUT); // Inisialisasi speaker sebagai output
  pinMode(btnResetPin, INPUT_PULLUP); // Inisialisasi tombol reset
  pinMode(btnSafetyPin, INPUT_PULLUP); // Inisialisasi tombol keselamatan
}

void loop() {
  // Membaca status tombol dan menggerakkan motor sesuai tombol yang ditekan
  if (digitalRead(btnXPin) == LOW) {
    motorX.setSpeed(255);
    motorX.run(FORWARD);
  } else {
    motorX.run(RELEASE);
  }

  if (digitalRead(btnYPin) == LOW) {
    motorY.setSpeed(255);
    motorY.run(FORWARD);
  } else {
    motorY.run(RELEASE);
  }

  if (digitalRead(btnZPin) == LOW) {
    motorZ.setSpeed(255);
    motorZ.run(FORWARD);
  } else {
    motorZ.run(RELEASE);
  }

  if (digitalRead(btnDPin) == LOW) {
    motorD.setSpeed(255);
    motorD.run(FORWARD);
  } else {
    motorD.run(RELEASE);
  }

  // Mengecek status tombol reset
  if (digitalRead(btnResetPin) == LOW) {
    resetMotors(); 
  }

 
  if (digitalRead(btnSafetyPin) == LOW) {
    stopMotors();
  }

 
  if (millis() - lastCount >= interval) {
    detachInterrupt(digitalPinToInterrupt(encoderPin)); // Menonaktifkan interrupt sementara
    rpm = (pulseCount - lastCount) * (60000 / interval); // Menghitung RPM
    lastCount = pulseCount;
    pulseCount = 0;
    lcd.setCursor(5, 0);
    lcd.print("    "); // Membersihkan tampilan sebelum menampilkan nilai baru
    lcd.setCursor(5, 0);
    lcd.print(rpm); // Menampilkan nilai RPM pada LCD
    attachInterrupt(digitalPinToInterrupt(encoderPin), countPulse, RISING); // Mengaktifkan kembali interrupt

    
    if (rpm == 0) {
      playMelody();
    }
  }
}


void countPulse() {
  pulseCount++;
}


void playMelody() {
  for (int i = 0; i < 8; i++) {
    int duration = 1000 / noteDurations[i];
    tone(speakerPin, melody[i], duration);
    delay(duration * 1.1);
    noTone(speakerPin);
    delay(50);
  }
}


void resetMotors() {
  motorX.setSpeed(70); // Kecepatan 70 RPM
  motorY.setSpeed(70); // Kecepatan 70 RPM
  motorZ.setSpeed(70); // Kecepatan 70 RPM
  motorD.setSpeed(70); // Kecepatan 70 RPM
  

  motorX.run(BACKWARD);
  motorY.run(BACKWARD);
  motorZ.run(BACKWARD);
  motorD.run(BACKWARD);


  

  motorX.run(RELEASE);
  motorY.run(RELEASE);
  motorZ.run(RELEASE);
  motorD.run(RELEASE);
}


void stopMotors() {
  motorX.run(RELEASE);
  motorY.run(RELEASE);
  motorZ.run(RELEASE);
  motorD.run(RELEASE);
}


void cleanPath() {
  motorX.setSpeed(70); // Kecepatan 70 RPM
  motorY.setSpeed(70); // Kecepatan 70 RPM
  motorZ.setSpeed(70); // Kecepatan 70 RPM
  motorD.setSpeed(70); // Kecepatan 70 RPM
  

  motorX.run(BACKWARD);
  motorY.run(BACKWARD);
  motorZ.run(BACKWARD);
  motorD.run(BACKWARD);

  delay(5000); 
  
  
  motorX.run(RELEASE);
  motorY.run(RELEASE);
  motorZ.run(RELEASE);
  motorD.run(RELEASE);
}
