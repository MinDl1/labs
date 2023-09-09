//For Arduino Uno
//пины
//красный пин 6 для первого светодиода справа
#define R_PIN 6
//зелёный пин 3 для первого светодиода справа
#define G_PIN 3
//синий пин 5 для первого светодиода справа
#define B_PIN 5

//Нужно для того, чтобы узнать какой светодиод будет гореть после вкючения
bool r = true;
bool g = true;
bool b = true;

//определение символ которые будут отвечать за включение и выключение функций
char first_simbol = 'q'; // первая функция, установка цвета по написанию r9g0b0 (красный)
char second_simbol = 'w'; // вторая функция, герлянда с изменением цвета через 1 сек
//char third_simbol = 'e';
int current_pin = 0; // выбор цвета тегущего пина для первой функции
int brightness = 0;  // выбор яркости для current_pin в функции 1

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
  //rgb loop
  //все пины выключается, сделанного для того, чтобы после выхода из функции светодиод-ы не светились
  digitalWrite(R_PIN, 0);
  digitalWrite(G_PIN, 0);
  digitalWrite(B_PIN, 0);
  //если что-то написали ардуино
  if(Serial.available() > 0){
    int inByte = Serial.read(); //чтение значения с клавиатуры
    //если первый написанный байт равен первому символу
    if(inByte == first_simbol){
      int inByte2 = Serial.read();
      while(inByte2 != first_simbol){
      	// реагируем только на значения r, g, b и цифры от 0 до 9
      	// игнорируем все другие значения 
        if (inByte2 == 'r') {
          current_pin = R_PIN;
        }
        if (inByte2 == 'g') {
          current_pin = G_PIN;
        }
        if (inByte2 == 'b') {
          current_pin = B_PIN;
        }
        // сопоставляем значения входящего байта диапазону команды Analog Read()
        if (inByte2 >= '0' && inByte2 <= '9') {
          brightness = map(inByte2, '0', '9', 0, 255);
          // устанавливаем заданную яркость на выбранном пине  
          analogWrite (current_pin, brightness);
        }
        inByte2 = Serial.read(); //читаем чтобы узнать, когда пользователь хочет выйти цикла
      }
    }
    else if(inByte == second_simbol){
      //чтение пока вход не будет буквой char в second_simbol, светится елочкой
      while(Serial.read() != second_simbol){
        //если остановка в прошлый раз была на красном, то снова загорится красный
        if(r == 1){
          on_off_diod(R_PIN);
          //если нажат символ этой функции в момент этого цвета, то выходит из цикла
          if(Serial.read() == second_simbol){
            break;
          }
        }
		//если остановка в прошлый раз была на зеленом, то снова загорится зеленый
        if(g == 1){
          //чтобы при следующем включении работало с того же цвета, что и выключилось(зеленый)
          r = false;
          on_off_diod(G_PIN);
          if(Serial.read() == second_simbol){
            break;
          }
        }
        //если остановка в прошлый раз была на синем, то снова загорится синий
        if(b == 1){
          r = false;
          g = false;
          on_off_diod(B_PIN);
          if(Serial.read() == second_simbol){
            break;
          }
        }
        //чтобы в следующем круге все цвета горели
        r = true;
        g = true;
        b = true;
      }
    }
    /*else if(inByte == third_simbol){
      
    }*/
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