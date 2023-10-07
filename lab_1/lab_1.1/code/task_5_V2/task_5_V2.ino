//For Arduino Uno

//Количество светодиодов
const int count_diods = 3;

int redPin[count_diods] = {6,9,12};   // инициализируем пины под красный цвет
int greenPin[count_diods] = {3,7,10}; // инициализируем пины под зеленый цвет
int bluePin[count_diods] = {5,8,11};   // инициализируем пины под синий цвет
//нужен для третьего режима, что массив был 1 пин красный из массива красных, 2 пин зеленый из массива зеленых, 3 пин синий из массива синих и тд +1 каждый
int diod_mass[count_diods][count_diods] = {{redPin[0], greenPin[1], bluePin[2]}, {redPin[1], greenPin[2], bluePin[0]}, {redPin[2], greenPin[0], bluePin[1]}};

//Нужно для того, чтобы узнать какой светодиод будет гореть после вкючения
bool r = true;
bool g = true;
bool b = true;

//определение символ которые будут отвечать за включение и выключение функций
char first_simbol = 'q'; // первая функция, установка цвета по написанию r9g0b0 (красный)
char second_simbol = 'w'; // вторая функция, герлянда с изменением цвета через 1 сек
char third_simbol = 'e'; // вторая функция, герлянда с изменением цвета через 1 сек как на новогодней ёлки, каждый светодиод светит другим цветом
int current_pin[count_diods] = {0,0,0}; // выбор цвета тегущего пина для первой функции
int brightness = 0;  // выбор яркости для current_pin в функции 1

void setup() {
    //setup code
  //слушаем клавиатуру
  Serial.begin(9600);
  //назначаем пинам режим работы
  for(int i = 0; i < count_diods; i++){
    pinMode(redPin[i], OUTPUT); 
    pinMode(greenPin[i], OUTPUT);
    pinMode(bluePin[i], OUTPUT);
  }
}

void loop() {
  //rgb loop
  //все пины выключается, сделанного для того, чтобы после выхода из функции светодиод-ы не светились
  for(int i = 0; i < count_diods; i++){
    digitalWrite(redPin[i], 0);
    digitalWrite(greenPin[i], 0);
    digitalWrite(bluePin[i], 0);
  }
  //если что-то написали в ардуино
  if(Serial.available() > 0){
    int inByte = Serial.read(); //чтение значения с клавиатуры
    //если первый написанный байт равен первому символу
    if(inByte == first_simbol){
      int inByte2 = Serial.read();
      while(inByte2 != first_simbol){
      	// реагируем только на значения r, g, b и цифры от 0 до 9
      	// игнорируем все другие значения 
        if (inByte2 == 'r') {
          //установливаем current_pin все красные
          for(int i = 0; i < count_diods; i++){
          	current_pin[i] = redPin[i];
          }
        }
        if (inByte2 == 'g') {
          for(int i = 0; i < count_diods; i++){
          	current_pin[i] = greenPin[i];
          }
        }
        if (inByte2 == 'b') {
          for(int i = 0; i < count_diods; i++){
          	current_pin[i] = bluePin[i];
          }
        }
        // сопоставляем значения входящего байта диапазону команды Analog Read()
        if (inByte2 >= '0' && inByte2 <= '9') {
          brightness = map(inByte2, '0', '9', 0, 255);
          // устанавливаем заданную яркость на выбранных пинах
          for(int i = 0; i < count_diods; i++){
          	analogWrite (current_pin[i], brightness);
          }
        }
        inByte2 = Serial.read(); //читаем чтобы узнать, когда пользователь хочет выйти цикла
      }
    }
    else if(inByte == second_simbol){
      //чтение пока вход не будет буквой char в second_simbol, светится елочкой
      while(Serial.read() != second_simbol){
        //если остановка в прошлый раз была на красном, то снова загорится красный
        if(r == 1){
          on_off_diod(redPin);
          //если нажат символ этой функции в момент этого цвета, то выходит из цикла
          if(Serial.read() == second_simbol){
            break;
          }
        }
		//если остановка в прошлый раз была на зеленом, то снова загорится зеленый
        if(g == 1){
          //чтобы при следующем включении работало с того же цвета, что и выключилось(зеленый)
          r = false;
          on_off_diod(greenPin);
          if(Serial.read() == second_simbol){
            break;
          }
        }
        //если остановка в прошлый раз была на синем, то снова загорится синий
        if(b == 1){
          r = false;
          g = false;
          on_off_diod(bluePin);
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
    else if(inByte == third_simbol){
      //нужна чтобы выйти из цикла while, если была нажата кнопка с третьим символом
      bool break_ = false;
      while(Serial.read() != third_simbol){
        for(int i = 0; i < count_diods; i++){
          //включение диодов в нужном нам порядке из массива, 1 светодиод крассный, 2 светодиод зеленый, 3 светодиод синий итд +1 в левую сторону
          on_off_diod(diod_mass[i]);
          //если хотим выйти из цикла, то выходим из цикла for, и переменную break_ делаем true чобы выйти из цикла while
          if(Serial.read() == third_simbol)
          {
            break_ = true;
            break;
          }
        }
        //выходим из цикла while
        if(break_ == true)break;
      }
    }
  }
}

//функция для включения и выключения диодов через 1 сек
void on_off_diod(int *pin){
  //включаем светодиоды
  for(int i = 0; i < count_diods; i++){
  	digitalWrite(pin[i], 1);
  }
  //секунда задержки
  delay(1000);
  //выключаем светодиоды
  for(int i = 0; i < count_diods; i++){
  	digitalWrite(pin[i], 0);
  }
}