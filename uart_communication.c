/* Baud Rate GENERATION
 * n => required baudrate
 * BRGH = 0
 * SPBRG = (Fosc / (64 * n)) - 1
 * For 9600 baudrate, SPBRG ≈ 77
 */

#include <p18F4550.h>
#include <stdio.h>

#define Fosc 48000000UL   // Oscillator frequency

// Initialize UART
void InitUART(unsigned int baudrate) {
    TRISCbits.TRISC6 = 0; // TX pin set as output
    TRISCbits.TRISC7 = 1; // RX pin set as input
    SPBRG = (unsigned char)(((Fosc / 64) / baudrate) - 1); // Baudrate calculation
    
    BAUDCON = 0b00000000; // Non-inverted data; 8-bit baudrate generator
    TXSTA = 0b00100000;   // Asynchronous 8-bit; Transmit enabled; Low speed baudrate
    RCSTA = 0b10010000;   // Serial port enabled; 8-bit data; Single receive enabled
}

// Send a single character
void SendChar(unsigned char data) {
    while (TXSTAbits.TRMT == 0); // Wait until transmit register is empty
    TXREG = data;                // Transmit data
}

// Redirect printf() to UART
void putch(unsigned char data) {
    SendChar(data);
}

// Receive a single character
unsigned char GetChar(void) {
    while (!PIR1bits.RCIF); // Wait until receive buffer becomes full
    return RCREG;           // Return received data
}

// Main function
void main(void) {
    InitUART(9600); // Initialize UART with 9600 baudrate
    
    printf("\r\nHello MicroPIC-18F: Enter any key from Keyboard\r\n");
    
    while (1) {
        printf("%c! ", GetChar()); // Receive character from PC and echo back
    }
} 