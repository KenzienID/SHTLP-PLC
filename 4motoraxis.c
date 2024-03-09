#include <AFMotor.h>

AF_DCMotor motorX(1);
AF_DCMotor motorY(2);
AF_DCMotor motorZ(3);
AF_DCMotor motorD(4);

const int btnXPin = 5; // Pin untuk tombol kontrol sumbu X
const int btnYPin = 6; // Pin untuk tombol kontrol sumbu Y
const int btnZPin = 7; // Pin untuk tombol kontrol sumbu Z
const int btnDPin = 8; // Pin untuk tombol kontrol sumbu D

void setup() {
  // Inisialisasi pin sebagai input untuk tombol
  pinMode(btnXPin, INPUT_PULLUP);
  pinMode(btnYPin, INPUT_PULLUP);
  pinMode(btnZPin, INPUT_PULLUP);
  pinMode(btnDPin, INPUT_PULLUP);
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
}
