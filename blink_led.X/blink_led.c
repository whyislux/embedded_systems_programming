/*
 * File:   blink_led.c
 * Author: admin
 *
 * Created on 21 de noviembre de 2025, 10:20 PM
 */
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include "pic16F877AConfig1.h"
#define _XTAL_FREQ 20000000
#include <xc.h>

void main(void) {
    //entrada = 1; salida = 0
    TRISB = 0xff;
    TRISC = 0x00;
    PORTCbits.RC7 = 0;
    
    if(PORTBbits.RB3 == 1){
    PORTCbits.RC7 = 1;
    }
    
    return;
}
