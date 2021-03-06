/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/


/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
volatile uint16_t i = 0;
 char lcd_string[3];
/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor */
    
    //char lcd_string[3];

    lcd_init(LCD_DISP_ON);

    // Display string without auto linefeed
    lcd_puts("Counter: ");   
    itoa(i , lcd_string , 10);
    lcd_puts(lcd_string);
    /*itoa(i , lcd_string , 16);
    lcd_gotoxy(0,1);
    lcd_putc('$');
    lcd_puts(lcd_string);
    itoa(i , lcd_string , 2);
    lcd_gotoxy(6,1);
    lcd_puts("0b");
    lcd_puts(lcd_string);*/
    // TODO: Display variable value in decimal, binary, and hexadecimal

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);       //OBNOVOVACI
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */
    
    uint8_t  lcd_user_symbols [8*2] = {0x04,  0x0E,  0x11,  0x11,  0x11,  0x11,  0x11,  0x1F, 0x0A, 0x04, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00};
    lcd_command(1<<LCD_CGRAM);

    for(int j= 0; j<16; j++) 
    {
        lcd_data(lcd_user_symbols [j]);
   
    }

    lcd_gotoxy(14,0);
    lcd_putc (0x00);
    lcd_putc (0x01);

    itoa(i , lcd_string , 10);
    lcd_gotoxy(0,1);  
    lcd_putc(0xFF);
    
    for (i=0;i<256; i++)
    {
        if (i==15) 
        {
        lcd_gotoxy(1,1);
        }
        if (i==31) 
        {
         lcd_gotoxy(2,1);
        }
    }      
    


    

    //lcd_init(LCD_DISP_ON_CURSOR_BLINK)
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)
{

    if (i > 255) 
    {
        i = 0;
    }
    char lcd_string[3];

    itoa(i , lcd_string , 10);
    lcd_gotoxy(9,0);
    lcd_puts("   ");  
    lcd_gotoxy(9,0);
    lcd_puts(lcd_string);

    /*itoa(i , lcd_string , 16);
    lcd_gotoxy(1,1);
    lcd_puts("   "); 
    lcd_gotoxy(1,1);
    lcd_puts(lcd_string);

    itoa(i , lcd_string , 2);
    lcd_gotoxy(8,1);
    lcd_puts("      "); 
    lcd_gotoxy(8,1);
    lcd_puts(lcd_string);*/

    i++;

}