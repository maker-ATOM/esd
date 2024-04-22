/*
 * lcd.c
 *
 *  Created on: Mar 10, 2021
 *      Author: MicroEmbedded
 */
#include "main.h"

void lcd_enable(void)
{
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, 0);
	HAL_Delay(1);
}


 void lcd_data(unsigned char dat)
 {
	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 1);		//RS=1 for LCD Data

	 //D0
	 if(dat & 0x01)
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);
	 else
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);
	 //D1
 	 if(dat & 0x02)
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 0);
 	//D2
	 if(dat & 0x04)
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 1);
	 else
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 0);
	 //D3
 	 if(dat & 0x08)
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 0);
 	 //D4
  	 if(dat & 0x10)
  		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
  	 else
  		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 0);
  	//D5
 	 if(dat & 0x20)
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);
 	//D6
  	 if(dat & 0x40)
  		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 1);
  	 else
  		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 0);
  	//D7
 	 if(dat & 0x80)
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 0);

lcd_enable();

 }

 void lcd_cmd(unsigned char dat)
 {
	 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 0);		//RS=0 for LCD command

	 //D0
	 if(dat & 0x01)
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 1);
	 else
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, 0);
	 //D1
 	 if(dat & 0x02)
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, 0);
 	//D2
	 if(dat & 0x04)
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 1);
	 else
		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, 0);
	 //D3
 	 if(dat & 0x08)
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 0);
 	 //D4
  	 if(dat & 0x10)
  		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
  	 else
  		 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 0);
  	//D5
 	 if(dat & 0x20)
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, 0);
 	//D6
  	 if(dat & 0x40)
  		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 1);
  	 else
  		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 0);
  	//D7
 	 if(dat & 0x80)
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 1);
 	 else
 		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 0);

lcd_enable();
 }

 void lcd_init(void)
  {
    HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, 0);
 	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, 0);

	lcd_cmd(0x38);						 //8bit use both lines
	lcd_cmd(0x06);						 //Entry mode
	lcd_cmd(0x0C);						 //display ON cursor OFF
	lcd_cmd(0x01);						 //Clear display
	lcd_cmd(0x80);						 //cursor at 1st line 1st position
  }

 void lcd_setcursor(unsigned char row,unsigned char pos)
 {
 lcd_cmd(0x0E);

 if (row == 1)
	lcd_cmd((pos & 0x0F)|0x80);
 else if (row == 2)
	lcd_cmd((pos & 0x0F)|0xC0);
 }

 void lcd_clear(void)
 {
	 HAL_Delay(1);
	 lcd_cmd(0x01);
	 HAL_Delay(1);
 }

 void lcd_displayString(int row, int pos, unsigned char* ch)
 {
	 unsigned char temp;

 	if(row==1)
 	{
 		temp = 0x80 | (pos);			 //set cursor at 1st line pos position
 	}
 	else if(row ==2)
 	{
 		temp = 0xC0 | (pos);			//set cursor at 2nd line pos position
 	}

 	lcd_cmd(temp);

 	while(*ch)							//while data is valid, display the string
		lcd_data(*ch++);
 }

