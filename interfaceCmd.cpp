#include "interfaceCmd.h"

    /** KEYPAD **/
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] =
 {{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
byte rowPins[ROWS] = {
  PIN_CLAV_ROW1, PIN_CLAV_ROW2, PIN_CLAV_ROW3, PIN_CLAV_ROW4};
byte colPins[COLS] = {
  PIN_CLAV_COL1, PIN_CLAV_COL2, PIN_CLAV_COL3};
Keypad KEYPAD_MANUELLA = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

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
    // Entrées interruptions avec pull down externe
//    pinMode(PIN_IN_INT_DAZIMUT, INPUT);
//    digitalWrite(PIN_IN_INT_DAZIMUT, HIGH);
    attachInterrupt(5, interruptAzD, LOW);
//    pinMode(PIN_IN_INT_GAZIMUT, INPUT);
//    digitalWrite(PIN_IN_INT_GAZIMUT, HIGH);
    attachInterrupt(4, interruptAzG, LOW);
//    pinMode(PIN_IN_INT_DELEV, INPUT);
//    digitalWrite(PIN_IN_INT_DELEV, HIGH);
    attachInterrupt(3, interruptElD, LOW);
//    pinMode(PIN_IN_INT_DELEV, INPUT);
//    digitalWrite(PIN_IN_INT_DELEV, HIGH);
    attachInterrupt(2, interruptElG, LOW);
    //
    // Sorties digitales
    pinMode(PIN_OUT_SENSAZIMUT,OUTPUT);
    pinMode(PIN_OUT_SENSELEV,OUTPUT);
    pinMode(PIN_OUT_RDYAZIMUT,OUTPUT);
    pinMode(PIN_OUT_RDYELEV,OUTPUT);
    //
    // Sorties PWM
    pinMode(PIN_OUT_PWMAZIMUT,OUTPUT);
    pinMode(PIN_OUT_PWMELEV,OUTPUT);
}

/** JOYSTICK **/

const int JOY_MIN_CENTER = -125;
const int JOY_MAX_CENTER = 125;
//
// Renvoie direction du joystick
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

    /** INTERFACE COMMANDE **/
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
            Serial.println(getAzimut());     //DEBUG
            Serial.println(getElevation());     //DEBUG
            key = KEYPAD_MANUELLA.getKey();
            if(key != NO_KEY)
            {
                switch(key)
                {
                case '1':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode clavier");
                    delay(500);
                    commandeClavier();
                    choixMenu = true;
                    break;
                case '2':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode joystick");
                    delay(500);
                    commandeJoystick();
                    choixMenu = true;
                    break;
                case '3':
                    LCD_MANUELLA.clear();
                    LCD_MANUELLA.print("Mode serveur");
                    delay(500);
                    commandeServeur();
                    choixMenu = true;
                    break;
                default:
                    break;
                }
            }
        }
    }
}
//
// Permet de positionner la parabole à l'aide d'une selection clavier.
// Vérifie que les coordonnées sont correctes avant de déplacer
void commandeClavier()
{
    int az = getAzimut();
    int el = getElevation();

    char str[4] = "";
    int chiffre = 0;
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

                if(chiffre <= 2)
                {
                    // Construction du nombre
                    str[chiffre] = key;
                    str[chiffre+1] = '\0';
                    LCD_MANUELLA.print(key);
                    ++chiffre;
                }
            }
        }while(key != '#');
        LCD_MANUELLA.clear();
        // Si erreur on redemande les valeurs sinon on sort de la boucle
        az = atoi(str);
        if(az < 0 || az > 180)
        {
            LCD_MANUELLA.print("Erreur");
            delay(1000);
            chiffre = 0;
        }
        else
        {
            LCD_MANUELLA.print("Dplct en cours");
            setAzimut(az);
            stopAzimut();
            runningA = false;
        }
    }

        // ELEVATION //
    chiffre = 0;
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

                if(chiffre <= 2)
                {
                    // Construction du nombre
                    str[chiffre] = key;
                    str[chiffre+1] = '\0';
                    LCD_MANUELLA.print(key);
                    ++chiffre;
                }
            }
        }while(key != '#');
        LCD_MANUELLA.clear();
        // Si erreur on redemande les valeurs sinon on sort de la boucle
        el = atoi(str);
        if(el < 0 || el > 90)
        {
            LCD_MANUELLA.print("Erreur");
            delay(1000);
            chiffre = 0;
        }
        else
        {
            LCD_MANUELLA.print("Dplct en cours");
            setElev(el);
            stopElev();
            runningE = false;
        }
    }
}
//
// Permet le déplacement relatif de la parabole à l'aide d'un joystick (4 directions numériques)
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
                dplctAzimut(1);
                break;
            case JOY_LEFT:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct gauche");
                dplctAzimut(-1);
                break;
            case JOY_UP:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct haut  ");
                dplctElev(1);
                break;
            case JOY_DOWN:
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Dplct bas   ");
                dplctElev(-1);
                break;
            default:
                stopAzimut();
                stopElev();
                LCD_MANUELLA.setCursor(0,1);
                LCD_MANUELLA.print("Aucun dplct ");
                break;
        }
    }
}

#define PREFIX ""

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static uint8_t ip[] = { 172, 27, 129, 231 };
WebServer webserver(PREFIX, 80);

void CmdForm(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  webserver.httpSuccess();

    if (type == WebServer::POST)
  {
    bool repeat;
    char az[16];
    char elev[16];
    unsigned int azimut = 0;
    unsigned int elevation = 0;

    webserver.readPOSTparam("azimut", 7, az, 16);
    webserver.readPOSTparam("elevation", 10, elev, 16);

    azimut = (int)strtoul(az, NULL, 10);
    elevation = (int)strtoul(elev, NULL, 10);

    if (azimut > 0 && azimut <= 180)
    {
        setAzimut(azimut);
        stopAzimut();
    }
    if (elevation > 0 && elevation <= 90)
    {
        setElev(elevation);
        stopElev();
    }

  if (type != WebServer::HEAD)
  {
    P(Msg) =
        "<html><head>"

        "<title>Controle Parabole</title>"

        "<body>"

        "<h1>Controle Parabole</h1>"

        "<form action='"PREFIX"' method='POST'>"
        "<p><label for='azimut'>Azimut: </label><br />"
        "<input type='text' name='az' id='azimut' /></p>"
        "<p><label for='elevation'>Elevation: </label><br />"
        "<input type='text' name='elev' id='elevation' /></p>"
        "<p><INPUT type='submit'></p>"
        "</form>"

        "<form action='"PREFIX"/positions' method='POST'>"
        "<input type='submit' value='Positions'>"
        "</form>"

        "</body></html>";

    webserver.printP(Msg);
  }
}

void CmdPos(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
    webserver.httpSuccess();

    char *azimut = (char*)malloc(sizeof(char)*4);
    char *elevation = (char*)malloc(sizeof(char)*4);

    azimut = itoa(getAzimut(), azimut, 10);
    elevation = itoa(getElevation(), elevation, 10);

    if (type != WebServer::HEAD)
    {
        webserver << "<html><head>" "<title>Positions Parabole</title>";
        webserver << "<body>" "<h1>Positions Parabole</h1>";
        webserver << "<p>Azimut: " << azimut << "</p>";
        webserver << "<p>Elevation: " << elevation << "</p>";
        webserver <<  "<form action='"PREFIX"/controle' method='POST'>" "<input type='submit' value='Controle'>" "</body></html>";
    }

}

void commandeServeur()
{
    Ethernet.begin(mac, ip);
    webserver.setDefaultCommand(&CmdForm);
    webserver.addCommand("controle", &CmdForm);
    webserver.addCommand("positions", &CmdPos);
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




