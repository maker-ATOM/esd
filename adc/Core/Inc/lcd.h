/*
 * lcd.h
 *
 *  Created on: Mar 10, 2021
 *      Author: MicroEmbedded
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
extern void lcd_init(void);
extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_setcursor(unsigned char ,unsigned char );
extern void lcd_clear(void);
extern void lcd_displayString(int , int , unsigned char*);
#endif /* INC_LCD_H_ */
