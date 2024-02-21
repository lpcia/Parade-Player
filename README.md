# Parade Player
Arduino based DY-???? MP3 Player with I2CKeyPad input, and a HD44780 LCD Display 
This version works with an automobile head-unit/large weatherproof speakers.

## Concept

This is an Arduino Project that lets people interact with a automated display.

## Background
I belong to a G Scale model railroad club that sets up large displays at train shows and local civic events such as a Christmas display at our city museum.  I wanted to make a display / decoration of an old service station that visitors could interact with to play sounds, start animatronics, or turn on lights by pressing a button on a (wired) remote keypad.

I had been toying around with various keypads / mp3 player circuit boards, etc. when a veterans group I belong to finally decided to reactivate an old self-propelled locomotive parade float that had been sitting in a garage for 15 years.  The vehicle is a modified 1938 Nash Lafayette built at the Nash plant her in Kenosha, WI.  In order to modernize her, We had to remove 200+ pounds of compressors, tanks, air lines and 80 years of old wiring and automotive electronics from the 1970's.  Instead of using air, I decided to use electronics to play music and sounds and re-engineered my idea into this Parade Locomotive Player.

## Operations
The MP3 Player is powered by the vehicle's 12 volt battery via a buck converter.  It is connected to the vehicle radio/ head-unit via the aux port.  In my case, I can play CD's and the Radio through the fender mounted speakers using the radio's controls.  Volume is also controlled by the radio.  

To play sounds, simply push a button on the keypad, and i'n my case a wired remote.  We added a remote because the driver cannot see the right front because of bells and smoke stacks, so a co-enginneer is required.  Even for them, pressing one of the buttons on the unit took their eyes off the road, so the remote was added.  It is simply a second keyboard / PCF8574 Remote 8-Bit I/O Expander for I2C Bus.  I wired it with a ten foot, tough old USB cable and used the existing USB connector (Probably a bad idea, but it works!).  Oddly the wired remote works without changes to the code.  I thought I was going to have to change the I2C address, but it just worked.


## Etcetera
Check out the pictures of our locomotive in the Media folder or visit https://sewivets.org/Voiture410/ 

> If you would like to donate to this project or our Nurses Training Fund, please see details on the website.

Thanks to 
1. Chris Snijde for the awesome work he did to make using generic DY players easy to use.
    - https://github.com/SnijderC/dyplayer
3. Gavin Lyons for is work with HD44780_LCD_PCF8574.h
    - https://github.com/gavinlyonsrepo/HD44780_LCD_PCF8574
4. And of course Adafruit!
    - https://www.adafruit.com
