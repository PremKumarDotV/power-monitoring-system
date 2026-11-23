#include <LPC21xx.h>
#include <stdio.h>
#include "types.h"
#include "spi.h"
#include "mcp3204.h"
#include "lcd.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "delay.h"
#include "kp.h" 
#define SW     (1<<19)      /* P0.19 */
#define bz     (1<<20)      /* P0.20 */

void gsm_send(char *msg)
{
    while (*msg)
    {
        U0THR = *msg;
        while (!(U0LSR & (1 << 5)));
        msg++;
    }
}

void UART0_Init(void)
{
    PINSEL0 |= 0x00000005;   // P0.0=TXD0, P0.1=RXD0

    U0LCR = 0x83;            // 8-bit, 1 stop, no parity, DLAB=1
    U0DLL = 97;              // 9600 baud @ 15MHz VPB clock
    U0DLM = 0;
    U0LCR = 0x03;            // DLAB=0
}

void SMS_ALERT1(void)
{
    gsm_send("AT\r\n");
    delay_ms(500);
    gsm_send("AT+CMGF=1\r\n");
    delay_ms(500);
    gsm_send("AT+CMGS=\"+919444177442\"\r\n");
    delay_ms(500);
    gsm_send("BE ALERT\r\n");
    gsm_send("voltage level exceeded\r\n");
    gsm_send("\x1A");   // Ctrl + Z
    delay_ms(3000);
}

void SMS_ALERT2(void)
{
    gsm_send("AT\r\n");
    delay_ms(500);
    gsm_send("AT+CMGF=1\r\n");
    delay_ms(500);
    gsm_send("AT+CMGS=\"+919444177442\"\r\n");
    delay_ms(500);
    gsm_send("BE ALERT\r\n");
    gsm_send("voltage is very low\r\n");
    gsm_send("\x1A");   // Ctrl + Z
    delay_ms(3000);
}
/*====================== MAIN ======================*/

int main()
{
    f32 voltage;
    f32 current;
    f32 power;
    u8 min_v;
    u8 max_v;
    u8 key;
    u8 sv;
    u8 si;
    u8 sp;
    char buf[16];
	UART0_Init();
    Init_SPI0();
    init_i2c();
    LCD_INIT();
    IODIR0 |= bz;
    IOSET0 |= bz;
	IOPIN0 |= 1<<7;
    LCD_CMD(0x01);
    LCD_STR("POWER MONITOR");
    delay_ms(2000);
    LCD_CMD(0x01);
    LCD_STR("ENTER MIN:");
    LCD_CMD(0xC0);
    key = keyscan();
    min_v = key;
    LCD_DATA(min_v + 48);
    delay_ms(1000);
    LCD_CMD(0x01);
    LCD_STR("ENTER MAX:");
    LCD_CMD(0xC0);
    key = keyscan();
    max_v = key;
    LCD_DATA(max_v + 48);
    delay_ms(1000);
    LCD_CMD(0x01);
    LCD_STR("SYSTEM READY");
	IOSET0 |= 1<<7;
    delay_ms(1500);
    while(1)
    {
        voltage = Read_ADC_MCP3204(0);
        current = voltage / 10.0;
        power = voltage * current;
		LCD_CMD(0x01);
        LCD_CMD(0x01);
        sprintf(buf,"V=%.2f",voltage);
        LCD_STR((unsigned char *)buf);
        LCD_CMD(0xC0);
        sprintf(buf,"I=%.2f",current);
        LCD_STR((unsigned char *)buf); 
        delay_ms(1500);
        LCD_CMD(0x01);
        sprintf(buf,"P=%.2fW",power);
        LCD_STR((unsigned char *)buf);
        delay_ms(1500);
        i2c_eeprom_write(0x50,0x00,(u8)voltage);
        delay_ms(10);
        i2c_eeprom_write(0x50,0x01,(u8)current);
        delay_ms(10);
        i2c_eeprom_write(0x50,0x02,(u8)power);
        delay_ms(10);
        if(((u8)voltage < min_v) || ((u8)voltage > max_v))
        {
            IOCLR0 |= bz;
            LCD_CMD(0x01);
            LCD_STR("VOLT ALERT!");
            LCD_CMD(0xC0);
            LCD_STR("CHECK INPUT");
            if((u8)voltage > max_v)
			     SMS_ALERT1();
			else
			     SMS_ALERT2(); 
            delay_ms(3000);
	        IOSET0 |= bz;
        }
        if((IOPIN0 & SW) == 0)
        {
            sv = i2c_eeprom_read(0x50,0x00);
            delay_ms(10);
            si = i2c_eeprom_read(0x50,0x01);
            delay_ms(10);
            sp = i2c_eeprom_read(0x50,0x02);
            delay_ms(10);
            LCD_CMD(0x01);
            sprintf(buf,"SV=%d SI=%d",sv,si);
            LCD_STR((unsigned char *)buf);
            LCD_CMD(0xC0);
            sprintf(buf,"SP=%d",sp);
            LCD_STR((unsigned char *)buf);
            delay_ms(3000);
			while((IOPIN0 & SW) == 0);
			LCD_CMD(0X01);
        }
    }
}
