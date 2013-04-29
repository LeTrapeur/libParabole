/*

        Interface de commande

*/

#ifndef INTERFACECMD_H
#define INTERFACECMD_H

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <WebServer.h>
#include <SPI.h>
#include <Ethernet.h>

#include "defPins.h"
#include "actionsParabole.h"
#include "Arduino.h"

template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

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

void CmdForm(WebServer &server, WebServer::ConnectionType type, char *, bool);
void CmdPos(WebServer &server, WebServer::ConnectionType type, char *, bool);

#endif
