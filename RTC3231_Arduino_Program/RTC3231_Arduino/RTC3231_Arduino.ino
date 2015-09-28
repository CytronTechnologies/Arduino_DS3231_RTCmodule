#include <DS1307RTC.h>  //Include DS1307 library (which is compatible with DS3231)
#include <Time.h>  //Include Time library 
#include <Wire.h>  //Include Wire library 
#include <LiquidCrystal.h> //Include Liquid Crystal (LCD) library

LiquidCrystal lcd(8,9,4,5,6,7);  //Define digital pins on BBFUINO associated with controlling LCD 
tmElements_t tm;  //Declare tmElements object to store time & date from DS3231


void setup()
{
  lcd.begin(8,2);  //Initialize a 2x8 type LCD
}
void loop()
{
  lcd.setCursor(0,0);  
  if(RTC.read(tm))  //Read the time & date from DS3231, if success, print time & date on LCD
  {
    lcd_to_two_digit_bcd(tm.Day);
    lcd.print('/');
    lcd_to_two_digit_bcd(tm.Month);
    lcd.print('/');
    lcd_to_two_digit_bcd(tmYearToY2k(tm.Year));
    lcd.setCursor(0,1);
    lcd_to_two_digit_bcd(tm.Hour);
    lcd.print(':');
    lcd_to_two_digit_bcd(tm.Minute);
    lcd.print(':');
    lcd_to_two_digit_bcd(tm.Second);
  }
  else  //if not, check the presence of DS3231 chip  
  {
      if (RTC.chipPresent()) //if present, the DS3231 may stop, please upload the Set Time program again to start it.
      {  
        lcd.print("DS3231  ");
        lcd.setCursor(0,1);
        lcd.print("is stop ");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Pls run ");
        lcd.setCursor(0,1);
        lcd.print("Set Time");
      } 
      else  //if not, the communication connections got problem, pls check
      {
        lcd.print("DS3231  ");
        lcd.setCursor(0,1);
        lcd.print("Error   ");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Pls chk ");
        lcd.setCursor(0,1);
        lcd.print("circuit ");
      }
  }
  delay(1000);
}


void lcd_to_two_digit_bcd(unsigned char num)  //use to print each time elements of DS3231 as two digits BCD.
{
  unsigned char byte_temp;
  byte_temp = num/10;
  lcd.print(byte_temp);
  byte_temp = num%10;
  lcd.print(byte_temp);
}
