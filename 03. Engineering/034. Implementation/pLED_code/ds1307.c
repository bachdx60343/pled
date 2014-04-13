//===========================================================================||
//   pLED - FPT University                                                   ||
//   Driver for Real Time Clock - Base on source code from ccsinfo.com       ||
//   Last edited: 20 - March - 2014                                          ||
//                                                                           ||
// ds1307_init() - Enable oscillator without clearing the seconds register   ||
//                 used when PIC loses power and DS1307 run from 3V BAT      ||
//               - Enable squarewave output with 1Hz frequency               ||
//                                                                           ||
// ds1307_set_date_time(day,mth,year,dow,hour,min,sec)  Set the date/time    ||
//                                                                           ||
// ds1307_get_date(day,mth,year,dow)               Get the date              ||
//                                                                           ||
// ds1307_get_time(hr,min,sec)                     Get the time              ||
//                                                                           ||
//===========================================================================||

#define RTC_SDA  PIN_C4 
#define RTC_SCL  PIN_C3 

#use i2c(master, sda=RTC_SDA, scl=RTC_SCL, slow) 

int8 bin2bcd(int8 bin_value); 
int8 bcd2bin(int8 bcd_value); 

void ds1307_init(void) 
{ 
   int8 byte0 = 0; 

   i2c_start();          // send start signal
   i2c_write(0xD0);      // indentification of I2C slave device with write operation
   i2c_write(0x00);      // address of register 0
   i2c_start();
   i2c_write(0xD1);      // change operation to read
   byte0 = i2c_read(0);  // read current first byte in DS1307, which stores seconds value and CH bit (Clock Halt)
   i2c_stop();           // send stop signal
   bit_clear(byte0, 7);  // clear bit 7 to enable oscillator, needed for clock to run

   delay_us(3);          // make sure another transmit is possible, base on datasheet

   i2c_start(); 
   i2c_write(0xD0);      // write to ds1307
   i2c_write(0x00);      // register 0
   i2c_write(byte0);     // write to register 0 with the same seconds and bit 7 cleared
   i2c_stop();
   
   delay_us(3);
   
   i2c_start();
   i2c_write(0xD0);
   i2c_write(0x07);      // Control Register 
   i2c_write(0x10);      // enable squarewave output pin with frequency 1Hz
   i2c_stop(); 

} 

void ds1307_set_date_time(int8 day, int8 mth, int8 year, int8 dow, int8 hr, int8 min, int8 sec) 
{ 
  sec &= 0x7F;           // clear CH bit
  hr  &= 0x3F;           // set 24h time mode

  i2c_start(); 
  i2c_write(0xD0);            // I2C write address 
  i2c_write(0x00);            // Start at REG 0
  i2c_write(bin2bcd(sec));    // REG 0 - seconds
  i2c_write(bin2bcd(min));    // REG 1 - minutes
  i2c_write(bin2bcd(hr));     // REG 2 - hours
  i2c_write(bin2bcd(dow));    // REG 3 - date of week
  i2c_write(bin2bcd(day));    // REG 4 - day of month
  i2c_write(bin2bcd(mth));    // REG 5 - month
  i2c_write(bin2bcd(year));   // REG 6 - year
  //i2c_write(0x80);            // REG 7 - Disable squarewave output pin 
  i2c_stop(); 
} 

void ds1307_get_date(int8 &day, int8 &mth, int8 &year, int8 &dow) 
{ 
  i2c_start(); 
  i2c_write(0xD0); 
  i2c_write(0x03);            // Start at REG 3
  i2c_start(); 
  i2c_write(0xD1);            // change to read
  dow  = bcd2bin(i2c_read(1) & 0x07);   // REG 3 - date of week 
  day  = bcd2bin(i2c_read(1) & 0x3f);   // REG 4 - day of month
  mth  = bcd2bin(i2c_read(1) & 0x1f);   // REG 5 - month
  year = bcd2bin(i2c_read(0));          // REG 6 - year
  i2c_stop(); 
} 

void ds1307_get_time(int8 &hr, int8 &min, int8 &sec) 
{ 
  i2c_start(); 
  i2c_write(0xD0); 
  i2c_write(0x00);                    // Start at REG 0
  i2c_start(); 
  i2c_write(0xD1);                    // read mode
  sec = bcd2bin(i2c_read(1) & 0x7f);  // REG 0 - seconds, exclude CH bit
  min = bcd2bin(i2c_read(1) & 0x7f);  // REG 1 - minutes
  hr  = bcd2bin(i2c_read(0) & 0x3f);  // REG 2 - hours, 24h mode
  i2c_stop(); 

} 

//convert binary to BCD value using double dabble algorithm
int8 bin2bcd(int8 bin_value) 
{ 
  int32 dabble;
  int8 hyaku, juu, ichi;
  int8 i;

  dabble = bin_value & 0x000000FF;
  for(i = 0; i < 8; i++)
  {
    hyaku = (int8)(dabble >> 16) & 0x0F;
    juu   = (int8)(dabble >> 12) & 0x0F;
    ichi  = (int8)(dabble >> 8)  & 0x0F;
    if(hyaku >= 5) hyaku += 3;
    if(juu   >= 5) juu   += 3;
    if(ichi  >= 5) ichi  += 3;
    dabble = ((int32)hyaku << 16) | ((int32)juu << 12) | ((int32)ichi << 8) | (dabble & 0x000000FF);
    dabble <<= 1;
  }
  juu   = (int8)(dabble >> 12) & 0x0F;
  ichi  = (int8)(dabble >> 8)  & 0x0F;
  return((juu << 4) | (ichi & 0x0F)); 
} 


// BCD range 00 - 99
int8 bcd2bin(int8 bcd_value) 
{ 
  int8 temp;
  temp = bcd_value;
  temp &= 0xF0; //get high nibble which store tens value
  return((temp >> 1) + (temp >> 3) + (bcd_value & 0x0F)); //(tens * 8) + (tens * 2) + ones
} 
