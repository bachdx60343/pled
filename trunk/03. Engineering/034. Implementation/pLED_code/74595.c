//===========================================================================||
//   pLED - FPT University                                                   ||
//   Driver for latch 74HC595 - Base on source code from CCS library         ||
//   Last edited: 1 - April - 2014                                           ||
//                                                                           ||
// void latch_write(int16 blue, int16 red, int16 green)                      ||
//                  Writes 48 bits to the 6 chips                            ||
//                                                                           ||
// void latch_ClearAll()      turn off all the leds                          ||
//                                                                           ||
// void latch_SetAll()        turn on all the leds                           ||
//                                                                           ||
//===========================================================================||

#IFNDEF EXP_OUT_ENABLE

#define EXP_OUT_ENABLE  PIN_E2
#define EXP_OUT_CLOCK   PIN_E1
#define EXP_OUT_DO      PIN_E0
#define NUMBER_OF_74595 6

#ENDIF

#INLINE
void latch_write(int16 blue, int16 red, int16 green)
{
	BYTE i;
	output_low(EXP_OUT_CLOCK);
	output_low(EXP_OUT_ENABLE);
  	
	for(i = 16; i > 0; i--)
	{
		if (circle_trigger == 1) break;
		//write green led first, the first bit output will be on the last latch
		if(green & 0x01)
			output_high(EXP_OUT_DO);
		else
			output_low(EXP_OUT_DO);
		shift_right(&green, 2, 0);
		output_high(EXP_OUT_CLOCK);
		output_low(EXP_OUT_CLOCK);
	  	
		//output red
		if(red & 0x01)
			output_high(EXP_OUT_DO);
		else
			output_low(EXP_OUT_DO);
		shift_right(&red, 2, 0);
		output_high(EXP_OUT_CLOCK);
		output_low(EXP_OUT_CLOCK);
	  	
		//output blue
		if(blue & 0x01)
			output_high(EXP_OUT_DO);
		else
			output_low(EXP_OUT_DO);
		shift_right(&blue, 2, 0);
		output_high(EXP_OUT_CLOCK);
		output_low(EXP_OUT_CLOCK);
	}
  	
	output_high(EXP_OUT_ENABLE);
	output_low(EXP_OUT_ENABLE);
}

#INLINE
void latch_ClearAll()
{
	BYTE i;
   output_low(EXP_OUT_CLOCK);
	output_low(EXP_OUT_ENABLE);
	output_low(EXP_OUT_DO);
	for(i = NUMBER_OF_74595 * 8; i > 0; i--)
	{
		output_high(EXP_OUT_CLOCK);
   	output_low(EXP_OUT_CLOCK);
	}
	output_high(EXP_OUT_ENABLE);
   output_low(EXP_OUT_ENABLE);
}

void latch_SetAll()
{
	BYTE i;
   output_low(EXP_OUT_CLOCK);
	output_low(EXP_OUT_ENABLE);
	output_high(EXP_OUT_DO);
	for(i = NUMBER_OF_74595 * 8; i > 0; i--)
	{
		output_high(EXP_OUT_CLOCK);
   	output_low(EXP_OUT_CLOCK);
	}
	output_high(EXP_OUT_ENABLE);
   output_low(EXP_OUT_ENABLE);
}

