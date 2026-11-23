#include<lpc21xx.h>
#include"delay.h"
#define lcd_d 0xff<<8
#define rs 1<<16
#define e 1<<18

typedef unsigned int U32;
typedef unsigned char U8;
typedef signed char S8;
typedef float F32;


void LCD_CMD(U8 d)
{
	IOPIN0 = d<<8;
	IOCLR0 = rs;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;
}

void LCD_DATA(char d)
{
	IOPIN0 = d<<8;
	IOSET0 = rs;
	IOSET0 =e;
	delay_ms(2);
	IOCLR0 =e;
}

void LCD_INIT(void)
{
	IODIR0 |= lcd_d|rs|e;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}

void LCD_STR(char *s)
{
	while(*s)
		LCD_DATA(*s++);
}

void LCD_INT(int n)
{
	S8 arr[5],i=0;
	if(n==0)
		LCD_DATA('0');
	else
	{
		   if(n<0)
		   {
				 LCD_DATA('-');
				 n=-n;
       }
	      while(n>0)
      	{
		     arr[i++]=n%10;
		     n=n/10;
        }
        for(--i;i>=0;i--)
   	      LCD_DATA(arr[i]+48);
  }
}
void Float_display(F32 f_val)
{
  U32 number;
  number = f_val;
  LCD_INT(number);
  LCD_DATA('.');
  number=(f_val-number)*100;
  LCD_INT(number);	
}	  

