
#include <HID-Project.h>                    //include HID_Project library
#include <HID-Settings.h>

//---------------------------------------------------------------------------------------------------------
// Usb media control, adapted by Moxl
// Version: 1.0
// Made for Arduino Pro Micro (or Leonardo ?) 5V
// To be compiled in Arduino IDE
// Works on Win10. Can be adapted for Linux/OSX, yet not confirmed supported on anything else.
// It checks for buttonpresses and will send key accordingly 
// It will be seen by computer as a second keyboard and no additional software is required, but that also has it limitations.
// See the sources for other buttons which can be send to host.
//
// Disclaimer: This was witten for personal use and I take no responsibility for anything you do with it.
//---------------------------------------------------------------------------------------------------------
// Wiring:
// play_BTN = 7 -> Should be pulled down with 10k resistor to GND, and button connected to VCC.
// next_BTN = 8 -> Should be pulled down with 10k resistor to GND, and button connected to VCC.
// prev_BTN = 6 -> Should be pulled down with 10k resistor to GND, and button connected to VCC.
// mute_BTN = 9 -> Should be pulled down with 10k resistor to GND, and button connected to VCC.
// 10K potentiometer = A0
//---------------------------------------------------------------------------------------------------------
//Sources: https://uboopenfactory.univ-brest.fr/Les-Labs/MusicLab/Projets/Arduino-Media-Keys
//         https://github.com/qwelyt/Keyboard/blob/master/Code/ModuleA/V2/ModuleA/Key.h
//
//---------------------------------------------------------------------------------------------------------
// To add a button to the code:
//---------------------------------------------------------------------------------------------------------
//--> Add this to variables
// const int any_BTN = 5;
// pinMode(any_BTN, INPUT);
//
//--> Add this to loop
// if (digitalRead(play_BTN)==HIGH) {
//    // Write single keys, do not use a number here!
//    Consumer.write(MEDIA_PLAY_PAUSE);
//    // Simple debounce
//    delay(300);
//  }
//---------------------------------------------------------------------------------------------------------



//Set rotation of the potentiometer. (true or false)
#define REVERSED true                       

//defining variables
int val = 0;
int previousval = 0;
int val2 = 0;

//Setting pins 
const int pinLed = LED_BUILTIN;
const int play_BTN = 7;
const int next_BTN = 8;
const int prev_BTN = 6;
const int mute_BTN = 9;


 //start of setup---------------------------------------------------------------------------------------
void setup() {

  
  //Setting pins
       pinMode(pinLed, OUTPUT);
       pinMode(play_BTN, INPUT);
       pinMode(mute_BTN, INPUT);
       pinMode(next_BTN, INPUT);
       pinMode(prev_BTN, INPUT);
       
   //initialize computer connection  
      Consumer.begin(); 
          
   //wait for computer to connect                    
      delay(1000);             

   //setting starting parameters.
  for(int a = 0; a < 52; a++) {
        Consumer.write(MEDIA_VOLUME_DOWN);      //set the volume to 0
        delay(2);
      }
  //starting 
  Keyboard.begin();

 //end of setup---------------------------------------------------------------------------------------
 }



 //start of loop---------------------------------------------------------------------------------------
void loop() {

  //Reading pinvalue for A0
  val = analogRead(A0);                      //read potentiometer value  
  val = map(val, 0, 1023, 0, 101);          //map it to 102 steps

  //if reversed then change 
  if(REVERSED) {
    val = 101 - val;
  }



// If you want to add functions: check https://uboopenfactory.univ-brest.fr/Les-Labs/MusicLab/Projets/Arduino-Media-Keys
// Also check https://github.com/qwelyt/Keyboard/blob/master/Code/ModuleA/V2/ModuleA/Key.h for more references.
// MEDIA_FAST_FORWARD 0xB3
// MEDIA_REWIND 0xB4
// MEDIA_NEXT 0xB5
// MEDIA_PREVIOUS 0xB6
// MEDIA_STOP 0xB7
// MEDIA_PLAY_PAUSE 0xCD
// MEDIA_VOLUME_MUTE 0xE2
// MEDIA_VOLUME_UP 0xE9
// MEDIA_VOLUME_DOWN 0xEA
// CONSUMER_EMAIL_READER 0x18A
// CONSUMER_CALCULATOR 0x192
// CONSUMER_EXPLORER 0x194
// CONSUMER_BROWSER_HOME 0x223
// CONSUMER_BROWSER_BACK 0x224
// CONSUMER_BROWSER_FORWARD 0x225
// CONSUMER_BROWSER_REFRESH 0x227
// CONSUMER_BROWSER_BOOKMARKS 0x22A

//check for buttonpresses.

 if (digitalRead(play_BTN)==HIGH) {
    // Write single keys, do not use a number here!
    Consumer.write(MEDIA_PLAY_PAUSE);
    // Simple debounce
    delay(300);
  }

   if (digitalRead(mute_BTN)==HIGH) {
    // Write single keys, do not use a number here!
    Consumer.write(MEDIA_VOLUME_MUTE);
    // Simple debounce
    delay(300);
  }

   if (digitalRead(next_BTN)==HIGH) {
    // Write single keys, do not use a number here!
    Consumer.write(MEDIA_NEXT);
    // Simple debounce
    delay(300);
  }

   if (digitalRead(prev_BTN)==HIGH) {
    // Write single keys, do not use a number here!
    Consumer.write(MEDIA_PREVIOUS);
    // Simple debounce
    delay(300);
  }


  //Setting the volume by potentiometer.
  if(abs(val - previousval) > 1) {          //check if potentiometer value has changed
    previousval = val;
    val /= 2;                               //divide it by 2 to get 51 steps
    while(val2 < val) {
      Consumer.write(MEDIA_VOLUME_UP);      //turn volume up to appropiate level
      val2++;
      delay(2);
    }
    while(val2 > val) {
      Consumer.write(MEDIA_VOLUME_DOWN);    //turn volume down to appropiate level
      val2--;
      delay(2);
    }
    delay(301); 
                       //wait at least 300ms between changing volume levels
                       //if it will change faster Windows can sometimes 
                       //increase or decrease volume by 10 steps at once
  }



 //end of loop---------------------------------------------------------------------------------------  
}
