#define PIN_TRIG 12 // Триг пин к первому датчику
#define PIN_ECHO 11 // Эхо пин к первому датчику
#define PIN_TRIG_2 7 // Триг пин ко второму датчику
#define PIN_ECHO_2 6 // Эхо пин ко второму датчику
#define PIN_TRIG_3 2 // Триг пин к первому датчику
#define PIN_ECHO_3 3 // Эхо пин к первому датчику
#define PIN_TRIG_4 8 // Триг пин ко второму датчику
#define PIN_ECHO_4 9 // Эхо пин ко второму датчику

#define PIN_RESET_BUTTON 4 // Ресет кнопка пин
#define PIN_SERVE_BUTTON 5 // Серве кнопка пин

void setup() {
  // Инициализируем взаимодействие по последовательному порту
  Serial.begin (9600);
  while (Serial.available() <= 0){ 
    Serial.println("hello"); // отправляем начальное сообщение
  }
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_TRIG_2, OUTPUT);
  pinMode(PIN_ECHO_2, INPUT);
  pinMode(PIN_TRIG_3, OUTPUT);
  pinMode(PIN_ECHO_3, INPUT);
  pinMode(PIN_TRIG_4, OUTPUT);
  pinMode(PIN_ECHO_4, INPUT);
  
  pinMode(PIN_RESET_BUTTON, INPUT); 
  pinMode(PIN_SERVE_BUTTON, INPUT);
}

void loop() {
  if(Serial.available() > 0){
    int inByte = Serial.read();
    long duration, cm, cm_2, cm_3, cm_4; //для первого датчика
    int reset_reading = 0;	// данные кнопки сброса
    int serve_reading = 0;	// данные кнопки подаuи

    reset_reading = digitalRead(PIN_RESET_BUTTON); 
    serve_reading = digitalRead(PIN_SERVE_BUTTON);

    // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, HIGH);
    // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    //  Время задержки акустического сигнала на эхолокаторе.
    duration = pulseIn(PIN_ECHO, HIGH);
    // Теперь осталось преобразовать время в расстояние
    cm = (duration / 2) / 29.1;

    digitalWrite(PIN_TRIG_2, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG_2, LOW);
    duration = pulseIn(PIN_ECHO_2, HIGH);
    cm_2 = (duration / 2) / 29.1;
    
    digitalWrite(PIN_TRIG_3, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG_3, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG_3, LOW);
    duration = pulseIn(PIN_ECHO_3, HIGH);
    cm_3 = (duration / 2) / 29.1;
    
    digitalWrite(PIN_TRIG_4, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG_4, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG_4, LOW);
    duration = pulseIn(PIN_ECHO_4, HIGH);
    cm_4 = (duration / 2) / 29.1;

    Serial.print(cm);
    Serial.print(", ");
    Serial.print(cm_2);
    Serial.print(", ");
    Serial.print(cm_3);
    Serial.print(", ");
    Serial.print(cm_4);
    Serial.print(", ");
    Serial.print(reset_reading);
    Serial.print(", ");
    Serial.println(serve_reading);
    Serial.print('\n');

    // Задержка между измерениями для корректной работы скеча
    delay(250);
  }
}