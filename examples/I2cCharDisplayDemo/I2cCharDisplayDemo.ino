/*
  Important NOTES:
    1. If using Arduino IDE, version 1.5.0 or higher is REQUIRED!
*/

/*
  I2cCharDisplayDemo.ino

  Written by: Gary Muhonen  gary@dcity.org

  Versions
    1.0.0 - 3/19/2016
      Original release.
    1.0.1 - 4/6/2016
      Modified the cursorMove() function to start at (1,1) instead of (0,0).
      Modified the cursorMove() function to work with OLED modules correctly.
      Modified the home() function to work with the newly modified cursorMove().
      Modified the oledBegin() function to work with the Newhaven OLED modules.
    1.0.2 - 4/17/2017
      Added a second class constructor (with additional parameter i2cPort),
        so that the user could specify which i2c port to use (0 or 1)
        Port 0 is the main i2c port using pins (SDA and SCL).
        Port 1 is the aux i2c port using pins (SDA1 and SCL1, e.g. on an Arduino DUE board).
        This adds support for the Arduino DUE board (using either of it's i2c ports).
    1.0.3 - 8/27/2018 Transfer to GM, and some minor changes
        Added these OLED "fade display" functions (not very useful for some types of OLED displays)
          void fadeOff();           // turns off the fade feature of the OLED
          void fadeOnce(uint8_t);   // fade out the display to off (fade time 0-16) - (on some display types, it doesn't work very well. It takes the display to half brightness and then turns off display)
          void fadeBlink(uint8_t);  // blinks the fade feature of the OLED (fade time 0-16) - (on some display types, it doesn't work very well. It takes the display to half brightness and then turns off display)

  Short Description:

      These files provide a software library and demo program for the Arduino
      and Particle microcontroller boards.

      The library files provide useful functions to make it easy
      to communicate with OLED and LCD character
      display modules that use the I2C communication protocol. The demo
      program shows the usage of the functions in the library.

      The library will work with **LCD** and **OLED** character displays
      (e.g. 16x2, 20x2, 20x4, etc.). The LCD displays must use the the
      HD44780 controller chip and have a I2C PCA8574 i/o expander chip
      on a backpack board (which gives the display I2C capability).
      OLED display modules must have the US2066 controller chip
      (which has I2C built in). Backback boards are available and
      details are in the link below.


  https://www.dcity.org/portfolio/i2c-display-library/
  This link has details including:
      * software library installation for use with Arduino, Particle and Raspberry Pi boards
      * list of functions available in these libraries
      * a demo program (which shows the usage of most library functions)
      * info on OLED and LCD character displays that work with this software
      * hardware design for a backpack board for LCDs and OLEDs, available on github
      * info on backpack “bare” pc boards available from OSH Park.


  This demo program is public domain. You may use it for any purpose.
    NO WARRANTY IS IMPLIED.

  License Information:  https://www.dcity.org/license-information/
*/


// include files... some boards require different include files
#ifdef ARDUINO_ARCH_AVR         // if using an arduino
#include "I2cCharDisplay.h"
#include "Wire.h"
#elif ARDUINO_ARCH_SAM        // if using an arduino DUE
#include "I2cCharDisplay.h"
#include "Wire.h"
#elif PARTICLE                     // if using a core, photon, or electron (by particle.io)
#include "I2cCharDisplay/I2cCharDisplay.h"  // use this if the library files are in the particle repository of libraries
//#include "I2cCharDisplay.h"     // use this if the library files are in the same folder as this demo program
#elif defined(__MK20DX128__) || (__MK20DX256__) || (__MK20DX256__) || (__MK62FX512__) || (__MK66FX1M0__) // if using a teensy 3.0, 3.1, 3.2, 3.5, 3.6
#include "I2cCharDisplay.h"
#include "Wire.h"
#else                           // if using something else then this may work
#include "I2cCharDisplay.h"
#include "Wire.h"
#endif


#define LCDADDRESS     0x27                    // i2c address for the lcd display
#define OLEDADDRESS    0x3c                    // i2c address for the oled display

#define TESTNUM        2                       // number of times to run each test

// In this demo program we are testing both a LCD and OLED display.
// This program will still run correctly even if you only have one of these displays is hooked up.
// Normally you would only use one of these two next lines of code, if you only have one display.

I2cCharDisplay lcd(LCD_TYPE, LCDADDRESS, 2);    // create an lcd object for a 2 line display
I2cCharDisplay oled(OLED_TYPE, OLEDADDRESS, 2); // create an oled object for a 2 line display
// If you are using a microcontroller with two I2C ports (like the Arduino DUE), you can specify the I2C port to use (0 or 1)
//     with this constructor. The 4th parameter is the I2C port to use (o or 1).
//     I2cCharDisplay oled(OLED_TYPE, OLEDADDRESS, 2, 1); // create an oled object for a 2 line display, using the 2nd I2C port (specified as 1 in this example)

void setup()
{
  Wire.begin();                     // initialize i2c
  lcd.begin();                      // initialize the lcd
  oled.begin();                     // initialize the oled
}


// change the constant TESTNUM above to control how many times each test is run.

void loop()
{

  // test the lcd backlight on/off and the oled brightness commands
  lcd.clear();
  oled.clear();
  lcd.print("Backlight On/Off");
  oled.print("Set Brightness");
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    delay(1000);
    lcd.backlightOff();
    oled.setBrightness(0);
    delay(1000);
    lcd.backlightOn();
    oled.setBrightness(255);
  }


  // test the clear command
  lcd.clear();
  oled.clear();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.print("Clear Display");
    oled.print("Clear Display");
    delay(1000);
    lcd.clear();
    oled.clear();
    delay(1000);
  }

  // test the cursor home command
  lcd.clear();
  oled.clear();
  lcd.cursorOn();
  oled.cursorOn();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.clear();
    oled.clear();
    lcd.print("Cursor Home");
    oled.print("Cursor Home");
    delay(1000);
    lcd.home();
    oled.home();
    delay(1000);
    lcd.print("123456789012345");
    oled.print("123456789012345");
    delay(1000);
  }
  lcd.cursorOff();
  oled.cursorOff();



  // test the cursor move command
  lcd.clear();
  oled.clear();
  lcd.cursorOn();
  oled.cursorOn();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.clear();
    oled.clear();
    lcd.print("Cursor Move");
    oled.print("Cursor Move");
    delay(1000);
    lcd.cursorMove(2, 1);
    oled.cursorMove(2, 1);
    lcd.print("12345");
    oled.print("12345");
    delay(1000);
    lcd.cursorMove(2, 9);
    oled.cursorMove(2, 9);
    delay(1000);
    lcd.print("12345");
    oled.print("12345");
    delay(1000);
  }
  lcd.cursorOff();
  oled.cursorOff();


  // test the display on/off commands
  lcd.clear();
  oled.clear();
  lcd.print("Display On/Off");
  oled.print("Display On/Off");
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.displayOn();
    oled.displayOn();
    delay(1000);
    lcd.displayOff();
    oled.displayOff();
    delay(1000);
  }
  lcd.displayOn();
  oled.displayOn();



  // test the cursor blink on/off commands
  lcd.clear();
  oled.clear();
  lcd.print("Cursor Block");
  oled.print("Cursor Block");
  lcd.cursorBlinkOn();
  oled.cursorBlinkOn();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.cursorMove(2, 7);
    oled.cursorMove(2, 7);
    delay(1000);
    lcd.print("12345");
    oled.print("12345");
    delay(1000);
    lcd.cursorMove(2, 7);
    oled.cursorMove(2, 7);
    delay(1000);
    lcd.print("67890");
    oled.print("67890");
    delay(1000);
  }
  lcd.cursorBlinkOff();
  oled.cursorBlinkOff();


  // test the cursor  on/off commands
  lcd.clear();
  oled.clear();
  lcd.print("Cursor On/Off");
  oled.print("Cursor On/Off");
  lcd.cursorMove(2, 7);
  oled.cursorMove(2, 7);
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.cursorOn();
    oled.cursorOn();
    delay(1000);
    lcd.cursorOff();
    oled.cursorOff();
    delay(1000);
  }


  // test the display shift left and right commands (cursor shifts too)
  lcd.clear();
  oled.clear();
  lcd.print("Disp Shift R/L");
  oled.print("Disp Shift R/L");
  delay(2000);
  lcd.cursorOn();
  oled.cursorOn();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.displayShiftLeft();
    oled.displayShiftLeft();
    delay(1000);
    lcd.displayShiftLeft();
    oled.displayShiftLeft();
    delay(1000);
    lcd.displayShiftLeft();
    oled.displayShiftLeft();
    delay(1000);
    lcd.displayShiftRight();
    oled.displayShiftRight();
    delay(1000);
    lcd.displayShiftRight();
    oled.displayShiftRight();
    delay(1000);
    lcd.displayShiftRight();
    oled.displayShiftRight();
    delay(1000);
  }
  lcd.cursorOff();
  oled.cursorOff();



  // test the cursor shift left/right commands
  lcd.clear();
  oled.clear();
  lcd.print("Cursor Shift L/R");
  oled.print("Cursor Shift L/R");
  lcd.cursorOn();
  oled.cursorOn();
  lcd.cursorMove(2, 7);
  oled.cursorMove(2, 7);
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.cursorShiftLeft();
    oled.cursorShiftLeft();
    delay(500);
    lcd.cursorShiftLeft();
    oled.cursorShiftLeft();
    delay(500);
    lcd.cursorShiftLeft();
    oled.cursorShiftLeft();
    delay(500);
    lcd.cursorShiftRight();
    oled.cursorShiftRight();
    delay(500);
    lcd.cursorShiftRight();
    oled.cursorShiftRight();
    delay(500);
    lcd.cursorShiftRight();
    oled.cursorShiftRight();
    delay(500);
  }
  lcd.cursorOff();
  oled.cursorOff();



  // test the displayLeftToRight and displayRightToLeft commands
  lcd.clear();
  oled.clear();
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.displayLeftToRight();
    oled.displayLeftToRight();
    lcd.clear();
    oled.clear();
    lcd.print("Display L -> R");
    oled.print("Display  L -> R");
    lcd.cursorMove(2, 7);
    oled.cursorMove(2, 7);
    lcd.print("12345");
    oled.print("12345");
    delay(2000);
    lcd.clear();
    oled.clear();
    lcd.print("Display R -> L");
    oled.print("Display  R -> L");
    lcd.displayRightToLeft();
    oled.displayRightToLeft();
    lcd.cursorMove(2, 7);
    oled.cursorMove(2, 7);
    lcd.print("12345");
    oled.print("12345");
    delay(2000);
  }
  lcd.displayLeftToRight();
  oled.displayLeftToRight();


  // test the displayShiftOn and displayShiftOff commands
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.clear();
    oled.clear();
    lcd.print("Display Shift On");
    oled.print("Display Shift On");
    delay(2000);
    lcd.displayShiftOn();
    oled.displayShiftOn();
    lcd.cursorMove(2, 9);
    oled.cursorMove(2, 9);
    for (uint8_t i = 0; i < 8; ++i)
    {
      lcd.print(i);
      oled.print(i);
      delay(500);
    }
    delay(2000);
    lcd.displayShiftOff();
    oled.displayShiftOff();
    lcd.clear();
    oled.clear();
    lcd.print("Disp Shift Off");
    oled.print("Disp Shift Off");
    delay(2000);
    lcd.cursorMove(2, 9);
    oled.cursorMove(2, 9);
    for (uint8_t i = 0; i < 8; ++i)
    {
      lcd.print(i);
      oled.print(i);
      delay(500);
    }
    delay(2000);
  }



  // test the lcd backlight on/off and the oled brightness commands
  lcd.clear();
  oled.clear();
  lcd.print("Backlight on/off");
  oled.print("Brightness test");
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    delay(1000);
    lcd.backlightOff();
    oled.setBrightness(0);
    delay(1000);
    lcd.backlightOn();
    oled.setBrightness(255);
  }


  // test creating and displaying custom characters
  // thanks to dfrobot.com for these custom characters
  uint8_t bell[8]     = { 0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4 };
  uint8_t note[8]     = { 0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0 };
  uint8_t clock1[8]   = { 0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0 };
  uint8_t heart[8]    = { 0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0 };
  uint8_t duck[8]     = { 0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0 };
  uint8_t check[8]    = { 0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0 };
  uint8_t cross[8]    = { 0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0 };
  uint8_t retarrow[8] = { 0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4 };
  lcd.createCharacter(0, bell);
  lcd.createCharacter(1, note);
  lcd.createCharacter(2, clock1);
  lcd.createCharacter(3, heart);
  lcd.createCharacter(4, duck);
  lcd.createCharacter(5, check);
  lcd.createCharacter(6, cross);
  lcd.createCharacter(7, retarrow);
  oled.createCharacter(0, bell);
  oled.createCharacter(1, note);
  oled.createCharacter(2, clock1);
  oled.createCharacter(3, heart);
  oled.createCharacter(4, duck);
  oled.createCharacter(5, check);
  oled.createCharacter(6, cross);
  oled.createCharacter(7, retarrow);
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.clear();
    oled.clear();
    delay(200);
    lcd.print("Custom Chars");
    oled.print("Custom Chars");
    lcd.cursorMove(2, 3);
    oled.cursorMove(2, 3);
    lcd.write(0);
    oled.write(0);
    delay(200);
    lcd.write(1);
    oled.write(1);
    delay(200);
    lcd.write(2);
    oled.write(2);
    delay(200);
    lcd.write(3);
    oled.write(3);
    delay(200);
    lcd.write(4);
    oled.write(4);
    delay(200);
    lcd.write(5);
    oled.write(5);
    delay(200);
    lcd.write(6);
    oled.write(6);
    delay(200);
    lcd.write(7);
    oled.write(7);
    delay(2000);
  }



  // test printing some numbers
  float    x = 1.234567;
  uint16_t j = 11;
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
  lcd.clear();
  oled.clear();
  lcd.print("Printing Numbers");
  oled.print("Printing Numbers");
  lcd.cursorMove(2, 1);               // move to 2nd line
  oled.cursorMove(2, 1);
  lcd.print("x=");
  lcd.print(x, 2);                    // print 1 decimal places
  oled.print("x=");
  oled.print(x, 2);
  lcd.cursorMove(2, 9);
  oled.cursorMove(2, 9);
  lcd.print("j=");
  lcd.print(j, HEX);                  // print in hex
  oled.print("j=");
  oled.print(j, HEX);
    lcd.print(" hex");
    oled.print(" hex");
  delay(2000);
  lcd.clear();
  oled.clear();
  lcd.print("Printing Numbers");
  oled.print("Printing Numbers");
  lcd.cursorMove(2, 1);               // move to 2nd line
  oled.cursorMove(2, 1);
  lcd.print("x=");
  lcd.print(x, 1);                    // print 1 decimal places
  oled.print("x=");
  oled.print(x, 1);
  lcd.cursorMove(2, 9);
  oled.cursorMove(2, 9);
  lcd.print("j=");
  lcd.print(j, DEC);                  // print in hex
  oled.print("j=");
  oled.print(j, DEC);
  delay(2000);
  }

  // test the oled fade mode = blink (display will fade down in brightness, blink, and come up in brightness... then repeat)
  //      In my opinion this feature is not that useful, but I provided it because the OLED is capable of it.
  // test the lcd backlight on/off
  // Note: Fade mode is not very useful for some displays, as some displays will fade in brightness to about 50% and then turn off.
  for (uint8_t i = 0; i < TESTNUM; ++i)
  //delay(2000);
  {
    lcd.clear();
    oled.clear();
    lcd.backlightOn();
    lcd.print("Backlight On");
    oled.fadeOff();
    oled.print("Fade Mode = Off");
    delay(2000);
    lcd.clear();
    oled.clear();
    lcd.print("Backlight Off");
    lcd.backlightOff();
    oled.print("Fade Mode = Blink");
    oled.fadeBlink(0);   // fade the oled with a delay of 0 (valid values are 0-15). You must use fadeOff() to turn off blink mode.
    delay(10000);
  }
  lcd.print("Backlight On");
  oled.fadeOff();



  // test the oled fade mode = once (display will fade down in brightness, and then turn off)
  //      In my opinion this feature is not that useful, but I provided it because the OLED is capable of it.
  // test the lcd backlight on/off
  // Note: Fade mode is not very useful for some displays, as some displays will fade in brightness to about 50% and then turn off.
  for (uint8_t i = 0; i < TESTNUM; ++i)
  {
    lcd.clear();
    oled.clear();
    lcd.backlightOn();
    lcd.print("Backlight On");
    oled.fadeOff();
    oled.print("Fade Mode = Off");
    delay(2000);
    lcd.clear();
    oled.clear();
    lcd.print("Backlight Off");
    lcd.backlightOff();
    oled.print("Fade Mode = Once");
    oled.fadeOnce(4);  // fade out the oled once with a delay of 4 (valid values are 0-15). You must use fadeOff() to turn display on again.
    delay(8000);
  }
  lcd.print("Backlight On");
  oled.fadeOff();


}
