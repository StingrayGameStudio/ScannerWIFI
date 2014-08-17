

#include "lcd_lib.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

void LCDsendChar(unsigned char ch)		//Sends Char to LCD
{
	LDP=(ch>>4);
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LDP=((ch&0b00001111));
	LCP|=1<<LCD_RS;
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	LCP&=~(1<<LCD_RS);
	_delay_ms(1);
}
void LCDsendCommand(unsigned char  cmd)
{
	LCP&=~(1<<LCD_RS);
	//4 bit part
	LDP=(cmd>>4);
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	LDP=((cmd&0b00001111));
	LCP|=1<<LCD_E;
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
}
void LCDinit(void)
{
	//4 bit part
	_delay_ms(15);
	LDP=0x00;
	LCP=0x00;
	LDDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCDR|=1<<LCD_E;LCDR|=1<<LCD_RS;
   //---------one------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCP|=1<<LCD_E;LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-----------two-----------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCP|=1<<LCD_E;LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//-------three-------------
	LDP=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4;
	LCP|=1<<LCD_E;LCP&=~(1<<LCD_RS);
	_delay_ms(1);
	LCP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------4 bit--dual line---------------
	LCDsendCommand(0b00101000);
}			
void LCDclr(void)
{
	LCDsendCommand(1<<LCD_CLR);
}
void LCDhome(void)
{
	LCDsendCommand(1<<LCD_HOME);
}
void LCDstring(char * data, uint8_t nBytes)
{
register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		if(data[i]==0)break;
		LCDsendChar(data[i]);
	}
}
void LCDGotoXY(uint8_t _x, uint8_t _y)
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(_y)
	{
	case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+_x; break;
	case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+_x; break;
	case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+_x; break;
	case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+_x; break;
	default: DDRAMAddr = LCD_LINE0_DDRAMADDR+_x; break;
	}
	// set data address
	LCDsendCommand((1<<LCD_DDRAM) | DDRAMAddr);
	
}

void LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		LCDsendCommand(a++);
		LCDsendChar(pcc);
		}
}

void LCDshiftLeft(uint8_t n)
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x1E);
	}
}
void LCDshiftRight(uint8_t n)
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x18);
	}
}
void LCDcursorOn(void)
{
	LCDsendCommand(0x0E);
}
void LCDcursorOnBlink(void)
{
	LCDsendCommand(0x0F);
}
void LCDcursorOFF(void)
{
	LCDsendCommand(0x0C);
}
void LCDblank(void)
{
	LCDsendCommand(0x08);
}
void LCDvisible(void)
{
	LCDsendCommand(0x0C);
}
void LCDcursorLeft(uint8_t n)
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x10);
	}
}
void LCDcursorRight(uint8_t n)
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x14);
	}
}
