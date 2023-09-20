#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>

#define LED_PIN_A0  A0
#define LED_PIN_A1  A1
#define LED_PIN_A2  A2
#define LED_PIN_A3  A3
#define LED_PIN_A4  A4
#define LED_PIN_A5  A5

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','*'},
  {'4','5','6','#'},
  {'7','8','9','0'},
  {'A','B','C','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Adafruit_7segment led_display1 = Adafruit_7segment();

int ledPins[] = {LED_PIN_A0, LED_PIN_A1, LED_PIN_A2, LED_PIN_A3, LED_PIN_A4, LED_PIN_A5};
int ledStates[] = {LOW, LOW, LOW, LOW, LOW, LOW};

void setup()
{
  for (int i = 0; i < 6; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], ledStates[i]);
  }
  
  led_display1.begin(112);

  led_display1.println("----");
  led_display1.writeDisplay();
}

void loop()
{
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    if (key >= '1' && key <= '5') {
      int ledIndex = key - '1';

      if (ledIndex >= 0 && ledIndex < 6) {
        ledStates[ledIndex] = !ledStates[ledIndex];
        digitalWrite(ledPins[ledIndex], ledStates[ledIndex]);
      }
    }

    led_display1.println(key);
    led_display1.writeDisplay();
  }
  
  delay(10); // Delay a little bit to improve performance
}
