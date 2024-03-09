#include <AFMotor.h>
#include <LiquidCrystal_I2C.h>

AF_DCMotor motorX(1);
AF_DCMotor motorY(2);
AF_DCMotor motorZ(3);
AF_DCMotor motorD(4);

const int btnXPin = 5; // Pin untuk tombol kontrol sumbu X
const int btnYPin = 6; // Pin untuk tombol kontrol sumbu Y
const int btnZPin = 7; // Pin untuk tombol kontrol sumbu Z
const int btnDPin = 8; // Pin untuk tombol kontrol sumbu D

const int encoderPin = 2; // Pin encoder untuk mengukur RPM
const unsigned long interval = 1000; // Interval untuk menghitung RPM (ms)

volatile unsigned long pulseCount = 0;
unsigned long lastCount = 0;
unsigned long rpm = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD dengan alamat I2C 0x27

void setup() {
  pinMode(encoderPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPin), countPulse, RISING); // Menghubungkan fungsi countPulse() dengan interrupt
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Menyalakan backlight LCD
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
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

  // Menghitung RPM setiap interval
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
  }
}

// Fungsi untuk menghitung pulsa encoder
void countPulse() {
  pulseCount++;
}
