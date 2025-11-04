/*
 * File:   counter.c
 * Author: admin
 *
 * Created on 30 de octubre de 2025, 07:26 AM
 */

#define _XTAL_FREQ 20000000
#include <xc.h>
#define debounce_ms 20
unsigned char counter = 0;
const unsigned char DISPLAY[10] = {
    0xfc,
    0x60,
    0xda,
    0xf2,
    0x66,
    0xb6,
    0xbe,
    0xe0,
    0xfe,
    0xe6,
};

//Funcion para antirrebote
unsigned char get_input_debounced(void){
    unsigned char a = PORTAbits.RA0;
    __delay_ms(debounce_ms);
    unsigned char b = PORTAbits.RA0;
    if(a==b){
        return b;
    }
    else{
        return 0xff; //inestabilidad del pin
    }
}

void main(void) {
    TRISA = 0x01;
    TRISB = 0x00;
    PORTB = DISPLAY[0];
    
    unsigned char counter = 0;
    unsigned char prev = 0;
    
    while(1){
        unsigned char stable = get_input_debounced();
        
        if(stable!=0xff){
            if (stable==1 && prev==0){
                counter++;
                PORTB = DISPLAY[counter];
            }
            prev = stable;
            
            if(counter==10){
            counter=0;
            PORTB = DISPLAY[0];
            }
        }
    }
}

