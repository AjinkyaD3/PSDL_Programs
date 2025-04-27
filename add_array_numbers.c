#include <pic18f4550.h>
#include <xc.h>

void main(void)
{
    int arr[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
    int sum = 0;

    for (int i = 0; i < 5; i++)
    {
        sum += arr[i];
    }

    TRISB = 0;
    LATB = sum;
    // PORTB=sum; latb or portb both can be used
}