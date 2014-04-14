//===========================================================================||
//   pLED - Capstone Project                                                 ||
//   FPT University - Spring 2014                                            ||
//                                                                           ||
// 		Main function, framework for the program                            ||
//                                                                           ||
//   Last edited: 13 - April - 2014                                          ||
//                                                                           ||
//   void var_init() - Initialize global variables' values                   ||
//   void main() - main program, called when the Microcontroller start       ||
//																									  ||
//   There are six Interrupt Service Routine (ISR):                          ||
//					- INT_TIMER1: timer1 interrupt, circle timing                 ||
//					- INT_CCP1: CCP1 interrupt, circle timing                     ||
//					- INT_TIMER0: timer0 interrupt, section timing                ||
//					- INT_EXT: external interrupt, receive clock's SQW/OUT        ||
//					- INT_RB: RB2-RB3-RB4-RB5 input change interrupt, RF signal   ||
//					- INT_RDA: RS232 receive interrupt, for update date, time     ||
//																									  ||
//===========================================================================||

#include "pLED.h"
#include "24256.c"
#include "74595.c"
#include "ds1307.c"
#include "data.c"

#PRIORITY INT_CCP1, INT_TIMER0, INT_EXT, INT_RB

#INT_EXT
void EXT_isr(){
	tick += 1;
	sec++;
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
      smode = 0;
   }
   if(bit_test(changes, 3))
   {
      mode = MODE_B;
      smode = 0;
   }
   if(bit_test(changes, 4))
   {
      mode = MODE_C;
      if (smode == 1)
      	smode = 0;
      else if (smode == 0)
      	smode = 1;
   }
   if(bit_test(changes, 5))
   {
      mode = MODE_D;
      smode = 0;
      if (pled_direction == 1)
      	pled_direction = -1;
      else if (pled_direction == -1)
      	pled_direction = 1;
   }
}

#INT_RDA
void  RDA_isr(void) 
{
   rc = getc();
   switch (rs232_status)
   {
   	case 0:
   		if (rc == 83) rs232_status = 1;
   		break;
   	case 1:
   		if (rc == 84) rs232_status = 2;
   		break;
   	case 2:
   		day = rc;
   		rs232_status = 3;
   		break;
   	case 3:
   		month = rc;
   		rs232_status = 4;
   		break;
   	case 4:
   		year = rc;
   		rs232_status = 5;
   		break;
   	case 5:
   		dow = rc;
   		rs232_status = 6;
   		break;
   	case 6:
   		hour = rc;
   		rs232_status = 7;
   		break;
   	case 7:
   		min = rc;
   		rs232_status = 8;
   		break;
   	case 8:
   		sec = rc;
   		rs232_status = 9;
   		break;
   	case 9:
   		if (rc == 69) rs232_status = 10;
   		break;
   	case 10:
   		if (rc == 68) rs232_status = 11;
   		break;
   	default:
   		//rs232_status = 0;
   		break;
   }
}

#INT_TIMER1
void  TIMER1_isr(void) 
{
   timer1_overflow++;
}

#INT_CCP1
void  CCP1_isr(void) 
{
   sigHall_timer = ((int32)timer1_overflow * 0xFFFF + CCP_1);
   timer1_overflow = 0;
   set_timer1(0);
   circle_trigger = 1;
}

#INT_TIMER0
void  TIMER0_isr(void) 
{
   section_trigger = 1;
}

void var_init()
{
   timer1_overflow = 0;
   sigHall_timer = 0;
   circle_trigger = 0;
   port_b = 0x00;
   last_b = port_b;
   tuning = 6;
   mode = MODE_A;
   smode = 0;
   tick = 1;
   digit_sec = 0;
   pled_position = 31;
   pled_direction = 1;
   pled_count = 0;
   rs232_status = 0;
}

void main()
{
	//initialize data
   var_init();
   //initialize timers and cp1 interrupt
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_2);      //div 2 - 26.2 ms overflow
	setup_ccp1(CCP_CAPTURE_FE);
   //with 819.2 us overflow for Timer0, motor's speed must be at least 20 RPS
   setup_timer_0(T0_INTERNAL | T0_DIV_16); //div 16 - 819.2 us overflow
   //enable interrupts
   enable_interrupts(INT_RB2|INT_RB3|INT_RB4|INT_RB5);;
   //enable_interrupts(INT_TBE);
   //enable_interrupts(INT_RDA);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_CCP1);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(INT_RDA);
	enable_interrupts(GLOBAL);
	//initialize clock
   ds1307_init();
  	
	// power on notice
	rgb_bits.blue =  0xF00F;
	rgb_bits.red =   0x0F0F;
	rgb_bits.green = 0x00FF;
	latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
  	
	//get the first values of date, time
	ds1307_get_time(hour, min, sec);
	ds1307_get_date(day, month, year, dow);
	// calculating hour hand's position for analog clock
   anal_hour = hour % 12;
   anal_hour = anal_hour * 5;
   anal_hour = anal_hour + (int8)(min / 12);
   // calculating hour, minute, day, month numbers to display in digital clock
   hour_h = (int8)(hour / 10);
	hour_l = hour % 10;
	min_h = (int8)(min / 10);
	min_l = min % 10;
	day_h = (int8)(day / 10);
	day_l = day % 10;
	month_h = (int8)(month / 10);
	month_l = month % 10;
  
   // main routine
   while(true)
   {
   	// rs232 operation
   	if (rs232_status == 11)
   	{
   		latch_write(0x0000, 0x0FF0, 0x0000);
   		rs232_status = 0;
   	   ds1307_set_date_time(day, month, year, dow, hour, min, sec);
   	   putc('O');
   	   delay_ms(100);
   	   putc('K');
   	   delay_ms(100);
		   latch_ClearAll();
   	}
   	// get the time value from ds1307 after each 5 minutes
		if(tick == 300)
		{
			ds1307_get_time(hour, min, sec);
			ds1307_get_date(day, month, year, dow);
		   anal_hour = hour % 12;
			anal_hour = anal_hour * 5;
			anal_hour = anal_hour + (int8)(min / 12);
		   tick = 1;
		}
		// change values of minute and hour at appropriate value of second and minute
		if(sec > 59)
		{
			sec = 0;
			min++;
			if(min > 59)
			{
				min = 0;
				ds1307_get_time(hour, min, sec);
				anal_hour = hour % 12;
			   anal_hour = anal_hour * 5;
			   anal_hour = anal_hour + (int8)(min / 12);
			}
			//refresh value for digital clock after each minute
			hour_h = (int8)(hour / 10);
			hour_l = hour % 10;
			min_h = (int8)(min / 10);
			min_l = min % 10;
		}
		//display routine
		if(circle_trigger == 1)
		{  
			circle_trigger = 0;
			latch_ClearAll();
			digit_sec++;
			section_trigger = 1;
			section_count = MAX_SECTION;
			section_timer = 256 - (int8)(sigHall_timer / (MAX_SECTION * 8)) + tuning;
			while(circle_trigger == 0 && section_count > 0)
			{ 	
				if(section_trigger == 1)
				{
					set_timer0(section_timer);
					section_trigger = 0;
					fetch_data();
					latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
					if (smode == 0 && section_count > 1) latch_ClearAll();
					section_count--;
				}
			}
		}// circle_trigger
   } // end of while(true)
}

