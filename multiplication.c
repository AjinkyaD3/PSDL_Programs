#include<pic18f4550.h>
#include<xc.h>

void main(void){
	int num1 = 0x02;
	int num2 = 0x05;

	int sum = num1*num2;

TRISB=0;
LATB=sum;

//or there is an another way of successive addition that will do the same because i dont know normal multiplication works in it or not 

int sum2;
for (int i =0;i<num2;i++){
	sum2+=num1;
}
TRISB=0;
LATB=sum2;
} 