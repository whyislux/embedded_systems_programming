/*
 * File:   counter.c
 * Author: admin
 *
 * Created on 30 de octubre de 2025, 07:26 AM
 */

#define _XTAL_FREQ 20000000
#include <xc.h>
unsigned char counter = 0;

void main(void) {
    TRISA = 0x01;
    TRISB = 0x00;
    PORTB = 0x00;
    
    while(1){
        unsigned char button = PORTAbits.RA0;
        
        if(button==1){
            counter++;
        }
        
        if(counter == 10){
            counter = 0;
        }
        
        switch (counter){
                case 0: 
                    PORTB = 0xfc;
                    break;
                    //PORTB = 0b11111100;
                
                case 1: 
                    PORTB = 0x60;
                    break; 
                    //PORTB = 0b01100000;
                    
                case 2: 
                    PORTB = 0xda;
                    break;
                    //PORTB = 0b11011010;
                    
                case 3: 
                    PORTB = 0xf2;
                    break;
                    // PORTB = 0b11110010;
                    
                case 4: 
                    PORTB = 0x66;
                    break;
                    // PORTB = 0b01100110;
                    
                case 5: 
                    PORTB = 0xb6;
                    break;
                    //PORTB = 0b10110110;
                    
                case 6: 
                    PORTB = 0xbe;
                    break;
                    //PORTB = 0b10111110;
                    
                case 7: 
                    PORTB = 0xe0;
                    break;
                    //PORTB = 0b11100000;
                    
                case 8: 
                    PORTB = 0xfe;
                    break;
                    // PORTB = 0b11111110;
                    
                case 9: 
                    PORTB = 0xe6;
                    break;
                    //PORTB = 0b11100110;
        }
    }
    return;
}

