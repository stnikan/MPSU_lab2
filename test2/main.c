/*
 * test2.c
 *
 * Created: 14.09.2023 10:18:10
 * Author : stnik
 */ 

#include <avr/io.h>
#define F_CPU 11059200UL
#include <util/delay.h>
#include <avr/interrupt.h>   //для использования прерываний

//———————————————

uint16_t sec = 0;
uint8_t my_str[]    = { 0x0F, 0x09,0x09,0x0F, 0xF0, 0x90, 0x90, 0xF0};
uint8_t my_column[] ={
	0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
	0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0};
	
uint8_t i = 0;

//———————————————

void timer_ini(void)
{	
	//таймер для смены картинки...
	TIMSK = (1<<TOIE1); //разрешение использования счетчика для прерываний
	TCCR1B = (1<<CS12); //используем делитель частоты
	TCNT1 = 65300; //initial value for timer to start counting
	
	//нам больше не нужен делей
	TCCR3B = (1<<CS32); //используем делитель частоты
	ETIMSK |= (1<<TOIE3);
	//TCNT3 = 65300;
	TCNT3 = 22058; 
}

//———————————————

ISR (TIMER1_OVF_vect) //смена рисуемого столбцаи и вывод картинки
{
	TCNT1 = 65450; 
	i = (i+1)%16;
	PORTD = my_column[i];
	PORTA = my_str[i%8];
	PORTC = my_str[(i+4)%8];;
}
//———————————————
ISR (TIMER3_OVF_vect) //смена картинки
{
	TCNT3 = 22058;// 65300;
	//i = (i+1)%8;
	//PORTD = my_column[i];
	//PORTA = my_str[i];
	if(sec>=2){
		sec=0;
		
		for (uint8_t i = 0; i<8;i++){
			my_str[i] = ~my_str[i];
		}
	}
	else {sec++;}
	
}






int main(void)
{	
	
    DDRA = 0xFF; 
    DDRD = 0xFF;
	DDRC = 0xFF;
	

	timer_ini();
	sei();
	 //разрешение прерываний
	

	
    while (1) 
    {	
			
		
    }
}