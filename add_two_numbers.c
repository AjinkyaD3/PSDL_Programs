#include<pic18f4550.h>
#include<XC.h>

void main(void){

int num1 = 0x02;
int num2 = 0x04;
int sum = num1+num2;
TRISB=0;
PORTB=sum;// here I can either use latb if I am right 
while(1); // while loop so that program does not exit immediately 

} 