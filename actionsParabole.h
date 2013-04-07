/*
                        Configuration pins

    Défini les actions de la parabole, sert d'interface logiciel entre l'Arduino
    et la carte de commande

    Modification: 03/04/2013

    Klempka Tristan, Valentin Roussel

*/
#ifndef ACTIONSPARABOLE_H
#define ACTIONSPARABOLE_H
#include "defPins.h"
#include "Arduino.h"

int getAzimut();
int getElevation();
void setAzimut(int az);
void dplctAzimut(int dAz);
void setElev(int el);
void dplctElev(int dEl);
void interruptAzD();
void interruptAzG();
void interruptElD();
void interruptElG();

#endif
