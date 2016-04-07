/*
  Important NOTES:
    1. If using Arduino IDE, version 1.5.0 or higher is REQUIRED!
*/

/*
  I2cCharDisplayDemo.ino

  Written by: Gary Muhonen  gary@wht.io

  versions
    1.0.0 - 3/19/2016
      Original release.
    1.0.1 - 4/6/2016
      changed the cursorMove() commands to start at 1,1 (instead of 0,0)

  Short Description:
    This demo program works with Arduino and Particle (Photon, Electron, and Core)
    microcontroller boards and it tests features in the I2cCharDisplay library
    (which contains many functions to communicate with OLED and LCD character
    display modules that use the I2C communication protocol).

    The library will work with **LCD** and **OLED** character displays
    (e.g. 16x2, 20x2, 20x4, etc.). The LCD displays must use the the
    HD44780 controller chip and have a I2C PCA8574 i/o expander chip
    on a backpack board (which gives the display I2C capability).
    OLED display modules must have the US2066 controller chip
    (which has I2C built in).

    See the project details links below for installation and usage information.

    Github repositories:
    * Arduino library files:  https://github.com/wht-io/i2c-char-display-arduino.git
    * Particle library files: https://github.com/wht-io/i2c-char-display-particle.git

    Project Details:

    * Library installation and usage: http://wht.io/portfolio/i2c-display-library/
    * OLED hardware information for EastRising modules: http://wht.io/portfolio/i2c-oled-backpack-board-eastrising/
    * OLED hardware information for Newhaven modules: http://wht.io/portfolio/i2c-oled-backpack-board-newhaven/
    * LCD hardware information: http://wht.io/portfolio/i2c-lcd-backpack-board/
*/

/*
  This demo program is public domain. You may use it for any purpose.
  NO WARRANTY IS IMPLIED.
*/


#ifdef ARDUINO_ARCH_AVR         // if using an arduino
#include <I2cCharDisplay.h>
#include <Wire.h>
#elif SPARK                     // if using a core, photon, or electron (by particle.io)
#include "I2cCharDisplay/I2cCharDisplay.h"
#else                           // if using something else
#endif

#define LCDADDRESS     0x27                    // i2c address for the lcd display
#define OLEDADDRESS    0x3c                    // i2c address for the oled display

#define TESTNUM        2                       // number of times to run each test

// In this demo program we are testing both a LCD and OLED display.
// This program will still run correctly even if you only have one of these displays is hooked up.
// Normally you would only use one of these two next lines of code, if you only have one display.

I2cCharDisplay lcd(LCD_TYPE, LCDADDRESS, 2);    // create an lcd object for a 2 line display
I2cCharDisplay oled(OLED_TYPE, OLEDADDRESS, 2); // create an oled object for a 2 line display

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


}
