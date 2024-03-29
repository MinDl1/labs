import processing.serial.*; //Добавление библиотеки serial

Serial myPort; //порт
String resultString; // Строuная переменная для результатов

float leftPaddle, rightPaddle;//переменныедляѕначений // датчихов иѕгиба
int resetButton, serveButton; // переменные для хнопох 
int leftPaddleX, rightPaddleX;//гориѕонтальныепоѕиции
// рахетох
int paddleHeight = 50; // вертихальный раѕмер рахетох
int paddleWidth = 10; // гориѕонтальный раѕмер рахетох 
float leftMinimum = 0; // минимальное ѕначение левого
// датчиха иѕгиба 
float rightMinimum = 0;//минимальноеѕначениеправого
// датчиха иѕгиба
float leftMaximum = 430; // махсимальное ѕначение левого
// датчиха иѕгиба
float rightMaximum = 430; // махсимальное ѕначение правого

int ballSize=10;//рaѕмермячихa
int xDirection=1;//гориѕонтaльноенaпрaвлениедвижения // мячихa
// влево: –1, впрaво: 1
int yDirection = 1; // вертихaльное нaпрaвление движения // мячихa
int xPos, yPos;
// вверх: –1, вниѕ: 1
//гориѕонтaльноеивертихaльное // положение мячихa

boolean ballInMotion=false;//мячихдвижется? 
int leftScore = 0;
int rightScore = 0;
int fastBall = 0; //скорость мячика

int fontSize = 36; // раѕмер mрифта для отображения счета

void setup(){
  size(640, 480); // устанавливаем раѕмер охна апплета
  String portName = Serial.list()[1]; //выбираем порт с которого будем считывать 1, 0, 2
  // открываем последовательный порт: 
  myPort = new Serial(this, portName, 9600);
  // сuитываем байты в буфер, пока не дойдем до // символа перевода строки (ASCII 10): 
  myPort.bufferUntil('\n');
  // инициалиѕируем ѕначения датчихов: 
  leftPaddle = height/2;
  rightPaddle = height/2;
  resetButton = 0;
  serveButton = 0; // кнопка для скорости мячика
  // инициалиѕируем гориѕонтальные поѕиции рахетох: 
  leftPaddleX = 50;
  rightPaddleX = width - 50;
  // рисуем фигуры беѕ охантовхи:
  noStroke();
  xPos = width/2;
  yPos = height/2;
  // соѕдаем mрифт иѕ третьего mрифта, доступного системе: 
  PFont myFont = createFont(PFont.list()[2], fontSize); 
  textFont(myFont);
}

void serialEvent(Serial myPort){
  // считываем данные иѕ последовательного буфера: 
  String inputString = myPort.readStringUntil('\n');
  // отбрасываем символы воѕврата харетхи и перевода строхи
  // иѕ строхи ввода:
  inputString = trim(inputString);
  // очищаем переменную resultString: 
  resultString = "";
  // раѕделяем входную строху по ѕапятым и преобраѕовываем
  // полученные фрагменты в целые числа:
  int sensors[] = int(inputString.split(", "));
  
  // если получены все строхи ѕначений датчихов, испольѕуем их:
  if (sensors.length == 4) {
    // масmтабируем данные датчихов иѕгиба х диапаѕону // рахетох:
    leftPaddle = (sensors[0]-2)*50;
    rightPaddle = (sensors[1]-2)*50;
    // присваиваем ѕначения хнопох соответствующим // переменным:
    resetButton = sensors[2];
    serveButton = sensors[3];
    // добавляем ѕначения х строхе реѕультата:
    resultString += "left: "+ leftPaddle + "\tright: " + rightPaddle;
    resultString += "\treset: "+ resetButton + "\tserve: " + serveButton;
  }
  myPort.write('\r'); // посылаем символ воѕврата харетхи
}

void draw(){
  // задаем цвет фона и заливки для окна апплета: 
  background(#044f6f);
  fill(#ffffff);
  // рисуем левую рахетху:
  // Лимиты
  if(leftPaddle > leftMaximum){
    leftPaddle = leftMaximum;
  }
  else if(leftPaddle < leftMinimum){
    leftPaddle = leftMinimum;
  }
  if(rightPaddle > rightMaximum){
    rightPaddle = rightMaximum;
  }
  else if(rightPaddle < rightMinimum){
    rightPaddle = rightMinimum;
  }
  rect(leftPaddleX, leftPaddle, paddleWidth, paddleHeight);
  // рисуем правую рахетху:
  rect(rightPaddleX, rightPaddle, paddleWidth, paddleHeight);
  // вычисляем местонахождение мячиха и прорисовываем его: 
  if(ballInMotion==true){
    animateBall(); 
  }
  // если нажата хнопха скорости, увиличиваем скорость, если скорость больше 2 то скорость становится обычной
  if (serveButton == 1) {
     fastBall++;
     if(fastBall > 2){
       fastBall = 0;
     }
  }
  //еслинажатахнопхасброса,обнуляемсчетиѕапусхаем // мячих в движение:
  if (resetButton == 1) {
      leftScore = 0;
      rightScore = 0;
      ballInMotion = true;
  }
  // выводим счет на Зхран: 
  text(leftScore, fontSize, fontSize); 
  text(rightScore, width-fontSize, fontSize);
}

void animateBall(){
  // если мячих движется влево: 
  if (xDirection < 0) {
    // если мячих нaходится слевa от левой рaхетхи
    if ((xPos >= leftPaddleX-10 && xPos <= leftPaddleX+10)) {
    // если мячих нaходится между верхом и ниѕом левой рaхетхи:
      if((leftPaddle - (paddleHeight/1.5) <= yPos+2 || leftPaddle - (paddleHeight/1.5) <= yPos-2) && (yPos+2 <= leftPaddle + (paddleHeight /1.5) || yPos-2 <= leftPaddle + (paddleHeight /1.5))) {
      // иѕменяем нaпрaвление гориѕонтaльного движения нa обрaтное:
        xDirection =-xDirection;
      }
    } 
  }
  // если мячих движется вправо: 
  else {
  // если мячих справа от правой рахетхи
    if (xPos >= rightPaddleX-10 && xPos <= rightPaddleX+10) {
    // если мячих находится между верхом и ниѕом // правой рахетхи:
      if((rightPaddle - (paddleHeight/1.5) <= yPos+2 || rightPaddle - (paddleHeight/1.5) <= yPos-2) && (yPos+2 <= rightPaddle + (paddleHeight /1.5) || yPos-2 <= rightPaddle + (paddleHeight /1.5))) {
      // иѕменяем направление гориѕонтального
      // движения на обратное: 
        xDirection =-xDirection;
      } 
    }
  }
  // если мячих выходит ѕа пределы охна слева: 
  if (xPos < 0) {
    rightScore++;
    resetBall(); 
  }
  // если мячих выходит ѕа пределы охна справа: 
  if (xPos > width) {
    leftScore++;
    resetBall();
  }
  // не даем мячиху выйти ѕа верхний или нижний предел охна 
  if ((yPos - ballSize/2 <= 0) || (yPos +ballSize/2 >=height)) { // иѕменяем направление вертихального движения мячиха
  // на обратное:
    yDirection = -yDirection; 
  }
  // обновляем местонахождение мячиха: 
  xPos = xPos + xDirection;
  yPos = yPos + yDirection;
  // Если скорость 1 2 3
  if(fastBall >= 1){
    xPos = xPos + xDirection;
    yPos = yPos + yDirection;
  }
  if(fastBall >= 2){
    xPos = xPos + xDirection;
    yPos = yPos + yDirection;
  }
  // рисуем мячих:
  rect(xPos, yPos, ballSize, ballSize); 
}

void resetBall() {
  // воѕвращаем мячих обратно в центр охна:
  xPos = width/2;
  yPos = height/2;
}
