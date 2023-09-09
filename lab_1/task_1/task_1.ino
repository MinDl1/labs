//For Arduino Uno
//пины
//красный пин 6
#define R_PIN 6
//зелёный пин 3
#define G_PIN 3
//синий пин 5
#define B_PIN 5

void setup() {
  //setup code
  //назначаем пинам режим работы
  pinMode(R_PIN, OUTPUT); 
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  //rgb loop with time delay 1
  on_off_diod(R_PIN);
  on_off_diod(G_PIN);
  on_off_diod(B_PIN);
}

//функция для включения и выключения диода через 1 сек
void on_off_diod(int pin){
  //включаем светодиод
  digitalWrite(pin, 1);
  //секунда задержки
  delay(1000);
  //выключаем светодиод
  digitalWrite(pin, 0);
}