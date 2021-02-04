# USB-Arduino-Media-Controller
Usb media control, made for Arduino Pro Micro (or Leonardo ?) 5V



//---------------------------------------------------------------------------------------------------------
// Usb media control, adapted by Moxl
// Version: 1.0
// Made for Arduino Pro Micro (or Leonardo ?) 5V
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
