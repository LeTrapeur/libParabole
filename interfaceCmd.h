/*

        Interface de commande

*/

#ifndef INTERFACECMD_H
#define INTERFACECMD_H

#include "defPins.h"
#include "actionsParabole.h"
#include "Arduino.h"
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>

extern LiquidCrystal LCD_MANUELLA;
extern Keypad KEYPAD_MANUELLA;
extern WebServer webserver;

extern const int JOY_MIN_CENTER;
extern const int JOY_MAX_CENTER;

enum JOYDIR{JOY_RIGHT, JOY_LEFT, JOY_UP, JOY_DOWN, JOY_CENTER};
JOYDIR getJoyDir();

void initPins();

void commandeMenu();
void commandeClavier();
void commandeJoystick();

void commandeServeur();
void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool);



#endif
