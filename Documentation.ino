/*
Hardware:  See Fritzing Schematic for wiring. (on Github....)

  (1) Arduino nano
  (1) 20x4 Display with I2C Interface Module
  (2) 16 Push button telephone keypads /  PCF8574  (*2 if you need a wired Remote)
  (1) LM2596 DC-DC Buck Converter (Input 5.2 to 35V Output 1.25 to 30V)  CAREFUL, no Reverse Polarity Circuit
  (1) Rocker Switch  PS1   Master Power Switch (Eventually this will turn off the AMP as well) 
  (1) DY-SV5W MP3 Player (Any that works https://github.com/SnijderC/dyplayer/tree/main
  
  Variable
  (1) Kenwood KDC-895 Head Unit (Radio/CD/Line In)  Just a headunit with an line in
  (2) Rockville RWB65W Marine Speakers

  *  Include an arduino reset button (Heap Fragmentation)  (Ground RST)
  Can use vehicle 12 volts (use FUSED hot wire), but use a dedicated batter for stable power.
    The vehicle this was designed for is very old and I don't trust the electrics.
// ====== ========= ========= ========= ========= ========= ========= =========|

Sources:  (SIM Card contains all code and documents)
Datasheet: https://grobotronics.com/images/companies/1/datasheets/DY-SV5W%20Voice%20Playback%20ModuleDatasheet.pdf
Example Implementation:  https://github.com/SnijderC/dyplayer
16-key keypad with an Arduino and a PCF8574 I/O expander module example (Borrowed heavly from this)
  https://curiousscientist.tech/blog/16-key-keypad-arduino-simplified

// ====== ========= ========= ========= ========= ========= ========= =========|
Sound File SD Card Instructions  ## Loading sound files

For normal playback of sound files, I recommend you name your files
sequentially and put them in the root directory of the drive unless you need
something more fancy. The numbering should be as follows:

00001.mp3
00002.mp3
00003.mp3
...

#### Important: files do not play in order of named sequence  <<<--------

The [`DY::DYPlayer::playSpecified`] function will **not** necessarily play the 
sound file named `00001.MP3` when asked to play sound file `1`. The module will 
look for the first sound file found in the filesystem. It's not using the file 
name, neither does it order by file name. 

To be sure the sound files play in the expected order:

1. Empty the storage device.
2. Make sure there aren't any trash files on the storage device.
3. Copy the files in the order they should be played (it helps to have them
   named sequentially, sort by name and copy the files, usually they will be
   copied in sequence order.
// ====== ========= ========= ========= ========= ========= ========= =========|


// ====== ========= ========= ========= ========= ========= ========= =========|
LCD Commands:
    lcd.setBacklight(255)     lcd.noDisplay();          lcd.display();
    lcd.clear();              lcd.home();               lcd.print("Hello LCD")
    lcd.scrollDisplayLeft()   lcd.scrollDisplayRight()  lcd.setCursor(0,0)(0,1)
    ABCD = Loco Sfx           Numbers = Music           * = Stop Playing 
   FUTURE: # Bank 2 of Numbers (More Music)             # = Play Selection

*/

