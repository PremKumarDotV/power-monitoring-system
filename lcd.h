


#ifndef LCD_H
#define LCD_H

void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_INIT(void);
void LCD_STR(unsigned char *s);
void LCD_INT(int n);
void Float_display(float f);


#endif
