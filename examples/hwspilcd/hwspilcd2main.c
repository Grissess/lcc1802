/*
	Display the COSMAC starship on a nokia LCD using hardware SPI shift register
	Nov 12 2013
	Dec 8 using hwspi2 for outboard clock
	Dec 11, finally working after bypassing inverter to MOSR load, changes to clearer etc
	Dec 19 adding Santa Animation
*/
#include <olduino.h>
#include <nstdlib.h>
#include <hspi.h>
#include "hwspilcd.h"
#include <spiship.h>
#include "santaw2.h"
void animate(){
	unsigned int offset;
	for (offset=0;offset<84;offset++){
		gotoXY(0,1); //position to 1st line with ship in it
		digitalWrite(lcdcmd,LCD_D); //get out of command mode
		LcdWriteN(spibytes+84+offset,84-offset);
		if (offset>0){
			LcdWriteN(spibytes+84,offset);
		}
		gotoXY(0,2); //position to 2nd line with ship in it
		digitalWrite(lcdcmd,LCD_D); //get out of command mode
		LcdWriteN(spibytes+168+offset,84-offset);
		if (offset>0){
			LcdWriteN(spibytes+168,offset);
		}
		gotoXY(0,3); //position to 2nd line with ship in it
		digitalWrite(lcdcmd,LCD_D); //get out of command mode
		LcdWriteN(spibytes+252+offset,84-offset);
		if (offset>0){
			LcdWriteN(spibytes+252,offset);
		}
		//delay(100);
	}
}
#define LcdSS 4
void main()
{
 	PIN4=0;
 	setqon();
	LcdInitialise();
	setqoff();
	LcdClear();
	LcdWriteN(santabw2,504);
	while(1);{
	animate();
}
}
#include <hspi2.c>
#include "hwspilcd2.c"
#include <olduino.c>
#include <nstdlib.c>