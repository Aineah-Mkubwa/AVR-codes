#include<avr/io.h>
#include<util/delay.h>

#define LCD_data        PORTD
#define LCD_control     PORTB
#define LCD_data_dir    DDRD
#define LCD_command_dir DDRB

#define Reg_sel         PB0
#define Red_Writ        PB1
#define Enable          PB2
void LCDinit(void);
void send_command(unsigned char command);
void send_data(unsigned char data);
void send_string(char *str);

int main()
{
    LCDinit();
    while(1)
    {
     send_command(0x80);
     send_string("H"); 

     }
}

void send_command(unsigned char command)
{
LCD_control &=~(1<<Reg_sel | 1<< Red_Writ);
LCD_data=command;
LCD_control |=1<<Enable;
_delay_us(1);
LCD_control &= ~(1<<Enable);
_delay_ms(3);
}
void LCDinit()
{
LCD_data_dir=0b1111111111;
LCD_command_dir=0xFF;// setting both data           and direction ports as outputs
 _delay_ms(20);
send_command(0x38);//initialize 1602 in 8 bit mode
send_command(0x0E);//
send_command(0x06);
send_command(0x01);
_delay_ms(2);
send_command(0x80);
}
void send_data(unsigned char data)
{
LCD_control &=~(1<< Red_Writ);
LCD_control |=1<<Red_Writ;
LCD_data=data;
LCD_control |=1<<Enable;
_delay_ms(1);
LCD_control &= ~(1<<Enable);
_delay_ms(1);
}
void send_string(char* str)
{
int i;
for(i=0;str[i]!=0;i++)  
{
 send_data(str[i]);
}
}