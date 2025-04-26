#include <pic18f4550.h>
#include <xc.h>

void main(void) {
    int num1 = 0x10;  // 16 in decimal
    int num2 = 0x04;  // 4 in decimal
    int result;

    result = num1 / num2;  // Division operator works fine

    TRISB = 0;  // Set PORTB pins as output
    LATB = result; // Output the result to PORTB

    while (1);  // Infinite loop to keep the program running
}

/* Alternative implementation using repeated subtraction
#include <pic18f4550.h>
#include <xc.h>

void main(void) {
    int num1 = 0x10;  // 16 in decimal
    int num2 = 0x04;  // 4 in decimal
    int result = 0;

    while (num1 >= num2) {  // Subtract num2 from num1 until num1 < num2
        num1 -= num2;
        result++;
    }

    TRISB = 0;  // Set PORTB pins as output
    LATB = result; // Output the result of the manual division

    while (1);  // Infinite loop to keep the program running
}
*/ 