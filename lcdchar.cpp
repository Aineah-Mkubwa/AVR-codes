#include<avr/io.h>
#include<util/delay.h>
#define LCD_data      PORTD 
#define LCD_control   PORTB  
#define Data_dir      DDRD
#define Control_dir   DDRB
#define Rs           PB0
#define Rw            PB1
#define En            PB2
void check_busy(void);
void peek_A_Boo(void);
void send_command(unsigned char command);
void send_data(unsigned char data);

int main()
{
    Control_dir |=1<<En |  1<<Rw  | 1<<Rs;
    _delay_ms(20);
    send_command(0x01);//clear screen
    _delay_ms(2);
    send_command(0x38);//8-bit mode for 1602 lcd
    _delay_us(50);
    send_command(0b00001110);//disp on3, disp pos, on, blink 0
     _delay_us(50);
    send_data(0x41); // send A to LCD
     send_data('Ab');
    while(1)
    {
     
    }
}

void peek_A_Boo(void)
{
LCD_control |= 1<<En;
_delay_ms(1);
LCD_control |= 1<<En;
_delay_ms(3);
}
void send_command(unsigned char command)
{
check_busy();
LCD_data=command; 
LCD_control &=~(1<<Rw | 1<<Rs); //sending command to lcd
peek_A_Boo();
LCD_data=0;
}
void send_data(unsigned char data)
{
    check_busy();
LCD_data=data; 
LCD_control &= ~(1<<Rw);
LCD_control |=1<<Rs; //sending data to lcd
peek_A_Boo();
LCD_data=0; 
}
void check_busy() //D7=1 when busy, otherwise 0 
{
Data_dir=0;//setting DDRA as input
LCD_control|=1<<Rw;
LCD_control &= ~(1<<Rs);
while(LCD_data>=0x80)
{
peek_A_Boo();
}
Data_dir=0xFF; //setting DDRA as o/p
}