# Laboratory works

## About project

Labs is a project based on different hardware and software.  
The project is made possible by [MinDl](https://github.com/MinDl1), [Gryn69](https://github.com/Gryn69), [Goremika26](https://github.com/Goremika26) who've generously donated dozens of hours in code development and upkeep.

<details>
<summary>Laboratory 1.1</summary>

# Lab_1.1

Lab_1.1 is a project based on Arduino that allows you to control the brightness of a three-color LED from the keyboard.

Lab_1.1 source code is made available on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

## Documentation

### Narrative documentation:

- Our [lab_1.1 docs](/lab_1/lab_1.1/docs/)

### Hardware and Software:

#### Hardware:

##### Minimum kit(to complete task_0 - task_2 one by one): 

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- RGB LED - 1
- Wires Male-Male - 4
- 220 Ohm resistor- 1

![lab_1.1 Minimum kit for Project](/lab_1/lab_1.1/images/Minimum_kit.png)

##### Maximum kit(to complete all tasks one by one):

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- RGB LED - 3
- Wires Male-Male - 19
- 220 Ohm resistor - 3
- Slider switches - 6

![lab_1.1 Maximum kit for Project](/lab_1/lab_1.1/images/Maximum_kit.png)

##### Base scheme for Project

![lab_1.1 task_1_image](/lab_1/lab_1.1/images/task_1/task_1.png)

![lab_1.1 task_0_Circuit](/lab_1/lab_1.1/images/task_1/task_1_Circuit.png)

##### DFD

![lab_1.1 DFD](/lab_1/lab_1.1/images/Lab_1_cheme.png)

##### Other images

Other images with connection in [/lab_1/lab_1.1/images](/lab_1/lab_1.1/images)

#### Software:

- [Arduino IDE](https://www.arduino.cc/en/software)

Our code has clear comments, but for you we will write the main points here.  
This is a base code for our Project.

```cpp
//For Arduino Uno
//Determining which pins the RGB LED is connected to
#define R_PIN 6
#define G_PIN 3
#define B_PIN 5

//setup code
void setup() {
  //assign the pins a mode of operation(output or input)
  pinMode(R_PIN, OUTPUT); 
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

//loop that will nonestop work on Arduino UNO
void loop() {
  //on RGB LED(Red) for second and off
  on_off_diod(R_PIN);
  //on RGB LED(Green) for second and off
  on_off_diod(G_PIN);
  //on RGB LED(Blue) for second and off
  on_off_diod(B_PIN);
}

//function for on and off RGB LED with one second delay (Function for turning on and off with one second delay the electric current on the pin)
void on_off_diod(int pin){
  //on RGB LED on pin (Start electric current transmission on the pin)
  digitalWrite(pin, 1);
  //second delay
  delay(1000);
  //off RGB LED on pin (Stop electric current transmission on the pin)
  digitalWrite(pin, 0);
}
```
Other code in folders in [/lab_1/lab_1.1](/lab_1/lab_1.1)

#### Tinkercad

<details>
<summary>Click to see task_0</summary>

[lab_1.1 Task_0 in Tinkercad](https://www.tinkercad.com/things/hUXn1sMvgoT?sharecode=V5-eb4NnIwa8_icPDEYQduF4htVFSvu5pyuB1vv3SXI)  
This circuit and code allows you to control the brightness of a RGB LED from the keyboard to make one of 16.7 million. 
For work you need to write r(number)g(number)b(number). __For example:__
- Red - r9g0b0
- Green - r0g9b0
- Blue - r0g0b9

</details>

<details>
<summary>Click to see task_1</summary>

[lab_1.1 Task_1 in Tinkercad](https://www.tinkercad.com/things/dO035Wefz5l?sharecode=3Hm3jjuLs1g7HK-fbBIjScHFplTGOnRNh4iorSZp8e8)  
This circuit and code allows you to on and off the brightness of a RGB LED.  
It works like this, one second is red, one second is green, one second is blue.  
You can't on or off, it just work after upload on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

</details>

<details>
<summary>Click to see task_2_V1</summary>

[lab_1.1 Task_2_V1 in Tinkercad](https://www.tinkercad.com/things/6JCQkYWYs3B?sharecode=U9FOTmA9Ncuwa_fjG77oxHb8qkzK34U_dj44oW_pIuc)  
This circuit and code allows you to on and off the brightness of a RGB LED.
It has one mode. You can on and off RGB LED if you write 'g'

</details>

<details>
<summary>Click to see task_2_V2</summary>

[lab_1.1 Task_2_V2 in Tinkercad](https://www.tinkercad.com/things/8wfPLGTnTLq?sharecode=STpkbYADtMDm-hr6B4mwUL6ALgLF5M9m0D9LhN1DJ6o)  
This circuit and code allows you to on and off the brightness of a RGB LED.
It has two modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.

</details>

<details>
<summary>Click to see task_3-4</summary>

[lab_1.1 Task_3-4 in Tinkercad](https://www.tinkercad.com/things/62KvX8lanUf?sharecode=Ap17QtAgDOo48hsks5oYpykxV940c-53qGE7I705esw)  
This circuit and code allows you to on and off the brightness of a Three RGB LEDs.
It has two modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.  
The code is the same as the code in task_2_V2

</details>

<details>
<summary>Click to see task_5_V1</summary>

[lab_1.1 Task_5_V1 in Tinkercad](https://www.tinkercad.com/things/53uGiR72OBC?sharecode=NPoRelFheTzRlagaMws3vqDz3LDr-U90Xm8LTyd8h8A)  
This circuit and code allows you to on and off the brightness of a Three RGB LEDs.
It has three modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.
- Third mode work like, first RGB LED red, second RGB LED green, thrid RGB LED blue. To on off this mode you need to write 'e' and switch all slider switches.  
The code is the same as the code in task_3-4

</details>

<details>
<summary>Click to see task_5_V2</summary>

[lab_1.1 Task_5_V2 in Tinkercad](https://www.tinkercad.com/things/dGwQRqxL8Af?sharecode=uzq7HeGMdqiiHOq7ge5AVx8bif7cwTnom_EspXsSfKo)  
This circuit and code allows you to on and off the brightness of a Three RGB LEDs.
It has two modes:  
- First mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.
- Second mode work like, first RGB LED red, second RGB LED green, thrid RGB LED blue. To on off this mode you need to write 'e'.

</details>

### Language & Applications documentation:

- [Arduino](https://docs.arduino.cc/)
- [C++](https://devdocs.io/cpp/)
- [Tinkercad](https://www.tinkercad.com/learn)

## Building

For build code and upload on Arduino, you need to download [Arduino IDE](https://www.arduino.cc/en/software).  
This code work only for [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

---

</details>

<details>
<summary>Laboratory 1.2</summary>

# Lab_1.2

Monkey ping pong  
Lab_1.2 is a project based on Arduino that allows you to play ping-pong with flexible sensor.

Lab_1.2 source code is made available on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

## Documentation

### Narrative documentation:

- Our [lab_1.2 docs](/lab_1/lab_1.2/docs/)

### Hardware and Software:

#### Hardware:

##### Minimum kit(to complete task_0): 

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- Buttons - 2
- Set of wires
- 4 kΩ Resistor - 4
- Flexible sensor - 2

![Minimum kit for Project](/lab_1/lab_1.2/images/Minimum_kit.png)

##### Maximum kit(to complete all tasks one by one):

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- Buttons - 2
- Set of wires
- 4 kΩ Resistor - 6
- Flexible sensor - 4

![Maximum kit for Project](/lab_1/lab_1.2/images/Maximum_kit.png)

##### Base scheme for Project

![Task_0_image](/lab_1/lab_1.2/images/Task_0/Task_0.png)

![Task_0_Circuit](/lab_1/lab_1.2/images/Task_0/Task_0_Circuit.png)

##### DFD

![lab_1.2 DFD](/lab_1/lab_1.2/images/Lab_2_cheme.png)

##### Other images

Other images with connection in [/lab_1/lab_1.2/images](/lab_1/lab_1.2/images)

#### Software:

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Processing](https://processing.org/)

Our code has clear comments, but for you we will write the main points here.  
This is a base code for our Project.

Arduino code

```cpp
/*
Сuитыватель показаний датчиков Контекст: Arduino

Сuитывает показания с двух аналоговых входов и двух цифровых входов и выводит их знаuения.

Подклюuения:
Аналоговые датuики — к контактам аналогового ввода A0 и A1 Кнопки — к контактам цифрового ввода 4 и 5
*/


const int leftSensor = A0; // аналоговый ввод для левой руки 
const int rightSensor = A1; // аналоговый ввод для правой руки 
const int resetButton = 4; // цифровой ввод для кнопки сброса 
const int serveButton = 5; // цифровой ввод для кнопки подаuи

int leftReading = 0;	// показания датuика левой руки 
int rightReading = 0;	// показания датuика правой руки 
int resetReading = 0;	// данные кнопки сброса
int serveReading = 0;	// данные кнопки подаuи

void setup() {
// настраиваем последовательное соединение: 
  Serial.begin(9600);
// configure the digital inputs: 
  pinMode(resetButton, INPUT); 
  pinMode(serveButton, INPUT);
}

void loop() {
// сuитываем показания аналоговых датuиков: 
  leftReading = analogRead(leftSensor); 
  rightReading = analogRead(rightSensor);

// сuитываем показания цифровых датuиков: 
  resetReading = digitalRead(resetButton); 
  serveReading = digitalRead(serveButton);

// Выводим результаты на экран: 
  Serial.print(leftReading); 
  Serial.print(','); 
  Serial.print(rightReading); 
  Serial.print(','); 
  Serial.print(resetReading); 
  Serial.print(',');
/* выводим на экран последнее показание датuика
с помощью функции printlin(), uтобы каждый набор из uетырех показаний был на отдельной строке:
*/
Serial.println(serveReading);
}
```
Processing code

```java
import processing.serial.*;

Serial myPort;
String resultString; // Строuная переменная для результатов

void setup() {
  size(480, 130); // устанавливаем размер окна апплета 
  printArray(Serial.list()); // Выводим на экран все
  // доступные последовательные порты
  
  // Hа моем компьютере порт микроконтроллера обыuно
  // первый порт в списке,
  // поэтому я открываю Serial.list()[0].
  // Измените 0 на номер последовательного порта,
  // к которому подклюuен ваш микроконтроллер: 
  String portName = Serial.list()[1];
  // открываем последовательный порт:
  myPort = new Serial(this, portName, 9600);
  
  // сuитываем байты в буфер, пока не дойдем до символа
  // перевода строки (ASCII 10): 
  myPort.bufferUntil('\n');
}

void draw() {
  // задаем цвет фона и заливки для окна апплета: 
  background(#044f6f);
  fill(#ffffff);
  // выводим строку в окне:
  if (resultString != null) { 
    text(resultString, 10, height/2);
  }
}

/* Метод serialEvent() исполняется автоматиuески в программе каждый раз, когда в буфер записывается
байт со знаuением, определенным в методе bufferUntil() в процедуре setup():
*/

void serialEvent(Serial myPort) {
  // Сuитываем данные из последовательного буфера: 
  String inputString = myPort.readStringUntil('\n');
  
  // Отбрасываем символы возврата каретки
  // и перевода строки из строки ввода: 
  inputString = trim(inputString);
  // Оuищаем переменную resultString: 
  resultString = "";
  
  // Разделяем входную строку по запятым и преобразовываем
  // полуuенные фрагменты в целые uисла:
  int sensors[] = int(inputString.split(", "));
  
  // Добавляем знаuения к строке результата:
  for (int sensorNum = 0; sensorNum < sensors.length; sensorNum++) {
    resultString += "Sensor " + sensorNum + ": ";
    resultString += sensors[sensorNum] + '\t';
  }
  // Выводим результат на экран: 
  println(resultString);
}
```

Other code in folders in [/lab_1/lab1.2/code](/lab_1/lab_1.2/code)

#### Tinkercad

<details>
<summary>Click to see Task_0</summary>

[lab_1.2 Task_0 in Tinkercad](https://www.tinkercad.com/things/9XXuvXolDj3?sharecode=ggglE6MH0tPTb_5_Z6lmFAVOzXe-qpBiG2zrRJ5MMPM)  
This circuit and code allows you to control 2 ping-pong paddles with flexible sensor and show you the game. 

</details>

<details>
<summary>Click to see Task_0_Arduino_ultrasonic_sensor</summary>

[lab_1.2 Task_0_Arduino_ultrasonic_sensor in Tinkercad](https://www.tinkercad.com/things/7Oxql65PcST?sharecode=waaRPWMERvyUNfi1oD_xEmB36GVAiRF01Zue4sO-fDY)  
This circuit and code allows you to control 2 ping-pong paddles with ultrasonic sensor and show you the game. 

</details>

<details>
<summary>Click to see Task_1-3</summary>

[lab_1.2 Task_1-3 in Tinkercad](https://www.tinkercad.com/things/e2kYLFEPLQk?sharecode=waSgHX7pjD2xIQmv0CseYd5RBD_IypeuP4LmsLCPHZI)  
This circuit and code allows you to control 4 ping-pong paddles with flexible sensor and show you the game. 

</details>

<details>
<summary>Click to see Task_1-3_Arduino_ultrasonic_sensor</summary>

[lab_1.2 Task_1-3_Arduino_ultrasonic_sensor in Tinkercad](https://www.tinkercad.com/things/h1qa7SH4AzB?sharecode=0vdZN52ufLO0fdSQTVMLpmT19Iv72kAeBdPmgsLWeyQ)  
This circuit and code allows you to control 4 ping-pong paddles with ultrasonic sensor and show you the game. 

</details>

<details>
<summary>Click to see Task_4</summary>

- Not done

</details>

### Language & Applications documentation:

- [Arduino](https://docs.arduino.cc/)
- [C++](https://devdocs.io/cpp/)
- [Tinkercad](https://www.tinkercad.com/learn)
- [Processing](https://processing.org/)

## Building

For build code and upload on Arduino, you need to download [Arduino IDE](https://www.arduino.cc/en/software) and [Processing](https://processing.org/) to see the game and play.  
This code work only for [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

---

</details>

<details>
<summary>Laboratory 1.3</summary>

# Lab_1.3

Lab_1.3 Это проект основанный на Arduino который позволяет обнаружить нарушение климатических условий. 

Lab_1.3 source code is made available on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

## Documentation

### Narrative documentation:

- Our [lab_1.3 docs](/lab_1/lab_1.3/docs/)

### Hardware and Software:

#### Hardware:

##### Maximum kit(to complete all tasks one by one):

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- DHT11 - 1
- LCD 16X2 I2C - 1
- MQ-3- 1
- Flame sensor - 1
- 220 Ω resistor - 2
- LED - 1
- RGB LED - 1
- Buzzer - 1
- Water pump - 1
- Relay - 1
- 9V battery - 1
- Ground humidity sensor - 1
- Wires kit

##### Last scheme for Project

![lab_1.3 Task_1_image](/lab_1/lab_1.3/images/Task_1-6/Task_1-6.jpg)

##### DFD

![lab_1.3 DFD](/lab_1/lab_1.3/images/Lab_3_cheme.png)

##### Other images

Other images with connection in [/lab_1/lab_1.3/images](/lab_1/lab_1.3/images)

#### Software:

- [Arduino IDE](https://www.arduino.cc/en/software)

Our code has clear comments, but for you we will write the main points here.  
This is a base code for Task_0.3 for our Project.

```cpp
// Подключение пинов
#define SENSOR_FLAME_PIN 4
// Переменная для определения огня
int flame;
// Настройка Arduino 
void setup()
{
  // Определения режимов для пинов
  pinMode(SENSOR_FLAME_PIN, INPUT);
  // Частота для работы Arduino с компьютером по USB порту
  Serial.begin(9600);
}
// Цикл который будет бесконечно работать на Arduino 
void loop() {
  // Считывание данных с сенсора
  flame = digitalRead(SENSOR_FLAME_PIN);
  // Если огогнь есть
  if (flame == 1){
    // Выводить сообщение  "Обнаружено пламя" на компьютер
    Serial.println("Обнаружено пламя");
    // Задержка 150 мс
    delay(150);
  } 
  // Если пламени нет
  else{
    // Выводить сообщение  "Пламя не обнаружено" на компьютер
    Serial.println("Пламя не обнаружено");
  }
 // delay(500);
}
```
Other code in folders in [/lab_1/lab_1.3/code/](/lab_1/lab_1.3/code/)

#### Electrical circuit

<details>
<summary>Click to see Task_0.1</summary>

![lab_1.3 Task_0.1](/lab_1/lab_1.3/images/Task_0.1/Task_0.1.png)

Принцип работы этой схемы заключается в том, что датчик DHT11 измеряет температуру и влажность окружающй сренды, считывает эти данные,  через Arduino передаёт на дисплей LCD 16X2 I2C, который выводит эти данные. 

</details>

<details>
<summary>Click to see Task_0.2</summary>

![lab_1.3 Task_0.2](/lab_1/lab_1.3/images/Task_0.2/Task_0.2.png)

Принцип работы этой схемы заключается в том, что датчик MQ-3 измеряет количество углексилого газа в воздухе и через Arduino посылает показатели на компьютер.

</details>

<details>
<summary>Click to see Task_0.3</summary>

![lab_1.3 Task_0.3](/lab_1/lab_1.3/images/Task_0.3/Task_0.3.png)

Принцип работы этой схемы заключается в том, что датчик Flame Sensor при обнаружении пламени посылает сигнал на Arduino, запускает звуковой и световой сигнал и посылает показатели на компьютер.

</details>

<details>
<summary>Click to see Task_0.4</summary>

![lab_1.3 Task_0.4](/lab_1/lab_1.3/images/Task_0.4/Task_0.4.png)

Принцип работы этой схемы заключается в том, что датчик влажности почвы измеряет уровень влажности окружающей среды, если уровень влажности ниже заданных показателей, посылает сигнал на Arduino, который включает водяной насос для увлажнения и выводит сообщение на компьютер "Pump ON" и "Pump OFF".

</details>

<details>
<summary>Click to see Task_1-6</summary>

![lab_1.3 Task_1-6](/lab_1/lab_1.3/images/Task_1-6/Task_1-6.jpg)

![lab_1.3 Task_1-6](/lab_1/lab_1.3/images/Task_1-6/Circuit_Task_1-6.png)

Объединяем схемы с Task_0.1 по Task_0.4 в одну с помощью беспаечной платы.  
Добавляем звуковое и световое оповещения индивидульное для каждого датчика.  
Вся информация теперь выводится на дисплей LCD 16X2 I2C.  
Теперь водяной насос включается не только от датчика влажности почвы, но и от датчика влажности воздуха.

</details>

### Language & Applications documentation:

- [Arduino](https://docs.arduino.cc/)
- [C++](https://devdocs.io/cpp/)

## Building

For build code and upload on Arduino, you need to download [Arduino IDE](https://www.arduino.cc/en/software).  
This code work only for [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

---

</details>

## Wishes

Use this project wisely.  
Best wishes