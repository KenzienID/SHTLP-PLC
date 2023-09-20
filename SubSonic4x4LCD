#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4; // Jumlah baris pada keypad
const byte COLS = 4; // Jumlah kolom pada keypad

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Sambungan baris ke pin 9-6
byte colPins[COLS] = {5, 4, 3, 2}; // Sambungan kolom ke pin 5-2

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int seconds = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
}

void loop()
{
  char key = keypad.getKey(); // Mendapatkan tombol yang ditekan pada keypad

  if (key)
  {
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Button Pressed:");
    lcd_1.setCursor(0, 1);
    lcd_1.print(key);

    delay(1000); // Tahan selama 1 detik sebelum membersihkan layar
  }
  
}
