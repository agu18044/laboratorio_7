
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>

#define _tmr0_value 61

void setup(void);

void __interrupt()isr(void){
    {
        if(T0IF == 1){
            PORTA++;
            T0IF = 0;
            TMR0 = _tmr0_value;
        }
        if (RBIF == 1){
        if (PORTBbits.RB0 == 0) {
            PORTC++;  //se aumenta el valor en contador leds
        }
        if  (PORTBbits.RB1 == 0){
            PORTC--;  //se disminuye el valor en contador leds
        }
        INTCONbits.RBIF = 0;
        }
    }
}

void main (void){
    setup();
    while(1){
         PORTD = 3; 
    }
}

void setup(void){
        ANSEL = 0;
        ANSELH = 0;
        
        TRISA = 0;
        TRISB = 3;
        TRISC = 0;
        TRISD = 0;
        
        PORTA = 0;
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;
    //CONFIG RELOJ    
        OSCCONbits.IRCF = 0b0110; //4Mhz
        OSCCONbits.SCS = 1; 
        
    //CONFIG TIMER0
        OPTION_REGbits.T0CS = 0;
        OPTION_REGbits.PSA = 0;
        OPTION_REGbits.PS2 = 1;  // Prescaler 111   1:256
        OPTION_REGbits.PS1 = 1;
        OPTION_REGbits.PS0 = 1;
        
    //CONFIG INTERRUPTS
        INTCONbits.GIE = 1;
        INTCONbits.RBIE = 1;    //interrupcion del puerto B
        INTCONbits.RBIF = 0;
        INTCONbits.T0IE = 1;    //interrupciones del TMR0
        INTCONbits.T0IF = 0;
        TMR0 = _tmr0_value;
       
    //CONFIG PULL-UPS
        OPTION_REGbits.nRBPU = 0;
        WPUB = 0b00000011;
        IOCBbits.IOCB0 = 1;     //pull-ups para pines en puerto B
        IOCBbits.IOCB1 = 1;    
}