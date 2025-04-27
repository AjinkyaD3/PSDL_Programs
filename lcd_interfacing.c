#include <p18f4550.h>
#include <xc.h> // Contains PIC18F4550 specifications

#define LCD_RS LATAbits.LATA0 // Define LCD Register Select Pin
#define LCD_EN LATAbits.LATA1 // Define LCD Enable Pin
#define LCDPORT LATB          // Define LCD Data Port

// Delay function
void lcd_delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
    {
        for (j = 0; j < 100; j++);
           
    }
}

// Send Instruction/Command to LCD
void SendInstruction(unsigned char command)
{
    LCD_RS = 0;        // RS low : Instruction Register
    LCDPORT = command; // Put command on data lines
    LCD_EN = 1;        // EN High
    lcd_delay(10);
    LCD_EN = 0; // EN Low; command sampled at falling edge
    lcd_delay(10);
}

// Send Data to LCD
void SendData(unsigned char lcddata)
{
    LCD_RS = 1;        // RS High : Data Register
    LCDPORT = lcddata; // Put data on data lines
    LCD_EN = 1;        // EN High
    lcd_delay(10);
    LCD_EN = 0; // EN Low; data sampled at falling edge
    lcd_delay(10);
}

// LCD Initialization
void InitLCD(void)
{
    ADCON1 = 0x0F;        // Set all pins as digital
    TRISB = 0x00;         // Set PORTB as output for data
    TRISAbits.TRISA0 = 0; // Set RA0 as output (RS)
    TRISAbits.TRISA1 = 0; // Set RA1 as output (EN)

    SendInstruction(0x38); // 8-bit mode, 2 lines, 5x7 dots
    SendInstruction(0x06); // Entry mode set
    SendInstruction(0x0C); // Display ON, Cursor OFF
    SendInstruction(0x01); // Clear display
    SendInstruction(0x80); // Set DDRAM address to 1st line
}

// Global Strings to display
unsigned char *String1 = "Microembedded";
unsigned char *String2 = "PIC-18F Board";

// Main function
void main(void)
{
    InitLCD(); // Initialize LCD

    // Display first string
    while (*String1)
    {
        SendData(*String1);
        String1++;
    }

    // Move cursor to second line
    SendInstruction(0xC0); // Set DDRAM address to 2nd line

    // Display second string
    while (*String2)
    {
        SendData(*String2);
        String2++;
    }

    while (1)
        ; // Infinite loop
}

// #include <p18f4550.h>

// #define LCD_EN LATAbits.LA1
// #define LCD_RS LATAbits.LA0
// #define LCDPORT LATB

// void lcd_delay(unsigned int time) {
//     unsigned int i, j;
//     for (i = 0; i < time; i++) {
//         for (j = 0; j < 100; j++);
//     }
// }

// void SendInstruction(unsigned char command) {
//     LCD_RS = 0;
//     LCDPORT = command;
//     LCD_EN = 1;
//     lcd_delay(10);
//     LCD_EN = 0;
//     lcd_delay(10);
// }

// void SendData(unsigned char lcddata) {
//     LCD_RS = 1;
//     LCDPORT = lcddata;
//     LCD_EN = 1;
//     lcd_delay(10);
//     LCD_EN = 0;
//     lcd_delay(10);
// }

// void InitLCD(void) {
//     ADCON1 = 0x0F;
//     TRISB = 0x00;
//     TRISAbits.RA0 = 0;
//     TRISAbits.RA1 = 0;

//     SendInstruction(0x38);
//     SendInstruction(0x06);
//     SendInstruction(0x0C);
//     SendInstruction(0x01);
//     SendInstruction(0x80);
// }

// unsigned char String1[] = "Microembedded";
// unsigned char String2[] = "PIC-18F Board";

// void main(void) {
//     unsigned char *ptr1 = String1;
//     unsigned char *ptr2 = String2;

//     InitLCD();

//     while (*ptr1) {
//         SendData(*ptr1++);
//     }

//     SendInstruction(0xC0);

//     while (*ptr2) {
//         SendData(*ptr2++);
//     }

//     while (1);
// }
