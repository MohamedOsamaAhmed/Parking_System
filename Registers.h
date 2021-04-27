
#ifndef REGISTERS_H_
#define REGISTERS_H_

/*External Interrupts Registers*/
#define SREG *((volatile u8 *)0x5F)
#define EICRA *((volatile u8 *)0x69)
#define EIMSK *((volatile u8 *)0x3D)
#define EIFR *((volatile u8 *)0x3C)


/* Timer0 Registers */
#define TIMSK0 *((volatile u8 *)0x6E)
#define TCCR0A *((volatile u8 *)0x44)
#define TCCR0B *((volatile u8 *)0x45)

/* UART0 Registers*/
#define UDR0 *((volatile u8 *)0xC6)
#define UBRR0 *((volatile u16 *) 0xC4)
#define UCSR0C *((volatile u8 *)0xC2)
#define UCSR0B *((volatile u8 *)0xC1)
#define UCSR0A *((volatile u8 *)0xC0)





#define MCUCR *((volatile u8 *)0x55)


#define PORTB *((volatile u8 *)0x25)
#define DDRB *((volatile u8 *)0x24)
#define PINB *((volatile u8 *)0x23)


#define DDRC *((volatile u8 *)0x27)
#define PORTC *((volatile u8 *)0x28)
#define PINC *((volatile u8 *)0x26)

#define PORTD *((volatile u8 *)0x2B)
#define DDRD *((volatile u8 *)0x2A)
#define PIND *((volatile u8 *)0x29)

#endif /* REGISTERS_H_ */
