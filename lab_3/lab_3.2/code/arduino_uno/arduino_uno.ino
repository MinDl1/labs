#include <LiquidCrystal_I2C.h>
#include <GyverMAX7219.h>

char stringToMorseCode[] = "";
int audio8 = 8;            // к контакту 8 подключен зуммер
int note = 1200;           // music note/pitch (используемый тон)
int dotLen = 100;          // length of the morse code 'dot' (длительность звучания точки)
int dashLen = dotLen * 3;  // length of the morse code 'dash' (длительность звучания тире)

MAX7219 < 1, 1, 5 > mtrx;   // одна матрица (8х8), пин CS на D5

LiquidCrystal_I2C lcd(0x27,16,2); // Задаем адрес и размерность дисплея

void setup() {
  Serial.begin(9600);

  lcd.init(); // Инициализация lcd
  lcd.backlight(); // Включаем подсветку

  pinMode(audio8, OUTPUT);
  mtrx.begin();       // запускаем
  mtrx.setBright(5);  // яркость 0..15
  mtrx.clear();
}
void loop() {
  char inChar = 0;
  String inData = "";  // data length of 6 characters
  String variable = "";
  String variable1 = "";
  int index1 = 0;

  if (Serial.available() > 0) {                     // если в последовательном порту есть принятые данные
    while (Serial.available() > 0 && index1 < 100)  // read till 6th character
    {
      inData = Serial.readString();
    }

    lcd.clear();
    lcd.setCursor(0, 0); // Устанавливаем курсор в начало 1 строки
    lcd.print(inData);
    Serial.println(inData);

    variable.toUpperCase();  // преобразуем нижний регистр в верхний
    for (byte i = 0; i < 100; i++) {
      variable.concat(String(inData[i]));  // объединяем строки
    }
    delay(20);
  }
  String stringToMorseCode = String(variable);
  for (int i = 0; i < sizeof(stringToMorseCode) - 1; i++) {
    char tmpChar = stringToMorseCode[i];
    tmpChar = toLowerCase(tmpChar);
    GetChar(tmpChar);
  }
}
void MorseDot() {
  tone(audio8, note, dotLen);  // start playing a tone
  mtrx.circle(4, 4, 8, GFX_FILL); // х, у, радиус, заливка
  mtrx.update();
  delay(dotLen);               // hold in this position
  mtrx.clear();
}
void MorseDash() {
  tone(audio8, note, dashLen);  // start playing a tone
  mtrx.circle(4, 4, 8, GFX_FILL); // х, у, радиус, заливка
  mtrx.update();
  delay(dashLen);               // hold in this position
  mtrx.clear();
}
void GetChar(char tmpChar) {
  switch (tmpChar) {
    case 'a':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'b':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'c':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'd':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'e':
      MorseDot();
      delay(100);
      break;
    case 'f':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'g':
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'h':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'i':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'j':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'k':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'l':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'm':
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'n':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'o':
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'p':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 'q':
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'r':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 's':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    case 't':
      MorseDash();
      delay(100);
      break;
    case 'u':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'v':
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'w':
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'x':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'y':
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      break;
    case 'z':
      MorseDash();
      delay(100);
      MorseDash();
      delay(100);
      MorseDot();
      delay(100);
      MorseDot();
      delay(100);
      break;
    default:
      break;
  }
}