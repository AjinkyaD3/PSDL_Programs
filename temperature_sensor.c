/*
 * File: temperature_sensor.c
 * Author: MicroEmbedded
 * Created on October 15, 2016, 4:35 PM
 */

#include <pic18f4550.h>
#include <stdio.h>

// LCD Pin Definitions
#define LCD_RS  LATAbits.LATA0
#define LCD_EN  LATAbits.LATA1
#define LCDPORT LATB

unsigned char str[16];

// LCD Delay Function
void lcd_delay(unsigned int time) {
    unsigned int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 100; j++);
    }
}

// Send Command to LCD
void SendInstruction(unsigned char command) {
    LCD_RS = 0;        // RS low : Instruction
    LCDPORT = command;
    LCD_EN = 1;        // EN High
    lcd_delay(10);
    LCD_EN = 0;        // EN Low; command sampled at EN falling edge
    lcd_delay(10);
}

// Send Data to LCD
void SendData(unsigned char lcddata) {
    LCD_RS = 1;        // RS HIGH : DATA
    LCDPORT = lcddata;
    LCD_EN = 1;        // EN High
    lcd_delay(10);
    LCD_EN = 0;        // EN Low; data sampled at EN falling edge
    lcd_delay(10);
}

// Initialize LCD
void InitLCD(void) {
    ADCON1 = 0x0F;               // Set all pins as digital
    TRISB = 0x00;                // Set data port as output
    TRISAbits.TRISA0 = 0;        // RS pin as output
    TRISAbits.TRISA1 = 0;        // EN pin as output

    SendInstruction(0x38);       // 8-bit mode, 2 lines, 5x7 dots
    SendInstruction(0x06);       // Entry mode
    SendInstruction(0x0C);       // Display ON, Cursor OFF
    SendInstruction(0x01);       // Clear display
    SendInstruction(0x80);       // Set address to first line
}

// Display String on LCD at given Row and Position
void LCD_display(unsigned int row, unsigned int pos, unsigned char *ch) {
    if (row == 1)
        SendInstruction(0x80 | (pos - 1));  // First row
    else
        SendInstruction(0xC0 | (pos - 1));  // Second row

    while (*ch)
        SendData(*ch++);
}

// ADC Initialization
void ADCInit(void) {
    TRISEbits.TRISE2 = 1;           // Set RE2 as input (AN7)
    ADCON1 = 0b00000111;         // Reference voltages: Vdd & Vss; AN0-AN7 Analog
    ADCON2 = 0b10101110;         // Right justified; Acquisition time 4TAD; Fosc/64
}

// Read Temperature from ADC Channel
unsigned short Read_Temp(void) {
    ADCON0 = 0b00011101;         // Select Channel AN7; ADC ON
    GODONE = 1;                  // Start Conversion
    while (GO_DONE == 1);        // Wait till conversion completes
    return ADRES;                // Return ADC result
}

// Main Function
int main(void) {
    unsigned int temp;

    InitLCD();
    ADCInit();
    LCD_display(1, 1, "Temperature:");

    while (1) {
        temp = Read_Temp();
        temp = ((temp * 500) / 1023);     // Convert ADC value to temperature
        sprintf(str, "%d'C ", temp);      // Prepare string to display
        LCD_display(2, 1, str);            // Display on LCD
        lcd_delay(9000);                   // Delay between readings
    }

    return 0;
} 