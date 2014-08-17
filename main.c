#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd/lcd_lib.h"

int main(void) {
    DDRB |= 1<<PB0; /* set PB0 to output */

	LCDinit();

	LCDclr();
	LCDvisible();

	LCDGotoXY(0,0);

	LCDstring("HelloWorld", 10);

	while(1) {
    }
    return 0;
}
