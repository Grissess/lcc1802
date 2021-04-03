/*
    Pixie sprite move example by Marcel van Tongoren 
*/

#include <stdint.h>
#include <nstdlib.h>

#define PIXIE_PATTERN
#define PIXIE_CHECK_BORDER

#include "devkit/video/pixie_video.h"
#include "devkit/input/joystick.h"

#if RES==32
static const uint8_t shape_o[] =
{
	RES/8, 
	0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00,
	0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00,
	0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00,
	0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00,
	0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00,
	0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00,
	0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80,
	0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0,
};

static const uint8_t shape_x[] =
{
	RES/8, 
	0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00,
	0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00,
	0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00,
	0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00,
	0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00,
	0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80,
	0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40,
	0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20,
};
#endif

#if RES==64
static const uint8_t shape_o[] =
{
	RES/8, 
	0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00,
	0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00,
	0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00,
	0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00,
	0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00,
	0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00,
	0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80,
	0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0,
};

static const uint8_t shape_x[] =
{
	RES/8, 
	0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00,
	0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00,
	0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00,
	0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00,
	0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00,
	0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80,
	0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40,
	0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20,
};
#endif

#if RES==128
static const uint8_t shape_o[] =
{
	RES/8, 
	0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00,
	0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00,
	0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00,
	0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00,
	0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00,
	0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00,
	0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80,
	0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0,
};

static const uint8_t shape_x[] =
{
	RES/8, 
	0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00, 0x90, 0x00, 0x60, 0x00, 0x60, 0x00, 0x90, 0x00,
	0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00, 0x48, 0x00, 0x30, 0x00, 0x30, 0x00, 0x48, 0x00,
	0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00, 0x24, 0x00, 0x18, 0x00, 0x18, 0x00, 0x24, 0x00,
	0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x12, 0x00,
	0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00, 0x09, 0x00, 0x06, 0x00, 0x06, 0x00, 0x09, 0x00,
	0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80, 0x04, 0x80, 0x03, 0x00, 0x03, 0x00, 0x04, 0x80,
	0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40, 0x02, 0x40, 0x01, 0x80, 0x01, 0x80, 0x02, 0x40,
	0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20, 0x01, 0x20, 0x00, 0xC0, 0x00, 0xC0, 0x01, 0x20,
};
#endif

uint8_t x, y, x2, y2, delay, collision1, collision2;
unsigned char key;
int lines = RES/8;
uint32_t sprite_data1;
uint32_t sprite_data2;

void middle(){
	x = (uint8_t) ((X_SIZE-4)/2);
    y = (uint8_t) ((Y_SIZE-lines)/2);                   // Set x and y to middle of screen
}

void main(){
	initvideo();

	middle();
	x2 = x+8;
	y2 = y;

	collision1 = showsprite (&sprite_data1, shape_o, x, y);
	collision2 = showsprite (&sprite_data2, shape_x, x2, y2);
	collision1 = 0;
	collision2 = 0;

	while (1) {
		key = get_stick();                  // get direction key value
		if (key != 0)
		{
			collision1 = movesprite(&sprite_data1, key);
			collision2 = movesprite(&sprite_data2, key);
		}

		if (collision1 == 1)
		{
			removesprite (&sprite_data1);
			middle();
			collision1 = showsprite (&sprite_data1, shape_o, x, y);
		}

		if (collision2 == 1)
		{
			removesprite (&sprite_data2);
			x2 = (int) ((X_SIZE-4)/2) + 8;
			y2 = (int) ((Y_SIZE-lines)/2);                   // Set x and y to middle of screen
			collision2 = showsprite (&sprite_data2, shape_x, x2, y);
		}
	}
}
