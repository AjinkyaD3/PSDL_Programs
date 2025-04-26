#include <pic18f4550.h>
#include <xc.h>

// Simple delay function using nested loops
void delay(unsigned int time) {
    for (unsigned int i = 0; i < time; i++) {
        for (unsigned int j = 0; j < 100; j++) {
            // Do nothing, just waste time
            ;
        }
    }
}

void main(void) {
    TRISB = 0x00;   // Set PORTB as output
    LATB = 0x00;    // Clear all PORTB outputs

    while (1) {
        LATB = 0xFF;     // Turn ON all LEDs connected to PORTB
        delay(500);      // Delay
        LATB = 0x00;     // Turn OFF all LEDs
        delay(500);      // Delay again
    }
} 