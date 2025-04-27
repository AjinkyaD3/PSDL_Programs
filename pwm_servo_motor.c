#include <p18f4550.h>

// unsigned char count = 0;
// bit TIMER,SPEED_UP;

void timer2Init(void)
{
    T2CON = 0b00000010; // Prescaler = 16, Timer2 OFF initially
    PR2 = 0x95;         // Period register value (adjusts PWM frequency)
}

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 1000; j++)
            ;
}

void main(void)
{
    unsigned int i;

    TRISCbits.TRISC1 = 0; // Set RC1 pin as output
    TRISCbits.TRISC2 = 0; // Set CCP1 pin (RC2) as output
    LATCbits.LATC1 = 0;   // Initially make RC1 LOW

    CCP1CON = 0b00111100; // (60)  Select PWM mode; CCP1CON<5:4> bits are Duty Cycle LSBs
    CCPR1L = 0x0F;        // Duty Cycle MSB (sets 10% duty cycle approx initially)

    timer2Init();         // Initialize Timer2
    T2CONbits.TMR2ON = 1; // Turn ON Timer2

    while (1) // Infinite loop
    {
        // Increase brightness
        for (i = 15; i < 150; i++)
        {
            CCPR1L = i;
            delay(100);
        }

        // Decrease brightness
        for (i = 150; i > 15; i--)
        {
            CCPR1L = i;
            delay(100);
        }
    }
}
