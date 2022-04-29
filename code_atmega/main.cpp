#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "lib/twi_lcd.h"
#include <util/delay.h>
#include <stdio.h>

#define tbi(port,bit){port^=(1<<bit);} // toggle
#define sbi(port,bit){port|=(1<<bit);}//set
#define cbi(port,bit){port&=~(1<<bit);}//clear
#define DHT11_PIN 6

uint8_t c=0,I_RH=0,D_RH=0,I_Temp=0,D_Temp=0,CheckSum; // dung cho DHT11
int NDlast=0,DAlast=0; // bien cuoi ND DA
char data[16]; // chuoi gui du lieu ra LCD
char data1[10];
unsigned long dem=0; // dung cho timer 0
unsigned long last=0;
unsigned long last1=0; 

unsigned char Receive(){
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}
void Send(char data){
	while (! (UCSRA & (1<<UDRE)));
	UDR = data ;
}
void SendString(char *str){
	unsigned char i=0;
	
	while (str[i]!=0){		// Send string till null 
		Send(str[i]);
		i++;
	}
}
void UARTinit(){
	UBRRH=0;
	UBRRL=51;// set baud rate
	UCSRC=(1<<URSEL)|(1<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0); // on mode use UBRRH, mode send 8bit
	UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);// enable tran enable receive	
}
void Request()				//Microcontroller send start pulse/request  DHT 11
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	// set to low pin 
	_delay_ms(20);			// wait for 20ms 
	PORTD |= (1<<DHT11_PIN);	// set to high pin 
	_delay_us(40);
}

void Response(){				// receive response from DHT11 and start trans bit
	DDRD &= ~(1<<DHT11_PIN); // chuyen thanh input chan PD6
	while(PIND & (1<<DHT11_PIN));// neu bang 1 dung
	while((PIND & (1<<DHT11_PIN))==0);// neu bang 0 dung (khoang 80us)
	while(PIND & (1<<DHT11_PIN));// neu bang 1 dung (khoang 80us)
	// bat dau gui...
}

uint8_t Receive_data(){			//receive data 
	for (int i=0; i<8; i++){
		while((PIND & (1<<DHT11_PIN)) == 0);  //check received bit 0 or 1 
		// giu o muc thap khi bat dau gui 1 bit nao do
		_delay_us(30); // sau 26-> 28 us kiem tra  1 (70us) hay 0
		if(PIND & (1<<DHT11_PIN))// if high pulse is greater than 30ms 
			c = (c<<1)|(0x01);	//then its logic HIGH 
		else			// otherwise its logic LOW 
			c = (c<<1);
		while(PIND & (1<<DHT11_PIN));// neu bang 1 dung doi cho bit dc gui xong
	}
	return c;
}
void read_dht11(){
	Request();		// send start pulse 
	Response();		//receive response 
	I_RH=Receive_data();	// store first eight bit in I_RH
	D_RH=Receive_data();	// store next eight bit in D_RH 
	I_Temp=Receive_data();	// store next eight bit in I_Temp 
	D_Temp=Receive_data();	//store next eight bit in D_Temp 
	CheckSum=Receive_data();// store next eight bit in CheckSum 	
	if (I_RH!=DAlast||I_Temp!=NDlast){ // neu doc khác moi cap nhat ra LCD
		sprintf(data,"DA=%d",I_RH); // in do am
		i2c_goto_puts(1,1,data);
		i2c_lcd_puts("%");

		sprintf(data,"ND=%d",I_Temp); // in nhiet do
		i2c_goto_puts(1,8,data);
		i2c_lcd_put(223);// put 1 ki tu '
		i2c_lcd_puts("C");

		Send('X');
		Send(I_RH/10); // gui do am
		Send(I_RH%10);

		Send(I_Temp/10);// gui nhiet do
		Send(I_Temp%10);
	}
	NDlast=I_Temp; // gan lay gia tri cuoi
	DAlast=I_RH;
}

uint16_t read_adc(unsigned char kenh_adc){ // doc adc
	ADMUX=kenh_adc|(1<<REFS0);
	ADCSRA|=(1<<ADSC);
	loop_until_bit_is_set(ADCSRA,ADIF); 
	return ADCW;
}
void read_gas_sensor(unsigned char kenh,int value){ // goc cam bien gas
	if (read_adc(kenh)>value){ // nong do khi gas lon
		if (bit_is_clear(PINC,6)){ // neu chua dc bat quat
			Send('E');
			tbi(PORTC,6)
		}
		if(OCR1A==1000){ // neu dong co servo = -90 (chua mo)
			Send('G');
			OCR1A=2000;// mo cua bep 
		}
		sprintf(data1,"CO GAS %d",read_adc(kenh));
		i2c_goto_puts(2,1,data1);
	}
	else{
		i2c_goto_puts(2,1,"BINH THUONG");
	}
}
void read_gas_sensor1(){
	if (bit_is_clear(PINA,0)){ // có khí gas
		if (bit_is_clear(PINC,6)){ // neu chua dc bat quat
			Send('E');
			tbi(PORTC,6)
		}
		if(OCR1A==1000){ // neu dong co servo = -90 (chua mo)
			Send('G');
			OCR1A=2000;// mo cua bep
		}
		//i2c_goto_puts(2,1,"  CO GAS   ");

	}
	else{
		//i2c_goto_puts(2,1,"BINH THUONG");
	}
}
void read_rain_sensor(){ // doc cam bien mua va cam bien anh sang
	if(bit_is_clear(PINA,1)||bit_is_clear(PINA,2)){ // cam bien mua va cam bien anh sang
	// co mua hoac khong co sang
		if(OCR1B==1000){ // neu dong co servo = -90 (chua keo vao)
			Send('H');
			OCR1B=2000;// keo do vao
		}
	}
	/*else if (bit_is_set(PINA,1)&&bit_is_set(PINA,2)) { // nang va ko mua
		if(OCR1B==2000){ // neu dong co servo = 90 ( keo vao roi)
			Send('H');
			OCR1B=1000;// keo do ra
		}
	}*/
}
void time_to_activity(unsigned long x){
	if((dem-last)>=x){// dem thoi gian hoat dong su dung timer 0 don vi (ms)
		tbi(PORTA,0);//ham can thuc hien
		last=dem=0;
	}
}
void TIMER0init(){
	TCCR0=(1<<CS01)|(1<<CS00); // mode NORMAL prescaler =clock/64
	TIMSK=(1<<TOIE0);
	TCNT0=130; // set gia tri bat dau dem (su dung thach anh 8.000.000 Mhz)
}
void ADCinit(){
	ADMUX|=(1<<REFS0);
	ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);// khoi dong adc
}
// bit is set
void button_send(){  // bit is set
	if(bit_is_set(PINA,4)){ // button 1=0
		_delay_ms(10);
		if (bit_is_set(PINA,4)){
			while(bit_is_set(PINA,4));
			Send('A');
			tbi(PORTC,2);
		}
		PORTA=(0<<PA4);
	}
	else if(bit_is_set(PINA,5)){ // button2 =0
		_delay_ms(10);
		if (bit_is_set(PINA,5)){
			while(bit_is_set(PINA,5));
			Send('B');
			tbi(PORTC,3);
		}
		PORTA=(0<<PA5);
	}
	else if(bit_is_set(PINA,6)){ // button3 =0
		_delay_ms(10);
		if (bit_is_set(PINA,6)){
			while(bit_is_set(PINA,6));
			Send('C');
			tbi(PORTC,4);
		}
		PORTA=(0<<PA6);
	}
	else if(bit_is_set(PINA,7)){ // button4 =0
		_delay_ms(10);
		if (bit_is_set(PINA,7)){
			while(bit_is_set(PINA,7));
			Send('D');
			tbi(PORTC,5);
		}
		PORTA=(0<<PA7);
	}
	else if(bit_is_set(PINB,0)){ // button5 =0
		_delay_ms(10);
		if (bit_is_set(PINB,0)){
			while(bit_is_set(PINB,0));
			Send('E');
			tbi(PORTC,6);
		}
		PORTB=(0<<PB0);
	}
	else if(bit_is_set(PINB,1)){ // button6 =0
		_delay_ms(10);
		if (bit_is_set(PINB,1)){
			while(bit_is_set(PINB,1));
			Send('F');
			tbi(PORTC,7);
		}
		PORTB=(0<<PB1);
	}
	else if(bit_is_set(PINB,2)){ // button7 =0  -- cua bep
		_delay_ms(10);
		if (bit_is_set(PINB,2)){
			while(bit_is_set(PINB,2));
			Send('G');
			if (OCR1A==1000)// neu dong thi mo
				OCR1A=2000;
			else OCR1A=1000; // nguoc lai
		}
		PORTB=(0<<PB2);
	}
	else if(bit_is_set(PINB,3)){ // button8 =0 phoi doi
		_delay_ms(10);
		if (bit_is_set(PINB,3)){
			while(bit_is_set(PINB,3));
			Send('H');
			if (OCR1B==1000)// neu khong phoi thi phoi
				OCR1B=2000;
			else OCR1B=1000; // neu phoi thi lay vao
		}
		PORTB=(0<<PB3);
	}
}
// bit is clear
void button_send1(){
	if(bit_is_clear(PINA,4)){ // button 1=0
		_delay_ms(10);
		if (bit_is_clear(PINA,4)){
			while(bit_is_clear(PINA,4));
			Send('A');
			tbi(PORTC,2);
		}
	}
	else if(bit_is_clear(PINA,5)){ // button2 =0
		_delay_ms(10);
		if (bit_is_clear(PINA,5)){
			while(bit_is_clear(PINA,5));
			Send('B');
			tbi(PORTC,3);
		}
	}
	else if(bit_is_clear(PINA,6)){ // button3 =0
		_delay_ms(10);
		if (bit_is_clear(PINA,6)){
			while(bit_is_clear(PINA,6));
			Send('C');
			tbi(PORTC,4);
		}
	}
	else if(bit_is_clear(PINA,7)){ // button4 =0
		_delay_ms(10);
		if (bit_is_clear(PINA,7)){
			while(bit_is_clear(PINA,7));
			Send('D');
			tbi(PORTC,5);
		}
	}
	else if(bit_is_clear(PINB,0)){ // button5 =0
		_delay_ms(10);
		if (bit_is_clear(PINB,0)){
			while(bit_is_clear(PINB,0));
			Send('E');
			tbi(PORTC,6);
		}
	}
	else if(bit_is_clear(PINB,1)){ // button6 =0
		_delay_ms(10);
		if (bit_is_clear(PINB,1)){
			while(bit_is_clear(PINB,1));
			Send('F');
			tbi(PORTC,7);
		}
	}
	else if(bit_is_clear(PINB,2)){ // button7 =0  -- cua bep
		_delay_ms(10);
		if (bit_is_clear(PINB,2)){
			while(bit_is_clear(PINB,2));
			Send('G');
			if (OCR1A==1000)// neu dong thi mo
			OCR1A=2000;
			else OCR1A=1000; // nguoc lai
		}
	}
	else if(bit_is_clear(PINB,3)){ // button8 =0 phoi doi
		_delay_ms(10);
		if (bit_is_clear(PINB,3)){
			while(bit_is_clear(PINB,3));
			Send('H');
			if (OCR1B==1000)// neu khong phoi thi phoi
			OCR1B=2000;
			else OCR1B=1000; // neu phoi thi lay vao
		}
	}
}
void timer1init(){
	TCNT1 = 0;										// Set timer1 count zero
	ICR1 = 20000;									// Set TOP count for timer1 in ICR1 register
	TCCR1A=(1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);    // Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/8
	TCCR1B=(1<<WGM13) | (1<<WGM12) | (1<<CS11);
	OCR1A=1000; // goc -90 do
	OCR1B=1000;
}
int main(void)
{	
	//PORTA=(1<<PA0)|(1<<PA1)|(1<<PA2)|(1<<PA3)|(0<<PA4)|(0<<PA5)|(0<<PA6)|(0<<PA7); // set 4 chan PORTA input
	//DDRA=(0<<PA0)|(0<<PA1)|(0<<PA2)|(0<<PA3)|(0<<PA4)|(0<<PA5)|(0<<PA6)|(0<<PA7);
	PORTA=0xFF;
	DDRA=0x00;
	PORTB=0xFF;// init input portB
	DDRB=0x00;

	PORTC=0x00;// 
	DDRC=0xFF;

	DDRD=(1<<PD5)|(1<<PD4); // set hai chan dieu xung  timer 1 la output
	
	i2c_init();
	i2c_lcd_init();
	UARTinit();
	TIMER0init();
	timer1init();
	sei();
	while (1) 
	{
		if((dem-last)>=1000){// dem thoi gian hoat dong su dung timer 0 don vi (ms)
			read_dht11();//ham can thuc hien 1s 1 lan
			last=dem=0;
		}
		button_send1();// nut nhan phan cung
		read_rain_sensor();
		read_gas_sensor1();
	}
}
ISR (TIMER0_OVF_vect){
	TCNT0=130;
	dem++;
}
ISR(USART_RXC_vect){
	char c=UDR;
	switch(c){
		case 'A':{
			tbi(PORTC,2);
			break;
		}
		case 'B':{
			tbi(PORTC,3);
			break;
		}
		case 'C':{
			tbi(PORTC,4);
			break;
		}
		case 'D':{
			tbi(PORTC,5);
			break;
		}
		case 'E':{
			tbi(PORTC,6);
			break;
		}
		case 'F':{
			tbi(PORTC,7);
			break;
		}
		case 'G':{ // cua bep
			if (OCR1A==1000)// neu dong thi mo
				OCR1A=2000;
			else OCR1A=1000; // nguoc lai
			break;
		}
		case 'H':{ // phoi do
			if (OCR1B==1000)// neu khong phoi thi phoi
				OCR1B=2000;
			else OCR1B=1000; // neu phoi thi lay vao
			break;
		}
	}
}



