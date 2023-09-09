///For Arduino Uno
//пины
#define R_PIN 6
#define G_PIN 3
#define B_PIN 5

//Нужно для того, чтобы узнать какой светодиод будет гореть после вкючения
bool r = true;
bool g = true;
bool b = true;

void setup() {
  //setup code
  //слушаем клавиатуру
  Serial.begin(9600);
  //назначаем пинам режим работы
  pinMode(R_PIN, OUTPUT); 
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  //rgb loop with time delay 1 if u write g
  if(Serial.available() > 0){
    int inByte = Serial.read(); //чтение значения с клавиатуры
    if(inByte == 'g'){
      //чтение пока вход не будет буквой "g", светится елочкой
      while(Serial.read() != 'g'){
        if(r == 1){
          on_off_diod(R_PIN);
          //если g нажата в момент этого цвета, то выходит из цикла
          if(Serial.read() == 'g'){
            break;
          }
        }

        if(g == 1){
          //чтобы при следующем включении работало с того же цвета, что и выключилось
          r = false;
          on_off_diod(G_PIN);
          if(Serial.read() == 'g'){
            break;
          }
        }
        
        if(b == 1){
          r = false;
          g = false;
          on_off_diod(B_PIN);
          if(Serial.read() == 'g'){
            break;
          }
        }
        r = true;
        g = true;
        b = true;
      }
    }
  }
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