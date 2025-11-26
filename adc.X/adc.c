/*
 * File:   adc.c
 * Author: admin
 *
 * Created on 6 de noviembre de 2025, 07:22 AM
 */
// PIC16F877A Configuration Bit Settings 

// 'C' source line config statements

// CONFIG
/*#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include "adc.h"
*/
#define _XTAL_FREQ 20000000
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define RS PORTBbits.RB6
#define EN PORTBbits.RB7

void lcdCommand(unsigned char cmd){
    RS = 0;
    PORTD = cmd;
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(1);
};

void lcdSendDataByte(unsigned char data){
    RS = 1;
    PORTD = data;
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(1);
};

void lcd_init(){
    __delay_ms(20);      // power-on wait
    lcdCommand(0x38);    // 8-bit, 2 lines, 5x8
    lcdCommand(0x06);    // entry mode
    lcdCommand(0x0C);    // display ON, cursor OFF (mejor que 0x0F al inicio)
    lcdCommand(0x01);    // clear
    __delay_ms(2);       // >=1.52 ms
    lcdCommand(0x80);    // DDRAM = 0
}

void lcdSendString(char *addr){
    while(*addr){
        lcdSendDataByte(*addr);
        addr++;
    }
}
void adc_init(){
    TRISA = 0x01;
    ADCON1 = 0b11001110;
    ADCON0 = 0b10000001;
     __delay_us(20);
}

unsigned int adc_read_an0(){
    __delay_us(20);
    GO_nDONE = 1;
    while(GO_nDONE);
    return((unsigned int)ADRESH << 8 | ADRESL);
};

void main(void) {
    TRISD = 0x00;
    TRISB = 0x00;
    
    lcd_init();
    adc_init();
    char buffer[16];
    uint16_t prev_mV = 0xff;
    
    while(1){
        uint16_t raw = adc_read_an0();
        uint16_t mV = (uint16_t)raw*5000L/1023U;
        
        if(mV != prev_mV){
            lcdCommand(0x80);
            sprintf(buffer, "RAW:%4u", raw);
            lcdSendString(buffer);
            
            lcdCommand(0xC0);
            sprintf(buffer, "mV:%4u", mV);
            lcdSendString(buffer);
            
            prev_mV = mV;
        }
        __delay_ms(100);
    }
    return;
}
