#ifndef __OLED_H
#define __OLED_H

#include "i2c.h"


void OLED_Init(void);

void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);

void OLED_ShowChar_EN(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
void OLED_ShowNum(uint8_t x,uint8_t y,float num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, char *chr,uint8_t size);	 
void OLED_ShowChar_CN(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]);

#endif  
