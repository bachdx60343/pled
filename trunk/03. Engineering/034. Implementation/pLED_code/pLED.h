//===========================================================================||
//   pLED - Capstone Project                                                 ||
//   FPT University - Spring 2014                                            ||
//                                                                           ||
//		   Header file for pLED project                                        ||
//                                                                           ||
//   Last edited: 23 - April - 2014                                          ||
//                                                                           ||
//                                                                           ||
//===========================================================================||

#include <16F887.h>
#device ADC=16

#FUSES HS
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES MCLR
#FUSES NOPROTECT
#FUSES NOCPD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES IESO
#FUSES FCMEN
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG
//configuration bits: 2007-2CE2(); 2008-0700(FFFF)

#use delay(crystal=20000000)
#use FIXED_IO( E_outputs=PIN_E2,PIN_E1,PIN_E0 )
#use rs232(baud=19200,parity=E,xmit=PIN_C6,rcv=PIN_C7,bits=8,stop=1,stream=PORT1)

#OPT 1

#define MAX_SECTION 60
#define MODE_A 2
#define MODE_B 3
#define MODE_C 4
#define MODE_D 5

//variables for CCP1 interrupt
int8 timer1_overflow;
int32 sigHall_timer;
//variables for display routine
int8 circle_trigger;
int8 section_trigger;
int8 section_count;
int16 section_timer;
signed int8 tuning;
//variables for RB interrupt, RF input
BYTE port_b, last_b;
int8 mode, smode;
//variables for date, time values
int8 day, month, year, dow;
int8 hour, min, sec;
int8 tick, digit_sec;
//variables for digital clock
int8 hour_h, hour_l, min_h, min_l, anal_hour;
int8 day_h, day_l, month_h, month_l;
//variables for MODE_D, running letters
int8 pled_position;
signed int8 pled_direction, pled_status;
int16 pled_count;
//variables for RS232 communication
int8 rc, rs232_status;

//leds' values at one moment
struct
{
	int16 blue;
	int16 red;
	int16 green;
} rgb_bits;

//number to display at upper position (hour-minute)
const int16 number_upper[10][3] = 
{
	{0x03F8, 0x0208, 0x03F8}, // 0
	{0x0040, 0x0020, 0x03F8}, // 1
	{0x03C8, 0x0248, 0x0278}, // 2
	{0x0248, 0x0248, 0x03F8}, // 3
	{0x0078, 0x0040, 0x03F8}, // 4
	{0x0278, 0x0248, 0x03C8}, // 5
	{0x03F8, 0x0248, 0x03C8}, // 6
	{0x0008, 0x0008, 0x03F8}, // 7
	{0x03F8, 0x0248, 0x03F8}, // 8
	{0x0278, 0x0248, 0x03F8}  // 9
};
//number to display at lower position (day-month)
const int16 number_lower[10][3] = 
{
	{0x03F8, 0x0208, 0x03F8}, // 0
	{0x03F8, 0x0100, 0x0080}, // 1
	{0x03C8, 0x0248, 0x0278}, // 2
	{0x03F8, 0x0248, 0x0248}, // 3
	{0x03F8, 0x0040, 0x03C0}, // 4
	{0x0278, 0x0248, 0x03C8}, // 5
	{0x0278, 0x0248, 0x03F8}, // 6
	{0x03F8, 0x0200, 0x0200}, // 7
	{0x03F8, 0x0248, 0x03F8}, // 8
	{0x03F8, 0x0248, 0x03C8}  // 9
};

//data for MODE_C, FPT logo
const int16 fpt_blue[60] = 
{
	0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,
	0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,
	0x8000,0x8000,0x8001,0xC003,0xE007,0xC00F,0x801F,0x803F,0x807F,0xC0FF,
	0xE07F,0xC03F,0x801F,0x800F,0x8007,0xC003,0xE001,0xC000,0x8000,0x8000,
	0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,
	0x8000,0x8000,0x8000,0xC7F8,0xE7F8,0xC0D8,0x80D8,0x8018,0x8000,0xC000
};

const int16 fpt_red[60] = 
{
	0xE0D8,0xC070,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,
	0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,
	0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,
	0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,
	0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,
	0x8000,0x8000,0x8000,0xC000,0xE000,0xC000,0x8000,0x8000,0x87F8,0xC7F8
};

const int16 fpt_green[60] = 
{
	0x0000,0x0000,0x0018,0x0018,0x07F8,0x07F8,0x0018,0x0018,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0001,0x0003,0x0007,0x000F,0x001F,0x003F,0x007F,0x00FF,
	0x007F,0x003F,0x001F,0x000F,0x0007,0x0003,0x0001,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};

//data for MODE_D, running letters
const int16 pled_inward[15] = 
{
	0x01F0, 0x0208, 0x03F8, 0x0000,
	0x0248, 0x0248, 0x03F8, 0x0000,
	0x0008, 0x0008, 0x03F8, 0x0000,
	0x0040, 0x00A0, 0x00F8
};

const int16 year_2014[15] = 
{
	0x03C8, 0x0248, 0x0278, 0x0000,
	0x03F8, 0x0208, 0x03F8, 0x0000,
	0x0040, 0x0020, 0x03F8, 0x0000,
	0x0078, 0x0040, 0x03F8
};

const int16 flappy1_blue[60] =
{
	0x0300,0x0300,0x0F00,0x1F00,0x3F00,0x3F00,0x3F80,0x3F80,0x3F80,0x3F80,
	0x3F80,0x3F80,0x3F80,0x3F80,0x3C00,0x1800,0x1000,0x0000,0x0000,0x0000,
	0x0080,0x0100,0x0100,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,
	0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x1A00,0x1700,0x1100,
	0x1C80,0x3E40,0x3F40,0x1FC0,0x1FC0,0x1FC0,0x1F00,0x0300,0x0300,0x0300,
	0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300
};

const int16 flappy1_red[60] =
{
	0xFE00,0xFE00,0xF000,0xEE00,0xDE00,0xDE00,0xDF00,0xDF80,0xDF80,0xDD80,
	0xDD80,0xDD80,0xDF80,0xDF80,0xDFE0,0xFFF0,0xFF80,0xFE70,0xFFE0,0xFFC0,
	0xFF00,0xFE00,0xFE00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xE400,0xE800,0xEE00,
	0xFF00,0xFF80,0xFF80,0xFF80,0xFF80,0xFF00,0xE000,0xFC00,0xFE00,0xFE00,
	0xFE00,0xFE00,0xFE00,0xFE00,0xFE00,0xFC00,0xFC00,0xFE00,0xFE00,0xFE00
};

const int16 flappy1_green[60] =
{
	0xFE00,0xFE00,0xF000,0xEE00,0xDE00,0xDE00,0xDF00,0xDF80,0xDF80,0xDD80,
	0xDD80,0xDD80,0xDF80,0xDF80,0xDC00,0xF800,0xF000,0xE000,0xE000,0xE000,
	0xE100,0xF200,0xFE00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xE400,0xE800,0xEE00,
	0xFF00,0xFF80,0xFF80,0xFF80,0xFF80,0xFF00,0xE000,0xFC00,0xFE00,0xFE00,
	0xFE00,0xFE00,0xFE00,0xFE00,0xFE00,0xFC00,0xFC00,0xFE00,0xFE00,0xFE00
};

const int16 flappy2_blue[60] =
{
	0x0300,0x0300,0x0F00,0x1F00,0x3F00,0x3F00,0x3F80,0x3F80,0x3F80,0x3F80,
	0x3F80,0x3F80,0x3F80,0x3F80,0x3C00,0x1800,0x1000,0x0000,0x0000,0x0000,
	0x0080,0x0100,0x0100,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,
	0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,0x0200,
	0x0200,0x0A00,0x1E00,0x1200,0x2180,0x3C40,0x1F40,0x1FC0,0x1F80,0x1F00,
	0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300
};

const int16 flappy2_red[60] =
{
	0xFE00,0xFE00,0xF000,0xEE00,0xDE00,0xDE00,0xDF00,0xDF80,0xDF80,0xDD80,
	0xDD80,0xDD80,0xDF80,0xDF80,0xDFE0,0xFFF0,0xFF80,0xFE70,0xFFE0,0xFFC0,
	0xFF00,0xFE00,0xFE00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xF400,0xE000,0xEC00,0xFE00,0xFF80,0xFF80,0xFF80,0xEE00,0xE000,
	0xFE00,0xFE00,0xFE00,0xFE00,0xFE00,0xFC00,0xFC00,0xFE00,0xFE00,0xFE00
};
const int16 flappy2_green[60] =
{
	0xFE00,0xFE00,0xF000,0xEE00,0xDE00,0xDE00,0xDF00,0xDF80,0xDF80,0xDD80,
	0xDD80,0xDD80,0xDF80,0xDF80,0xDC00,0xF800,0xF000,0xE000,0xE000,0xE000,
	0xE100,0xF200,0xFE00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,0xFC00,
	0xFC00,0xF400,0xE000,0xEC00,0xFE00,0xFF80,0xFF80,0xFF80,0xEE00,0xE000,
	0xFE00,0xFE00,0xFE00,0xFE00,0xFE00,0xFC00,0xFC00,0xFE00,0xFE00,0xFE00
};
