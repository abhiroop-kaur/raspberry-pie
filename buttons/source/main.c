#include <unistd.h>
#include <stdio.h>
//#include <wiringPi.h>
#include "gpio.h"
#include "uart.h"
#include <uart.h>
#include <stdbool.h>
// unsigned int *gpio = (unsigned int *)0xFE200000;

// defining the macro for the mask to make p an input pin (000)
#define GPIO_BASE 0xFE200000 // Address for GPIOFSELO
unsigned *gpio = (unsigned*) GPIO_BASE; // GPIO base
#define INP_GPIO(p)  *(gpio + ((p)/10)) &= ~(7<<(((p)%10) *3))


// defining the macro for the mask to make p an output pin (001)
// #define GPIO BASE 0xFE200000 // Address for GPIOESELO
// unsigned *gpio = (unsigned*) GPIO_BASE; // GPIO base
#define OUT_GPIO(p)  *(gpio + ((p)/10)) |= (1<<(((p)%10) *3))

#define GPIO_Set_Bit(p) (*(gpio + 7) = (1 << p))
#define GPIO_Clear_Bit(p) (*(gpio + 10) = (1 << p))
#define GPIO_Read_Bit(p) (*(gpio + 13) & (1 << p))

#define Clock 11
#define Data 10
#define Latch 9

unsigned short buttons[15];



#define CLO_REG 0xFE003004

void wait_function(unsigned int time);
void setup();
unsigned short* Read_SNES();


void setup()
{//defining clock
    INP_GPIO(Clock);
    OUT_GPIO(Clock);
    
    INP_GPIO(Latch);
    OUT_GPIO(Latch);

    INP_GPIO(Data);
}
//defining how the wait function will proceed
void wait_function(unsigned int time){
    unsigned *clo = (unsigned *) CLO_REG;
    unsigned c = *clo;
    while(*clo - time < c){}; 
}

unsigned short* Read_SNES()
{
    GPIO_Set_Bit(Clock);
    GPIO_Set_Bit(Latch);
    wait_function(12);
    GPIO_Clear_Bit(Latch);
    for (int i = 0; i < 16; i++)
    {
        wait_function(6);
        GPIO_Clear_Bit(Clock);
        wait_function(6);
        buttons[i] = GPIO_Read_Bit(Data);
        GPIO_Set_Bit(Clock);
    }
    return buttons;
}

int main()
{
    setup();
    uart_puts("Created by: Alokik Singh and Abhiroop Kaur\n");

    unsigned short * buttonPressed;
    bool buttonState = true;
    uart_puts("Press the button: ");

    while (buttonState)
    {//defining different button names
        buttonPressed = Read_SNES();
        if (buttonPressed[0] == 0) {
            uart_puts("B Button Pressed\n");
	    
        }
        
	else  if (buttonPressed[1] == 0) {
            uart_puts("Y Button Pressed\n");
	    
        }

        else if (buttonPressed[2] == 0) {
            uart_puts("Select Button Pressed\n");
	    
        }

	else  if (buttonPressed[3] == 0) {
            uart_puts("Terminating program\n");
            break;
            
        }

        else if (buttonPressed[4] == 0) {
            uart_puts("Up Button Pressed\n");
	    
        }

	else  if (buttonPressed[5] == 0) {
            uart_puts("Down Button Pressed\n");
	    
        }

	else  if (buttonPressed[6] == 0) {
            uart_puts("Left Button Pressed\n");
	    
        }

        else if (buttonPressed[7] == 0) {
            uart_puts("Right Button Pressed\n");
	    
        }

	else  if (buttonPressed[8] == 0) {
            uart_puts("A Button Pressed\n");
	    
        }

	else  if (buttonPressed[9] == 0) {
            uart_puts("X Button Pressed\n");
	    
        }

	else  if (buttonPressed[10] == 0) {
            uart_puts("L Button Pressed\n");
	   
        }

        else if (buttonPressed[11] == 0) {
            uart_puts("R Button Pressed\n");
	    
        }
    // adding wait time
        wait_function(500000); // 1 second delay
    }
    
    return 0;
}


