#include "defPins.h"

//Entrées analogiques
const int PIN_IN_AZIMUT = 0;        // A0: potentiomètre azimut
const int PIN_IN_ELEV = 1;          // A1: potentiomètre élevation
//
// Entrées interruptions
const int PIN_IN_INT_DAZIMUT = 18;  // D18: butée droite azimut
const int PIN_IN_INT_GAZIMUT = 19;  // D19: butée gauche azimut
const int PIN_IN_INT_DELEV = 20;    // D20: butée droite elevation
const int PIN_IN_INT_GELEV = 21;    // D21: butée gauche elevation
//
// Sorties digitales
const int PIN_OUT_SENSAZIMUT = 30;  // D30: sens azimut
const int PIN_OUT_SENSELEV = 31;    // D31: sens élevation
const int PIN_OUT_RDYAZIMUT = 32;   // D32: reprise moteur azimut
const int PIN_OUT_RDYELEV = 33;     // D33: reprise moteur elevation
//
// Sorties PWM
const int PIN_OUT_PWMAZIMUT = 44;   // D44: moteur azimut
const int PIN_OUT_PWMELEV = 46;     // D46: moteur elevation
//
// Pins clavier matriciel (voir manuella)
const int PIN_CLAV_ROW1 = 25;
const int PIN_CLAV_ROW2 = 26;
const int PIN_CLAV_ROW3 = 27;
const int PIN_CLAV_ROW4 = 28;
const int PIN_CLAV_COL1 = 22;
const int PIN_CLAV_COL2 = 23;
const int PIN_CLAV_COL3 = 24;
//
// Pins LCD (voir manuella)
const int PIN_LCD_RS = 8;
const int PIN_LCD_E = 9;
const int PIN_LCD_D0 = 2;
const int PIN_LCD_D1 = 3;
const int PIN_LCD_D2 = 5;
const int PIN_LCD_D3 = 6;
//
// Pins joystick (voir manuella)
const int PIN_JOY_X = 6;
const int PIN_JOY_Y = 7;
