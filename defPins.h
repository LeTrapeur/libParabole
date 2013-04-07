/*
                        Configuration pins

    D�termine le mappage des pins sur la carte Arduino Mega 2560
    Nombre de pins utilis�es: 10

    Modification: 03/04/2013

    Klempka Tristan, Valentin Roussel

*/
#ifndef DEFPINS_H
#define DEFPINS_H
//
// Entr�es analogiques
extern const int PIN_IN_AZIMUT;         // A0: potentiom�tre azimut
extern const int PIN_IN_ELEV;           // A1: potentiom�tre �levation
//
// Entr�es interruptions
extern const int PIN_IN_INT_DAZIMUT;    // D18: but�e droite azimut
extern const int PIN_IN_INT_GAZIMUT;    // D19: but�e gauche azimut
extern const int PIN_IN_INT_DELEV;      // D20: but�e droite elevation
extern const int PIN_IN_INT_GELEV;      // D21: but�e gauche elevation
//
// Sorties digitales
extern const int PIN_OUT_SENSAZIMUT;    // D30: sens azimut
extern const int PIN_OUT_SENSELEV;      // D31: sens �levation
extern const int PIN_OUT_RDYAZIMUT;     // D32: reprise moteur azimut
extern const int PIN_OUT_RDYELEV;       // D33: reprise moteur elevation
//
// Sorties PWM
extern const int PIN_OUT_PWMAZIMUT;     // D44: moteur azimut
extern const int PIN_OUT_PWMELEV;       // D46: moteur elevation
//
// Pins clavier matriciel (voir manuella)
extern const int PIN_CLAV_ROW1;
extern const int PIN_CLAV_ROW2;
extern const int PIN_CLAV_ROW3;
extern const int PIN_CLAV_ROW4;
extern const int PIN_CLAV_COL1;
extern const int PIN_CLAV_COL2;
extern const int PIN_CLAV_COL3;
//
// Pins LCD (voir manuella)
extern const int PIN_LCD_RS;
extern const int PIN_LCD_E;
extern const int PIN_LCD_D0;
extern const int PIN_LCD_D1;
extern const int PIN_LCD_D2;
extern const int PIN_LCD_D3;
//
// Pins joystick (voir manuella)
extern const int PIN_JOY_X;
extern const int PIN_JOY_Y;

#endif
