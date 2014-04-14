//===========================================================================||
//   pLED - Capstone Project                                                 ||
//   FPT University - Spring 2014                                            ||
//                                                                           ||
// 		Function for fetching the data to rgb_bits structure                ||
//                                                                           ||
//   Last edited: 13 - April - 2014                                          ||
//                                                                           ||
//   void fetch_data() - depend on chosen mode, the board position and timing||
//                       fetch appropriate data to rgb_bits structure        ||
//																									  ||
//   There are four modes:                                                   ||
//					- MODE_A: data for analog clock                               ||
//					- MODE_B: data for digital clock                              ||
//					- MODE_C: data for an image, FPT logo                         ||
//					- MODE_D: data for running letters, pLED                      ||
//																									  ||
//===========================================================================||

void fetch_data()
{
	if(mode == MODE_A) // display analog clock
	{
		// the section_count vary from 1-60 and need to adjust to 0-59 value of minute and second
		int8 pos = section_count;
		if (section_count == 60)	pos = 0;
		// set default value for normal section
		rgb_bits.blue =  0x0001;
		rgb_bits.red =   0x0001;
		rgb_bits.green = 0x0001;
		// leds' value for hour mark on analog clock
		if((section_count % 5) == 0)
		{
			rgb_bits.blue =  0x0003;
			rgb_bits.red =   0x0003;
			rgb_bits.green = 0x0003;
		}
		// leds' value at 3-6-9-12 hour
		if((section_count % 15) == 0)
		{
			rgb_bits.blue =  0x007;
			rgb_bits.red =   0x007;
		}
		// hour hand's position
		if(pos == anal_hour)
		{
			rgb_bits.blue = 0xFC00;
		}
		// minute hand's position
		if(pos == min)
		{
			rgb_bits.red = 0xFF00;
		}
		//second hand's position
		if(pos == sec)
		{
			rgb_bits.green = 0xFFF1;
		}
	}
	else if(mode == MODE_C) // display an image - FPT logo
	{
		//the image data, which store information for entire circle, is an array
		rgb_bits.blue = fpt[section_count * 3 - 3];
		rgb_bits.red = fpt[section_count * 3 - 2];
		rgb_bits.green = fpt[section_count * 3 - 1];
	}
	else if(mode == MODE_B) // display digital clock with format hour-minute, day-month
	{
		rgb_bits.red = 0x8000;
		switch (section_count)
		{
			//section 52-54: display the ten of hour
			case 52:
				rgb_bits.green = number_upper[hour_h][0];
				break;
			case 53:
				rgb_bits.green = number_upper[hour_h][1];
				break;
			case 54:
				rgb_bits.green = number_upper[hour_h][2];
				break;
			//section 56-58: display the unit of hour
			case 56:
				rgb_bits.green = number_upper[hour_l][0];
				break;
			case 57:
				rgb_bits.green = number_upper[hour_l][1];
				break;
			case 58:
				rgb_bits.green = number_upper[hour_l][2];
				break;
			//section 2-4: display the ten of minute
			case 2:
				rgb_bits.green = number_upper[min_h][0];
				break;
			case 3:
				rgb_bits.green = number_upper[min_h][1];
				break;
			case 4:
				rgb_bits.green = number_upper[min_h][2];
				break;
			//section 6-8: display the unit of minute
			case 6:
				rgb_bits.green = number_upper[min_l][0];
				break;
			case 7:
				rgb_bits.green = number_upper[min_l][1];
				break;
			case 8:
				rgb_bits.green = number_upper[min_l][2];
				break;
			////section 60: display the second mark, 0.5s on and 0.5s off
			case 60:
				if(digit_sec < 15)
					rgb_bits.green = 0x00A0;
				else
					rgb_bits.green = 0x0000;
				if(digit_sec == 31)
					digit_sec = 0;
				break;
			//section 37-39: display the ten of day
			case 39:
				rgb_bits.blue = number_lower[day_h][2];
				break;
			case 38:
				rgb_bits.blue = number_lower[day_h][1];
				break;
			case 37:
				rgb_bits.blue = number_lower[day_h][0];
				break;
			//section 33-35: display the unit of day
			case 35:
				rgb_bits.blue = number_lower[day_l][2];
				break;
			case 34:
				rgb_bits.blue = number_lower[day_l][1];
				break;
			case 33:
				rgb_bits.blue = number_lower[day_l][0];
				break;
			//section 25-27: display the ten of month
			case 27:
				rgb_bits.blue = number_lower[month_h][2];
				break;
			case 26:
				rgb_bits.blue = number_lower[month_h][1];
				break;
			case 25:
				rgb_bits.blue = number_lower[month_h][0];
				break;
			//section 21-23: display the unit of month
			case 23:
				rgb_bits.blue = number_lower[month_l][2];
				break;
			case 22:
				rgb_bits.blue = number_lower[month_l][1];
				break;
			case 21:
				rgb_bits.blue = number_lower[month_l][0];
				break;
			////section 29-31: display the hyphen
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
	else if (mode == MODE_D) // display running letters
	{ 	
		rgb_bits.blue = 0x0000;
		rgb_bits.red = 0x0000;
		rgb_bits.green = 0x0000;
	  	
		int pcount;
		pcount = section_count - pled_position + 14;
		if (pled_position < 15)
			if (pcount >= 60)
			{
				pcount = pcount - 60;
			}
		if (pcount >=0 && pcount < 15)
		{
			if(pcount > 11) rgb_bits.blue = pled_inward[pcount];
			else if(pcount > 7) rgb_bits.red = pled_inward[pcount];
			else if(pcount > 3) rgb_bits.green = pled_inward[pcount];
			else
			{
				rgb_bits.red = pled_inward[pcount];
				rgb_bits.green = pled_inward[pcount];
			}
		}
	  	
		pled_count++;
		if (pled_count > 120)
		{
			pled_count = 0;
			pled_position = pled_position + pled_direction;
		}
		if (pled_position == 0) pled_position = 60;
		else if (pled_position == 61) pled_position = 1;
	}
}
