/*
  Important NOTES:
    1. If using Arduino IDE, version 1.5.0 or higher is REQUIRED!
*/

/*
  I2cCharDisplay.h

  Written by: Gary Muhonen  gary@wht.io

  versions
    1.0.0 - 3/19/2016
      Original Release.
    1.0.1 - 4/6/2016
      Modified the cursorMove() description.

    Short Description:
      This library works with Arduino and Particle (Photon, Electron, and Core)
      microcontroller boards and it provides many functions to communicate with
      OLED and LCD character display modules that use the I2C communication
      protocol.

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
  Windy Hill Technology LLC code, firmware, and software is released under the
  MIT License (http://opensource.org/licenses/MIT).

  The MIT License (MIT)

  Copyright (c) 2016 Windy Hill Technology LLC

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/


#ifdef ARDUINO_ARCH_AVR        // if using an arduino and IDE is version 1.0 or higher
#include "Arduino.h"
#include <Wire.h>
#elif SPARK                    // if using a core, photon, or electron (by particle.io)
#include "application.h"
#else                          // if using something else
#endif


// _displayType options
#define LCD_TYPE                     0 // if the display is an LCD using the PCA8574 outputting to the HD44780 lcd controller chip
#define OLED_TYPE                    1 // if the display is a OLED using the US2066 oled controller chip

// oled specific constants
#define OLED_COMMANDMODE             0x80
#define OLED_DATAMODE                0x40
#define OLED_SETBRIGHTNESSCOMMAND    0X81

// lcd specific constants

// bits on the PCA8574 chip for controlling the lcd
#define LCD_BACKLIGHTON     8 // backlight on bit
#define LCD_BACKLIGHTOFF    0 // backlight off
#define LCD_ENABLEON        4 // Enable bit on
#define LCD_ENABLEOFF       0 // Enable bit off
#define LCD_READ            2 // Read bit
#define LCD_WRITE           0 // Write bit
#define LCD_DATA            1 // Register Select bit for Data
#define LCD_COMMAND         0 // Register Select bit for Command

// lcd and oled constants

// lcd commands
#define LCD_CLEARDISPLAYCOMMAND      0x01
#define LCD_RETURNHOMECOMMAND        0x02
#define LCD_ENTRYMODECOMMAND         0x04
#define LCD_DISPLAYCONTROLCOMMAND    0x08
#define LCD_SHIFTCOMMAND             0x10
#define LCD_FUNCTIONSETCOMMAND       0x20
#define LCD_SETCGRAMADDRCOMMAND      0x40
#define LCD_SETDDRAMADDRCOMMAND      0x80

// bits for _lcdEntryModeCommand
#define LCD_DISPLAYLEFTTORIGHT       0x02
#define LCD_DISPLAYRIGHTTOLEFT       0X00
#define LCD_DISPLAYSHIFTON           0x01
#define LCD_DISPLAYSHIFTOFF          0x00

// bits for _lcdDisplayControlCommand
#define LCD_DISPLAYON                0x04
#define LCD_DISPLAYOFF               0x00
#define LCD_CURSORON                 0x02
#define LCD_CURSOROFF                0x00
#define LCD_CURSORBLINKON            0x01
#define LCD_CURSORBLINKOFF           0x00

// bits for _lcdFunctionSetCommand
#define LCD_8BITMODE                 0x10
#define LCD_4BITMODE                 0x00
#define LCD_2LINES                   0x08
#define LCD_1LINES                   0x00
#define LCD_5x10DOTS                 0x04
#define LCD_5x8DOTS                  0x00

// bits for shifting the display and the cursor
#define LCD_DISPLAYSHIFT             0x08
#define LCD_CURSORSHIFT              0x00
#define LCD_SHIFTRIGHT               0x04
#define LCD_SHIFTLEFT                0x00


class I2cCharDisplay : public Print {       // parent class is Print, so that we can use the print functions
public:

  I2cCharDisplay(uint8_t displayType, uint8_t i2cAddress, uint8_t rows); // creates a display object
  void begin();                                                      // required to inialize the display. run this first!
  void clear();                                                      // clear the display and home the cursor to 1,1
  void home();                                                       // move the cursor to home position (1,1)
  void cursorMove(uint8_t row, uint8_t col);                         // move cursor to position row,col (positions start at 1)
  void displayOff();                                                 // turns off the entire display
  void displayOn();                                                  // turns on the entire display
  void cursorBlinkOff();                                             // turns off the blinking block cursor
  void cursorBlinkOn();                                              // turns on the blinking block cursor
  void cursorOff();                                                  // turns off the underline cursor
  void cursorOn();                                                   // turns on an underline cursor
  void displayShiftLeft();                                           // shifts all rows of the display one character to the left (shifts cursor too)
  void displayShiftRight();                                          // shifts all rows of the display one character to the right (shifts cursor too)
  void cursorShiftLeft(void);                                        // shifts the cursor one character to the left
  void cursorShiftRight(void);                                       // shifts the cursor one character to the right
  void displayLeftToRight();                                         // characters are displayed left to right (DEFAULT MODE)
  void displayRightToLeft();                                         // characters are displayed left to right
  void displayShiftOn();                                             // cursor is held constant and previous characters are shifted when new ones come in
  void displayShiftOff();                                            // cursor moves after each character is received by the display (DEFAULT MODE)
  void createCharacter(uint8_t, uint8_t[]);                          // used to create custom dot matrix characters (8 are available)
  virtual size_t write(uint8_t);                                     // allows the print command to work (in Arduino or Particle)

// functions specific to lcd displays

  void backlightOn();
  void backlightOff();

// functions specific to oled displays

  void setBrightness(uint8_t);



/*
 * #if defined(ARDUINO) && ARDUINO >= 100
 * virtual size_t write(uint8_t);
 * #else
 * virtual void write(uint8_t);
 * #endif
 */


private:
  void lcdBegin();               // used to initialize the lcd display
  void oledBegin();              // used to initialize the oled display
  void sendCommand(uint8_t);     // send a command to the display
  void sendData(uint8_t);        // send data to the display
  void sendLcdCommand(uint8_t);  // send a command to the lcd display
  void sendLcdData(uint8_t);     // send data to the lcd display
  void sendOledCommand(uint8_t); // send a command to the oled display
  void sendOledData(uint8_t);    // send data to the oled display

  // private variables
  // keep track of current state of these lcd commands
  uint8_t _displayType;           // keep track of the type of display we are using (e.g. lcd, oled, etc.)

  uint8_t _lcdEntryModeCommand;
  uint8_t _lcdDisplayControlCommand;
  uint8_t _lcdFunctionSetCommand;

  uint8_t _i2cAddress;
  uint8_t _rows;                   // number of rows in the display (starting at 1)
  uint8_t _lcdBacklightControl;    // 0 if backlight is off, 0x08 is on
};
