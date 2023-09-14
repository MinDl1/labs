# Laboratory works

## About project

Labs is a project based on different hardware and software.  
The project is made possible by [MinDl](https://github.com/MinDl1), [Gryn69](https://github.com/Gryn69), [Goremika26](https://github.com/Goremika26) who've generously donated dozens of hours in code development and upkeep.

<details>
<summary>Laboratory 1</summary>

# Lab_1

Lab_1 is a project based on Arduino that allows you to control the brightness of a three-color LED from the keyboard.

Lab_1 source code is made available on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

## Documentation

### Narrative documentation:

- Our [docs](/lab_1/docs/Лабраторная%20работа%201.1.pdf)

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

![Minimum kit for Project](/lab_1/images/Minimum_kit.png)

##### Maximum kit(to complete all tasks one by one):

- Computer - 1
- Arduino UNO - 1
- Wire for connecting an Arduino UNO to a computer - 1
- Small breadboard - 1
- RGB LED - 3
- Wires Male-Male - 19
- 220 Ohm resistor - 3
- Slider switches - 6

![Maximum kit for Project](/lab_1/images/Maximum_kit.png)

##### Base scheme for Project

![task_1_image](/lab_1/images/task_1/task_1.png)

![task_0_Circuit](/lab_1/images/task_1/task_1_Circuit.png)

##### Other images

Other images with connection in [/images](/lab_1/images)

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
Other code in folders in [lab_1](/lab_1)

#### Tinkercad

<details>
<summary>Click to see task_0</summary>

[Lab_1_Task_0 in Tinkercad](https://www.tinkercad.com/things/hUXn1sMvgoT?sharecode=V5-eb4NnIwa8_icPDEYQduF4htVFSvu5pyuB1vv3SXI)  
This circuit and code allows you to control the brightness of a RGB LED from the keyboard to make one of 16.7 million. 
For work you need to write r(number)g(number)b(number). __For example:__
- Red - r9g0b0
- Green - r0g9b0
- Blue - r0g0b9

</details>

<details>
<summary>Click to see task_1</summary>

[Lab_1_Task_1 in Tinkercad](https://www.tinkercad.com/things/dO035Wefz5l?sharecode=3Hm3jjuLs1g7HK-fbBIjScHFplTGOnRNh4iorSZp8e8)  
This circuit and code allows you to on and off the brightness of a RGB LED.  
It works like this, one second is red, one second is green, one second is blue.  
You can't on or off, it just work after upload on [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3).

</details>

<details>
<summary>Click to see task_2_V1</summary>

[Lab_1_Task_2_V1 in Tinkercad](https://www.tinkercad.com/things/6JCQkYWYs3B?sharecode=U9FOTmA9Ncuwa_fjG77oxHb8qkzK34U_dj44oW_pIuc)  
This circuit and code allows you to on and off the brightness of a RGB LED.
It has one mode. You can on and off RGB LED if you write 'g'

</details>

<details>
<summary>Click to see task_2_V2</summary>

[Lab_1_Task_2_V2 in Tinkercad](https://www.tinkercad.com/things/8wfPLGTnTLq?sharecode=STpkbYADtMDm-hr6B4mwUL6ALgLF5M9m0D9LhN1DJ6o)  
This circuit and code allows you to on and off the brightness of a RGB LED.
It has two modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.

</details>

<details>
<summary>Click to see task_3-4</summary>

[Lab_1_Task_3-4 in Tinkercad](https://www.tinkercad.com/things/62KvX8lanUf?sharecode=Ap17QtAgDOo48hsks5oYpykxV940c-53qGE7I705esw)  
This circuit and code allows you to on and off the brightness of a Three RGB LEDs.
It has two modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.  
The code is the same as the code in task_2_V2

</details>

<details>
<summary>Click to see task_5_V1</summary>

[Lab_1_Task_5_V1 in Tinkercad](https://www.tinkercad.com/things/53uGiR72OBC?sharecode=NPoRelFheTzRlagaMws3vqDz3LDr-U90Xm8LTyd8h8A)  
This circuit and code allows you to on and off the brightness of a Three RGB LEDs.
It has three modes:  
- First mode work like, you need to write r(number)g(number)b(number). Like in [task_0](#tinkercad). To on off this mode you need to write 'q'.
- Second mode work like, one second is red, one second is green, one second is blue. Like in [task_1](#tinkercad). To on off this mode you need to write 'w'.
- Third mode work like, first RGB LED red, second RGB LED green, thrid RGB LED blue. To on off this mode you need to write 'e' and switch all slider switches.  
The code is the same as the code in task_3-4

</details>

<details>
<summary>Click to see task_5_V2</summary>

[Lab_1_Task_5_V2 in Tinkercad](https://www.tinkercad.com/things/dGwQRqxL8Af?sharecode=uzq7HeGMdqiiHOq7ge5AVx8bif7cwTnom_EspXsSfKo)  
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

## Wishes

Use this project wisely.  
Best wishes