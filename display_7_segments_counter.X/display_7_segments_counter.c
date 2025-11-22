#define _XTAL_FREQ 20000000
#include <xc.h>
#define debounce_ms 20
unsigned char counter = 0;
//Funcion para antirrebote
unsigned char get_input_debounced(void){
    unsigned char a = PORTBbits.RB3;
    __delay_ms(debounce_ms);
    unsigned char b = PORTBbits.RB3;
    if(a==b){
        return b;
    }
    else{
        return 0xff; //inestabilidad del pin
    }
}

void main(void) {
    TRISA = 0x00;
    TRISB = 0x08;
    TRISE = 0xfc;
    TRISC = 0x7f;
    
    unsigned char counter = 0;
    unsigned char prev = 0;
    
    while(1){
        unsigned char stable = get_input_debounced();
        
        if(stable!=0xff){
            if (stable==1 && prev==0){
                counter++;
            }
            prev = stable;
            
            if(counter==0){
                PORTA = 0xc1;
                PORTE = 0xfe;
            }
            if(counter==1){
                PORTA = 0xf3;
                PORTE = 0xff;
            }
            if(counter==2){
                PORTA = 0xc9;
                PORTE = 0xfd;
            }
            if(counter==3){
                PORTA = 0xe1;
                PORTE = 0xfd;
            }
            if(counter==4){
                PORTA = 0xf3;
                PORTE = 0xfc;
            }
            if(counter==5){
                PORTA = 0xe5;
                PORTE = 0xfc;
            }
            if(counter==6){
                PORTA = 0xc5;
                PORTE = 0xfc;
            }
            if(counter==7){
                PORTA = 0xf1;
                PORTE = 0xff;
            }
            if(counter==8){
                PORTA = 0xc1;
                PORTE = 0xfc;
            }
            if(counter==9){
                PORTA = 0xe1;
                PORTE = 0xfc;
            }
            
            if(counter==10){
            counter=0;
            }
        }
    }
    return;
}
