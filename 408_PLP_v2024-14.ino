/* 40et8 Voiture 410 Parade Train Player Version 2.2
   Donated to Voiture 410 by Linda & Paul Ciarelli
   Chiseled and Built by Paul Ciarelli   
   © 2003 This is a Three Pauls Production

Special Thanks to:
  Jim Holter for donating wiring / electrical parts.
  Tim Green & the "Green Machine" for helping with design and installation

See Documentation Tab for more information

Functions:  
  Print to LCD: 
  void blurt2Display(int8_t x, char *displayLine1, char *displayLine2, int delayTime) {}
    LCD Line 0 - 4
    Lines 1 - 4 as strings
    set a delay if needed
  Play a sound file:  
    void playSelection(int selNumber, int selDuration) {  
    Selection # and length in seconds -- delay required to stop some chop.
*/

// Preamble
// Section: Included library 
#include <Arduino.h>
#include "DYPlayerArduino.h"      // DY-SV5W
#include "HD44780_LCD_PCF8574.h"  // Thanks Gavin Lyons!  This was the one.
#include "I2CKeyPad.h"            // 4x4 Telephone Keypad

// Section: Globals / Initialization
// Init MP3 Player
  DY::Player player;  // Initialise the player, it defaults to using Serial.

// Init Display
  HD44780LCD myLCD( 4, 20, 0x27, &Wire); // instantiate an object
//                     12345678901234567890  
  char lcdLine1[21] = "40&8 V410 P. Player "; // Lines 1 and 2 will normally be static,
  char lcdLine2[21] = "Press Reset to Stop "; 
  char lcdLine3[21]; // Lines 3 and 4 will show current variables such as song selected.
  char lcdLine4[21]; 
  uint32_t selDelay = 300;
  uint32_t normDelay = 4000;

// Init keypad
  const uint8_t KEYPAD_ADDRESS = 0x20;
  I2CKeyPad keyPad(KEYPAD_ADDRESS);
  uint32_t start, stop;
  uint32_t lastKeyPressed = 0;
  char iChar = " ";
// Section: Function Prototypes

// Section: Setup
// ====== ========= ========= ========= ========= ========= ========= =========|
void setup() {

  // Setup DY Player Setup
  player.begin();
  player.setVolume(30);        // 30 = 100% Volume
  player.setEq(DY::Eq::Rock);  // Rock is best-sounding for small speakers
  player.setCycleMode(DY::PlayMode::OneOff);

  // Play Silence
  player.playSpecifiedDevicePath(DY::Device::Sd, "/17.MP3");

  // Setup Display
  myLCD.PCF8574_LCDInit(myLCD.LCDCursorTypeOn);
  myLCD.PCF8574_LCDClearScreen();
  myLCD.PCF8574_LCDBackLightSet(true);
  //                12345678901234567890  
  strcpy(lcdLine1, "40&8 Voiture 410    ");
  strcpy(lcdLine2, "Parade Player v2.14 ");
  strcpy(lcdLine3, "(C) 2023 Three Paul ");
  strcpy(lcdLine4, "Productions         ");
  blurt2Display(lcdLine1, lcdLine2, lcdLine3, lcdLine4, normDelay);
  
  // Setup Keypad
  if (keyPad.begin() == false) {  //  In essence just run keyPad.begin()
    strcpy(lcdLine1, "Error               ");
    strcpy(lcdLine2, "No Comm w/Keyboard  ");
    strcpy(lcdLine3, "                    ");
    strcpy(lcdLine4, "                    ");
    blurt2Display(lcdLine1, lcdLine2, lcdLine3, lcdLine4, normDelay);
    while (1)
      ;
  }
  // Let's Go...   // Loop Instructions
    //              12345678901234567890  
  strcpy(lcdLine3, "Letter: Loco Sfx    ");
  strcpy(lcdLine4, "Number: Song        ");
  blurt2Display(lcdLine1, lcdLine2, lcdLine3, lcdLine4, selDelay);

}  // setup

// ====== ========= ========= ========= ========= ========= ========= =========|
void loop() {

  uint32_t now = millis();
  // Select Keyboard Type --  N = NO_KEY, F = FAILED Note NO_KEY is MIA ? !
      char plpKey[19] = "147*2580369#ABCDNF";  // 16 Key Black Telephone Kepad
    //char plpKey[19] = "123A456B789C*0#DNF";  // 16 Key Membrane Keypad Red/Blue
  
  // set lcd lines one and two back to sandard and keep 3 & 4 from Growing past 20 Char!
  strcpy(lcdLine1, "40&8 Voiture 410    ");
  strcpy(lcdLine2, "Parade Player v2.14 ");
  strcpy(lcdLine3, "Press Reset to Stop ");
  strcpy(lcdLine4, "                    ");

  // Reset button (grounds the RST pin)
  // Press to stop music, and (not coincidentally) clear Heap Fragmentation

  if (now - lastKeyPressed >= 100) {
    lastKeyPressed = now;
    start = micros();
    uint8_t index = keyPad.getKey();
    iChar = plpKey[index];
    //                12345678901234567890
    strcpy(lcdLine3, "Selection:" );   // + the selection number
    strcpy(lcdLine4," " ); // + something!
    stop = micros();

    if (index != 16) {  // NO_KEY is not a thing!
      blurt2Display(lcdLine1, lcdLine2, lcdLine3, lcdLine4, selDelay);
      delay(100); 
      
      switch (iChar) {
        // Control keys
        // 0 - 9 are songs / music
        //                                  12345678901234567890
        case '1': playSelection("/01.MP3", "On the Road Again WN", selDelay); break;
        case '2': playSelection("/02.MP3", "I Get Around B Boys ", selDelay); break;
        case '3': playSelection("/03.MP3", "Walkn on Sunshine KW", selDelay); break;
        case '4': playSelection("/04.MP3", "Armed Forces Medley ", selDelay); break;
        case '5': playSelection("/05.MP3", "This is My Country  ", selDelay); break;
        case '6': playSelection("/06.MP3", "Grand Old Flag      ", selDelay); break;
        case '7': playSelection("/07.MP3", "New AF Medley PBS   ", selDelay); break;
        case '8': playSelection("/08.MP3", "Sousa The Thunderer ", selDelay); break;
        case '9': playSelection("/09.MP3", "Sousa S & S Forever ", selDelay); break;

        // A - D /  0, *, # are Train Sound Effects
        case 'A': playSelection("/10.MP3", "French Whistle Blast", selDelay); break;
        case 'B': playSelection("/11.MP3", "Multi-Whistle Blasts", selDelay); break;
        case 'C': playSelection("/12.MP3", "Startup Chuff       ", selDelay); break;
        case 'D': playSelection("/13.MP3", "Brakes              ", selDelay); break;
        case '*': playSelection("/14.MP3", "Regulate Steam      ", selDelay); break;
        case '0': playSelection("/15.MP3", "Brake Compressor    ", selDelay); break;
        case '#': playSelection("/16.MP3", "Ozzy All Aboard!    ", selDelay); break;

        default:;
      }
    }
  }
}  // End main loop
// ====== ========= ========= ========= ========= ========= ========= =========|
// Funcitions
// Send data for all 4 display lines
void blurt2Display(char *displayLine1, char *displayLine2, 
                   char *displayLine3, char *displayLine4, int delayTime) {
//  lcd.home(); lcd.clear();
  myLCD.PCF8574_LCDClearScreen();
	myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberOne, 0);   myLCD.PCF8574_LCDSendString(displayLine1);
	myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberTwo, 0);   myLCD.PCF8574_LCDSendString(displayLine2);
  myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberThree, 0);	myLCD.PCF8574_LCDSendString(displayLine3);
  myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberFour, 0);  myLCD.PCF8574_LCDSendString(displayLine4);
  delay(delayTime);
}
// Play:  supply Selection #, Nanme for Display, and duration in seconds
void playSelection(char *filePath, char *displayLine4, int selDuration) { 
// Update Display line 4 with the name of the selection
  myLCD.PCF8574_LCDGOTO(myLCD.LCDLineNumberFour, 0);  myLCD.PCF8574_LCDSendString(displayLine4);
  player.playSpecifiedDevicePath(DY::Device::Sd, filePath);  // play the selection
  delay(selDuration); // requred delay 
}
