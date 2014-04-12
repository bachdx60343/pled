#include <pLED.h>
//#include "PIC16F887_registers.h"
//#include <stdlibm.h>
#include "24256.c"
#include "74595.c"
#include "ds1307.c"

int8 timer1_overflow;
int32 sigHall_timer;
BYTE port_b, last_b;
int8 cycle_trigger;
int8 section_trigger;
int8 section_count;
int16 section_timer;
signed int8 tuning;
int8 mode;
int8 day, month, year, dow;
int8 hour, min, sec;
int8 tick, digit_sec;
int8 h_high, h_low, m_high, m_low, anal_hour;
int8 day_h, day_l, month_h, month_l;
int8 ast_count;
int8 pled_position, pled_direction, pled_count, pled_on;

#PRIORITY INT_CCP1, INT_TIMER0, INT_EXT, INT_RB

#INT_EXT
void EXT_isr(){
	tick += 1;
	sec++;
	if(pled_position == 20) pled_direction = 1;
	else if(pled_position == 50) pled_direction = 0;
	if(pled_direction == 0) pled_position--;
	else if(pled_direction == 1) pled_position++;
}

#INT_RB
void  RB_isr(void) 
{
   BYTE changes;
   port_b = input_b();
   changes = last_b ^ port_b;
   last_b = port_b;
   if(bit_test(changes, 2))
   {
      mode = MODE_A;
      //tuning = 6;
      //section_timer = 64220;
   }
   if(bit_test(changes, 3))
   {
      mode = MODE_B;
      //tuning = 7;
      //section_timer = 64230;
   }
   if(bit_test(changes, 4))
   {
      mode = MODE_C;
      //tuning = 8;
      //section_timer = 64240;
   }
   if(bit_test(changes, 5))
   {
      mode = MODE_D;
      //tuning = 9;
      //section_timer = 64250;
   }
}

#INT_TBE
void  TBE_isr(void) 
{

}

#INT_RDA
void  RDA_isr(void) 
{

}

#INT_TIMER1
void  TIMER1_isr(void) 
{
   timer1_overflow++;
   //section_trigger = 1;
   //set_timer1(section_timer);
}

#INT_CCP1
void  CCP1_isr(void) 
{
   sigHall_timer = ((int32)timer1_overflow * 0xFFFF + CCP_1);
   timer1_overflow = 0;
   set_timer1(0);
   cycle_trigger = 1;
   //section_count = MAX_SECTION;
   //section_trigger = 1;
   //set_timer0(section_timer);
}

#INT_TIMER0
void  TIMER0_isr(void) 
{
   section_trigger = 1;
   //set_timer0(section_timer);
}

void var_init()
{
   timer1_overflow = 0;
   sigHall_timer = 0;
   cycle_trigger = 0;
   port_b = 0x00;
   last_b = port_b;
   tuning = 6;
   mode = 2;
	ast_count=0;
   tick = 1;
   digit_sec = 0;
   pled_position = 31;
   pled_direction = 1;
   pled_count = 0;
   pled_on = 0;
}

void main()
{
   var_init();
	setup_timer_1(T1_INTERNAL | T1_DIV_BY_2);      //div 2 - 26.2 ms overflow
	setup_ccp1(CCP_CAPTURE_FE);
   ds1307_init();
   //with 819.2 us overflow for Timer0, motor's speed must be at least 20 RPS
   setup_timer_0(T0_INTERNAL | T0_DIV_16); //div 16 - 819.2 us overflow
   
   enable_interrupts(INT_RB2|INT_RB3|INT_RB4|INT_RB5);;
   //enable_interrupts(INT_TBE);
   //enable_interrupts(INT_RDA);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_CCP1);
   enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);
  	
	rgb_bits.blue =  0x0001;
	rgb_bits.red =   0xC000;
	rgb_bits.green = 0xFFFF;
	latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
   //ds1307_set_date_time(10,4,14,5,19,49,30);
	ds1307_get_time(hour, min, sec);
	ds1307_get_date(day, month, year, dow);
	//write_eeprom(0, min);
   anal_hour = hour % 12;
   anal_hour = anal_hour * 5;
   anal_hour = anal_hour + (int8)(min / 12);
   
   h_high = (int8)(hour / 10);
	h_low = hour % 10;
	m_high = (int8)(min / 10);
	m_low = min % 10;
  	
	day_h = (int8)(day / 10);
	day_l = day % 10;
	month_h = (int8)(month / 10);
	month_l = month % 10;
  
   while(true)
   {
		if(tick == 300)
		{
			ds1307_get_time(hour, min, sec);
			ds1307_get_date(day, month, year, dow);
		   anal_hour = hour % 12;
			anal_hour = anal_hour * 5;
			anal_hour = anal_hour + (int8)(min / 12);
		   tick = 1;
		}
		if(sec > 59)
		{
			sec = 0;
			min++;
			if(min > 59)
			{
				min = 0;
				ds1307_get_time(hour, min, sec);
				//write_eeprom(0, min);
				anal_hour = hour % 12;
			   anal_hour = anal_hour * 5;
			   anal_hour = anal_hour + (int8)(min / 12);
			}
			h_high = (int8)(hour / 10);
			h_low = hour % 10;
			m_high = (int8)(min / 10);
			m_low = min % 10;
		}
		if(cycle_trigger == 1)
		{
			cycle_trigger = 0;
			latch_ClearAll();
			digit_sec++;
			section_trigger = 1;
			section_count = MAX_SECTION;
			section_timer = 256 - (int8)(sigHall_timer / (MAX_SECTION * 8)) + tuning;
//!			if(section_count == 30)
//!			{
//!				section_timer = 256 - (int8)(sigHall_timer / (MAX_SECTION * 8)) + tuning;
//!				//section_timer = 87 + tuning;
//!			}
	      
			while(cycle_trigger == 0 && section_count > 0)
			{ 	
				if(section_trigger == 1)
				{
					//latch_enable();
					set_timer0(section_timer);
					section_trigger = 0;
					fetch_data();
					latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
					if(section_count > 1) latch_ClearAll();
					section_count--;
				}
			}
		}
   }
}

void fetch_data()
{
	if(mode == MODE_A)
	{
		int8 pos = section_count;
		if(section_count == 60)
		pos = 0;
		rgb_bits.blue =  0x0001;
		rgb_bits.red =   0x0001;
		rgb_bits.green = 0x0001;
		if((section_count % 5) == 0)
		{
			rgb_bits.blue =  0x0003;
			rgb_bits.red =   0x0003;
			rgb_bits.green = 0x0003;
		}
		if((section_count % 15) == 0)
		{
			rgb_bits.blue =  0x007;
			rgb_bits.red =   0x007;
		}
		if(pos == anal_hour)
		{
			rgb_bits.blue = 0xFC00;
		}
		if(pos == min)
		{
			rgb_bits.red = 0xFF00;
		}
		if(pos == sec)
		{
			rgb_bits.green = 0xFFF1;
		}
	}
	else if(mode == MODE_C)
	{
		rgb_bits.blue = fpt[section_count * 3 - 3];
		rgb_bits.red = fpt[section_count * 3 - 2];
		rgb_bits.green = fpt[section_count * 3 - 1];
	}
	else if(mode == MODE_B)
	{
		rgb_bits.red = 0x8000;
		switch (section_count)
		{
			case 52:
				rgb_bits.green = number_upper[h_high][0];
				break;
			case 53:
				rgb_bits.green = number_upper[h_high][1];
				break;
			case 54:
				rgb_bits.green = number_upper[h_high][2];
				break;
			case 56:
				rgb_bits.green = number_upper[h_low][0];
				break;
			case 57:
				rgb_bits.green = number_upper[h_low][1];
				break;
			case 58:
				rgb_bits.green = number_upper[h_low][2];
				break;
			case 2:
				rgb_bits.green = number_upper[m_high][0];
				break;
			case 3:
				rgb_bits.green = number_upper[m_high][1];
				break;
			case 4:
				rgb_bits.green = number_upper[m_high][2];
				break;
			case 6:
				rgb_bits.green = number_upper[m_low][0];
				break;
			case 7:
				rgb_bits.green = number_upper[m_low][1];
				break;
			case 8:
				rgb_bits.green = number_upper[m_low][2];
				break;
			case 60:
				if(digit_sec < 10)
					rgb_bits.green = 0x00A0;
				else
					rgb_bits.green = 0x0000;
				if(digit_sec == 30)
					digit_sec = 0;
				break;
			  	
			case 39:
				rgb_bits.blue = number_lower[day_h][2];
				break;
			case 38:
				rgb_bits.blue = number_lower[day_h][1];
				break;
			case 37:
				rgb_bits.blue = number_lower[day_h][0];
				break;
			case 35:
				rgb_bits.blue = number_lower[day_l][2];
				break;
			case 34:
				rgb_bits.blue = number_lower[day_l][1];
				break;
			case 33:
				rgb_bits.blue = number_lower[day_l][0];
				break;
			case 27:
				rgb_bits.blue = number_lower[month_h][2];
				break;
			case 26:
				rgb_bits.blue = number_lower[month_h][1];
				break;
			case 25:
				rgb_bits.blue = number_lower[month_h][0];
				break;
			case 23:
				rgb_bits.blue = number_lower[month_l][2];
				break;
			case 22:
				rgb_bits.blue = number_lower[month_l][1];
				break;
			case 21:
				rgb_bits.blue = number_lower[month_l][0];
				break;
			case 29:
				rgb_bits.blue = 0x0040;
				break;
			case 30:
				rgb_bits.blue = 0x0040;
				break;
			case 31:
				rgb_bits.blue = 0x0040;
				break;
			default:
				rgb_bits.green = 0x0000;
				rgb_bits.blue = 0x0000;
				break;
		}  	
	}
	else if (mode == MODE_D)
	{
		//rgb_bits.blue = asterisk[ast_count][0];
		//rgb_bits.red = asterisk[ast_count][1];
		//rgb_bits.green = asterisk[ast_count][2];
		//if (ast_count > 8){ ast_count=0;} else ast_count++;
	  	
		rgb_bits.blue = 0x0000;
		rgb_bits.red = 0x0000;
		rgb_bits.green = 0x0000;
	  	
		if (section_count == pled_position)
		{
			pled_on = 1;
			pled_count = 14;
		}
		else if (section_count == pled_position - 15)
		{
			pled_on = 0;
		}
		if (pled_on == 1)
		{
			if(pled_count >=0 && pled_count < 15)rgb_bits.red = pled[pled_count];
			pled_count--;
		}
	}
}
