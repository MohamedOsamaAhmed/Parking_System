/*

 * main.c
 *
 *  Created on: Apr 20, 2021
 *      Author: MohamedOsama
 */

/* 
The main Function of This code is that:
    A car park has two gates one for entering cars and the other for leaving cars when a car enters the parking area a
    presuure sensor acitvates a switch that is connected to pin INT0 and the same for leaving cars INT1 these two actions
    will make LEDs at PC4 and PC5 ON then display cars number using UART and prevent entering more than 10 cars by makeing
    LED PB4 On.
    These applied using AVR Atmega328P with 8MHz RC clock source.
*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Registers.h"
#include <util/delay.h>

/* cars number */
u8 ncar = 0;
/* two flags to indicate if entering or exiting actions happen*/
u8 entering_flag = 0;
u8 exiting_flag = 0;

/*Counter for Timer to count 5 seconds*/
u32 counter = 0;
/* Function To fair Interrupts on Entering at INT0 and Exiting at INT1 */
void ExternalInerrupt_Init()
{
    /* The Falling edge of INT0 and INT1 generates an interrupt request */
    EICRA = 0xA;

    /* Enable external Interrupt on INT0 and INT1 */
    EIMSK = 0x3;

    /* Clear interrupt flag     */
    EIFR = 0x3;
    /* Enable Global Interrupt */
    SET_BIT(SREG, 7);
}
void Timer0_Init()
{
    /* Set OC0A is disconnected and Waveform Generation Mode Normal*/
    TCCR0A = 0x0;
    /* Clk Source with No Prescaler */
    TCCR0B = 0x1;
    /* Disable Interrupt on overflow*/
    TIMSK0 = 0x1;
}

void DIO_Init()
{
    /* Set Pins PC4,PC5 and PB5 as output and initial value = 0 for Leds indication */
    SET_BIT(DDRB, 5);

    SET_BIT(DDRC, 4);
    SET_BIT(DDRC, 5);

    CLR_BIT(PORTB, 5);
    CLR_BIT(PORTC, 4);
    CLR_BIT(PORTC, 5);

    /* Set Pins PD2 and PD3 Pull up Direction(n) = 0 Port(n) = 1 PUD bit in MCUCR Register = 0 For pressure Seneor for
    entering and exiting which is switch*/

    CLR_BIT(DDRD, 2);
    CLR_BIT(DDRD, 3);

    SET_BIT(PORTD, 2);
    SET_BIT(PORTD, 3);

    CLR_BIT(MCUCR, 4);

    /*Set Pin PD1 output to send cars number using UART*/
    SET_BIT(DDRD, 1);

}
void UART_Init()
{

    /* Send Enable */
    UCSR0B = 0x8;
    /* ASynchronous USART, 1 stop bit and 8-bit character size */
    UCSR0C = 0x6;
    /* Buderate 9600 with 8Mhz RC clock*/
    UBRR0 = 51;



}
/* Function to send data using UART*/
void USART_Send(u8 data)
{
	UDR0 = data;
    /* wait till the transmission is completed*/
	while (GET_BIT(UCSR0A,6) != 0)
	{

	}

}
int main()
{

    DIO_Init();
    Timer0_Init();
    ExternalInerrupt_Init();
    UART_Init();
    while (1)
    {
          
       
    }
}

/*Interrupt for Entering Action when switch is pressed increase cars number and stop entering if cars number > 9 by turning Led On PB5 */
#define __INTR_ATTRS used, externally_visible
void __vector_1(void) __attribute__((signal, __INTR_ATTRS));
void __vector_1(void)
{

	/*increase car number*/
	 ncar++;
    if (ncar > 9)
    {


        /*Led On at PB5 to show that is parking area is occupied*/
        SET_BIT(PORTB, 5);

        /* Clear interrupt flag */
        SET_BIT(EIFR,0);

        /* Disable Entering Action (external Interrupt on INT0) only and INT1 Still working */
        EIMSK = 0x2;
   
    }
    else
    {

        /*Led On at PC5 for 1 Second*/
        SET_BIT(PORTC, 5);
        _delay_ms(1000);
        CLR_BIT(PORTC, 5);
    }

}
/* Interrupt for exiting switch is pressed increase cars number and continue entering if cars number < 9 by turning Led Off PB5 */
#define __INTR_ATTRS used, externally_visible
void __vector_2(void) __attribute__((signal, __INTR_ATTRS));
void __vector_2(void)
{
	 /* decrease Cars number */
	if (ncar > 0)
	{
	    ncar--;
	}
    /*Led On at PC4 for 1 Seconds*/
    SET_BIT(PORTC, 4);
    _delay_ms(1000);
    CLR_BIT(PORTC, 4);

    if (ncar <= 9)
    {
    	/*Led Off at PB5 vaild place for more cars to enter*/
    	CLR_BIT(PORTB, 5);

        /* Enable Entering Action (external Interrupt on INT0) and INT1 Still working */
        EIMSK = 0x3;

    }

}

/*Timer0 ISR to count 5 seconds to disply cars number every 5 seconds*/
#define __INTR_ATTRS used, externally_visible
void __vector_16(void) __attribute__((signal, __INTR_ATTRS));
void __vector_16(void)
{
    /* Calculating overflow times to count 5 seconds ((2^8)-1)*5)/(8*10^6) */
    if (counter == 156863)
    {
        USART_Send(ncar);
        counter = 0;
    }
    else
    {
    counter++;
    }
 }



