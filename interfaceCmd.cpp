#include "interfaceCmd.h"
#include <WebServer.h>

    /** KEYPAD **/
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {
  PIN_CLAV_ROW1, PIN_CLAV_ROW2, PIN_CLAV_ROW3, PIN_CLAV_ROW4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  PIN_CLAV_COL1, PIN_CLAV_COL2, PIN_CLAV_COL3}; //connect to the column pinouts of the keypad
Keypad KEYPAD_MANUELLA = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//WebServer webserver = WebServer("",80);


    /** LCD **/
LiquidCrystal LCD_MANUELLA(PIN_LCD_RS, PIN_LCD_E, PIN_LCD_D0, PIN_LCD_D1, PIN_LCD_D2, PIN_LCD_D3);



    /** PINS **/
void interruptAzD(); // Déclaration anticipée
void interruptAzG(); // Déclaration anticipée
void interruptElD(); // Déclaration anticipée
void interruptElG(); // Déclaration anticipée
void initPins()
{
    // Entrées analogiques
    // Utiliser directement analogRead()
    //
    // Entrées interruptions
    attachInterrupt(PIN_IN_INT_DAZIMUT, interruptAzD, HIGH);
    attachInterrupt(PIN_IN_INT_GAZIMUT, interruptAzG, HIGH);
    attachInterrupt(PIN_IN_INT_DELEV, interruptElD, HIGH);
    attachInterrupt(PIN_IN_INT_GELEV, interruptElG, HIGH);
    //
    // Sorties digitales
    pinMode(PIN_OUT_SENSAZIMUT,OUTPUT);
    pinMode(PIN_OUT_SENSELEV,OUTPUT);
    pinMode(PIN_OUT_RDYAZIMUT,OUTPUT);
    pinMode(PIN_OUT_RDYELEV,OUTPUT);
    //
    // Sorties PWM
    pinMode(PIN_OUT_SENSAZIMUT,OUTPUT);
    pinMode(PIN_OUT_SENSELEV,OUTPUT);
}



/** Joystick **/

const int JOY_MIN_CENTER = -125;
const int JOY_MAX_CENTER = 125;

JOYDIR getJoyDir()
{
    int x = analogRead(PIN_JOY_X) - 525;    // Translation
    int y = -(analogRead(PIN_JOY_Y) - 525); // Translation

    if( y > JOY_MAX_CENTER)
    {
        if(x > y) return JOY_RIGHT;
        else if(x > - y) return JOY_UP;
        else
        return JOY_LEFT;
    }
    else if( y < JOY_MIN_CENTER)
    {
        if(x > - y) return JOY_RIGHT;
        else if(x > y) return JOY_DOWN;
        else
        return JOY_LEFT;
    }
    else
    {
        if(x > JOY_MAX_CENTER) return JOY_RIGHT;
        else if(x < JOY_MIN_CENTER) return JOY_LEFT;
    }
    return JOY_CENTER;
}

    /** Interface de commande **/
void commandeMenu()
{
    // Présentation //
    LCD_MANUELLA.clear();
    LCD_MANUELLA.print("Interface cmd");
    LCD_MANUELLA.setCursor(0,1);
    LCD_MANUELLA.print("by FlippyMaster");
    delay(1000);
    LCD_MANUELLA.setCursor(0,1);
    LCD_MANUELLA.print("and Val0u      ");
    delay(1000);
    // Menu cmd
    bool running = true;
    bool choixMenu = false;
    char key = 'x';
    while(running)
    {
        LCD_MANUELLA.clear();
        LCD_MANUELLA.print("1 Clav. 2 Jstick");
        LCD_MANUELLA.setCursor(0,1);
        LCD_MANUELLA.print("3 Serveur");
        choixMenu = false;
        while(!choixMenu)
        {
            key = KEYPAD_MANUELLA.getKey();
            if(key != NO_KEY)
            {
                switch(key)
                {
                case '1':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode clavier");
                    delay(1000);
                    commandeClavier();
                    choixMenu = true;
                    break;
                case '2':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode joystick");
                    delay(1000);
                    commandeJoystick();
                    choixMenu = true;
                    break;
                case '3':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode serveur");
                    delay(1000);
                    commandeServeur();
                    choixMenu = true;
                    break;
                default:
                    break;
                }
            }
        }
    }

//    commandeClavier()
//    commandeJoystick()

}

void commandeClavier()
{
    int az = getAzimut();
    int el = getElevation();

    char str[4] = "";
    int i = 0;
    char key = 'x';

    bool runningA = true;
    while(runningA)
    {
        // AZIMUT //
        LCD_MANUELLA.clear();
        LCD_MANUELLA.print("Azimut : ");
        LCD_MANUELLA.setCursor(9,0);
        do
        {
            Serial.println(key);
            key = KEYPAD_MANUELLA.getKey();
            if(key != NO_KEY)
            {
                if(key == '*')
                    return;

                if(i <= 2)
                {
                    str[i] = key;
                    str[i+1] = '\0';
                    LCD_MANUELLA.print(key);
                    ++i;
                }
            }
        }while(key != '#');
        LCD_MANUELLA.clear();
        i = 0;

        az = atoi(str);
        if(az < 0 || az > 180)
        {
            LCD_MANUELLA.print("Erreur");
            delay(1000);
        }
        else
        {
            LCD_MANUELLA.print("Dplct en cours");
            setAzimut(az);
            runningA = false;
        }
    }

        // ELEVATION //
    bool runningE = true;
    while (runningE)
    {
        LCD_MANUELLA.clear();
        LCD_MANUELLA.print("Elevat : ");
        LCD_MANUELLA.setCursor(9,0);
        do
        {
            Serial.println(key);
            key = KEYPAD_MANUELLA.getKey();
            if(key != NO_KEY)
            {
                if(key == '*')
                    return;

                if(i <= 2)
                {
                    str[i] = key;
                    str[i+1] = '\0';
                    LCD_MANUELLA.print(key);
                    ++i;
                }
            }
        }while(key != '#');
        LCD_MANUELLA.clear();

        el = atoi(str);
        if(el < 0 || el > 90)
        {
            LCD_MANUELLA.print("Erreur");
            delay(1000);
            i = 0;
        }
        else
        {
            LCD_MANUELLA.print("Dplct en cours");
            setAzimut(el);
            runningE = false;
        }
    }
}

void commandeJoystick()
{
    bool running = true;
    char key = 'x';
    while(running)
    {
        key = KEYPAD_MANUELLA.getKey();
        if(key == '*') return;

        JOYDIR dir = getJoyDir();
        switch(dir)
        {
            case JOY_RIGHT:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct droite");
    //            dplctAzimut(1);
                break;
            case JOY_LEFT:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct gauche");
    //            dplctAzimut(-1);
                break;
            case JOY_UP:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct haut  ");
    //            dplctElev(1);
                break;
            case JOY_DOWN:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct bas   ");
    //            dplctElev(-1);
                break;
            default:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Aucun dplct ");
                break;
        }
    }
}

#define PREFIX ""

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static uint8_t ip[] = { 172, 27, 132, 200 };
WebServer webserver(PREFIX, 80);

void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  /* this line sends the standard "we're all OK" headers back to the
     browser */
  webserver.httpSuccess();

  /* if we're handling a GET or POST, we can output our data here.
     For a HEAD request, we just stop after outputting headers. */
  if (type != WebServer::HEAD)
  {
    /* this defines some HTML text in read-only memory aka PROGMEM.
     * This is needed to avoid having the string copied to our limited
     * amount of RAM. */
    P(helloMsg) = "<h1>Arduino Web Server</h1>";

    /* this is a special form of print that outputs from PROGMEM */
    webserver.printP(helloMsg);
  }
}


void commandeServeur()
{
    Ethernet.begin(mac, ip);
    webserver.setDefaultCommand(&helloCmd);
    webserver.addCommand("index.html", &helloCmd);
    webserver.begin();


    bool running = true;
    char key = 'x';
    while(running)
    {
        LCD_MANUELLA.clear();
        LCD_MANUELLA.print("Serveur actif");
        while(1)
        {
            key = KEYPAD_MANUELLA.getKey();
            if(key == '*') return;
            char buff[64];
            int len = 64;
            webserver.processConnection(buff, &len);
        }
    }
}




