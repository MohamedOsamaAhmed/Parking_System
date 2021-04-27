# Parking System
## Summary 
This is an embedded c project using Atmega328p micro controller and 8MHz internal RC oscillator. It is a parking area management; the main function is counting cars number in the parking area and prevent entering more than 10 cars.

## Hardware Components
>   Atmega328p Micro Controller runs on 8MHz internal RC

>   UART

>	2- Push buttons

>	3-Led 

>	3-Resistor 330 Ohm

>	2-Resistor 1000 Ohm

## Main Function
(ISIS-F Hardware) A car park has two gates, one for entering cars and the other for leaving cars. When a car enters the parking area, a pressure sensor activates a switch that is connected to pin INTO which generates external interrupt to open the entry gate (LED at pin PC2) for the car to enter. When a car exits the parking area, a pressure sensor activates a switch that is connected to pin INT1 which generates external interrupt to open the exit gate (LED at pin PC4) for the car to leave. 
Define a global variable 'ncars' to hold the number of cars in the parking area. If 'ncars' reaches 10, then disable the external interrupt INTO to prevent more cars from entering and turn on an LED on pin PB5 to show that there is no vacancy in the parking area. When 'ncars' gets 
below 10, then enable the external interrupt INTO. 
The system should always display 'ncars' on the PC screen every 5 seconds. This should be done via interrupt of TC1 to produce the 5-seconds delay.	

## Flowchart
![alt text](https://github.com/MohamedOsamaAhmed/Parking_System/blob/main/Parking%20System.png?raw=true)

## Proteus Design
![alt text](https://github.com/MohamedOsamaAhmed/Parking_System/blob/main/ProteusDesign.PNG?raw=true)
## Header Files

>•	**Registers.h:** contains all needed registers of Atmega328p microcontroller.

>•	**STD_TYPES.h:** contains standard types to overcome compiler dependency for example int size may     change 2 bytes or 4 bytes so if there is a change in the expected size,                       we only change one time in STD_TYPES.h file.

>•	**BIT_MATH.h:** contains Macros for setting and clearing any pin in the micro.

## Using Different Styles in The Code
1.	In function ` ExternalInerrupt_Init() ` I set the register one time but in function ` DIO_Init() ` I write on register bit by bit which is **better?**

    Writing on the  Register one time is faster but need to write all bits in the register
    Or 
    you should use bitwise or like this code ` EIMSK =| 0x3 `to set only the first two bits for example and let the rest as they are but this take more time to be executed than     the first.
    write on register bit by bit is more readable you can know that every line only select one choice but it is the slowest way.

2.	Using ` _delay_ms() ` function make CPU counting and don’t make any thing else so it is preferred to use timer peripheral to do this job like I did when sending cars number     every 5 seconds but it also increase latency of the system. 

## Problems
  > • 	**UART Module doesn’t work on Proteus 8 only work on version 7.** 
  
  > •	**Code debugging supported in Proteus 8 only.**
   
  > •	**In Proteus 7: If entering action happens when the ncars = 10 exiting action doesn’t turn       occupied led off it needs one exiting again although ncars still = 10 but it works             properly on Proteus 8.** 

## Conclusion
#### The main purpose of this project not to show how we can solve hard business logic but learn that:
   > •	**There are many ways to write the same code every one has advantages and disadvantages and you choose depending on your requirements.**
   
   > •	**Flowcharts simplify the implementation.**
   
   > •	**Simulation doesn’t always work right so try many versions or the best way use hardware components.** 
   
   > •	**Interrupts is the last solution you should use as it is not a good thing.**


