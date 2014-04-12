//test speed
	int i;
	int8  count = 0;
	int8* pt_byte;
   while(true)
   {
   	if(count == 60)
   	{
   		write_eeprom(count, 0xFF);
   		write_eeprom(count + 1, bin2bcd(count));
   		count = 0;
   	}
		if(cycle_trigger == 1)
		{
		   //cycle = (float)sigHall_timer / 150;
		   pt_byte = &sigHall_timer;
		   write_eeprom(count, *(pt_byte + 3));
		   write_eeprom(count + 1, *(pt_byte + 2));
		   write_eeprom(count + 2, *(pt_byte + 1));
		   write_eeprom(count + 3, *(pt_byte + 0));
		   count += 4;
			rgb_bits.blue =  0x0001;
			rgb_bits.red =   0xC000;
			rgb_bits.green = 0xFFFF;
			for(i = 0; i < 60; i++)
			{
				latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
				latch_ClearAll();
			}
			cycle_trigger = 0;
		}
   }
   
 //test LEDs
 //!	   rgb_bits.blue =  0x8000;
//!		rgb_bits.red =   0x8000;
//!		rgb_bits.green = 0x8000;
//!   	for(int i = 0; i < 16; i++)
//!   	{
//!   		latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
//!   		delay_ms(500);
//!   		shift_right(&rgb_bits.blue, 2, 0);
//!   		shift_right(&rgb_bits.red, 2, 0);
//!   		shift_right(&rgb_bits.green, 2, 0);
//!   	}

//test 60 section
		if(cycle_trigger == 1)
		{
			cycle_trigger = 0;
			section_trigger = 1;
			section_count = 0;
			section_timer = 256 - (int8)(sigHall_timer / (MAX_SECTION * 8)) + tuning;
			while(section_count < MAX_SECTION)
			{
				if(section_trigger == 1)
				{
					set_timer0(section_timer);
					latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
					//delay_us(100);
					latch_ClearAll();
				  	
					section_trigger = 0;
					section_count++;
				}
			}
		}


// RF test
if(mode==2)
		{
			rgb_bits.blue =  0xFFFF;
			rgb_bits.red =   0x0000;
			rgb_bits.green = 0x0000;
		}
	   else if(mode==3)
		{
			rgb_bits.blue =  0x0000;
			rgb_bits.red =   0xFFFF;
			rgb_bits.green = 0x0000;
		}
		else if(mode==4)
		{
			rgb_bits.blue =  0x0000;
			rgb_bits.red =   0x0000;
			rgb_bits.green = 0xFFFF;
		}
		else if(mode==5)
		{
			rgb_bits.blue =  0x00FF;
			rgb_bits.red =   0x0000;
			rgb_bits.green = 0xFF00;
		}
		latch_write(rgb_bits.blue, rgb_bits.red, rgb_bits.green);
		delay_ms(100);
