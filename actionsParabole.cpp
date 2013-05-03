#include "actionsParabole.h"
// TODO Conversion à refaire
// TODO Tester fonction arrêt
// TODO Tester alimentation PC Fixe
#define UNIT_TO_DEG_AZ 0.1760
#define PWM_TO_DEG_AZ 0.4167
#define UNIT_TO_DEG_EL 0.0880
#define PWM_TO_DEG_EL 2.8333

#define OFF 0
#define ON 1

<<<<<<< HEAD
#define VIT 100
=======
#define H_SPEED 255
#define L_SPEED 105
>>>>>>> b26a56413db5c8b57d230ec487717021df9ab574

volatile int FLAG_INTERRUPT = OFF;

int getAzimut()
{
    return (analogRead(PIN_IN_AZIMUT) * UNIT_TO_DEG_AZ);
}

int getElevation()
{
    return (analogRead(PIN_IN_ELEV) * UNIT_TO_DEG_EL);
}

void setAzimut(int az)
{
    // Déterminer sens
    if (az < getAzimut()) digitalWrite(PIN_OUT_SENSAZIMUT, HIGH); //
    else if (az > getAzimut()) digitalWrite(PIN_OUT_SENSAZIMUT, LOW); // !!
    else
    return;
    // Placement
    int distance = abs(az - getAzimut());
    while(distance > 0 && FLAG_INTERRUPT == OFF)
    {
        // Déplacement proportionnel à la distance à parcourir
        if(distance > 5)
            analogWrite(PIN_OUT_PWMAZIMUT, H_SPEED);
        else
            analogWrite(PIN_OUT_PWMAZIMUT, L_SPEED);

        distance = abs(az - getAzimut()); // Recalcul de la distance à parcourir
    }
    FLAG_INTERRUPT = OFF;
}

void stopAzimut()
{
    analogWrite(PIN_OUT_PWMAZIMUT, 0);
}

void dplctAzimut(int dAz)
{
    setAzimut(getAzimut() + dAz);
}

void setElev(int el)
{
    // Déterminer sens
    if (el < getElevation()) digitalWrite(PIN_OUT_SENSELEV, LOW);
    else if (el > getElevation()) digitalWrite(PIN_OUT_SENSELEV, HIGH);
    else
    return;
    // Placement
    int distance = abs(el - getElevation());
    while(distance > 0 && FLAG_INTERRUPT == OFF)
    {
        if(distance > 5)
            analogWrite(PIN_OUT_PWMELEV, H_SPEED);
        else
            analogWrite(PIN_OUT_PWMELEV, L_SPEED);

        distance = abs(az - getAzimut()); // Recalcul de la distance à parcourir
    }
    FLAG_INTERRUPT = OFF;
}

void stopElev()
{
    analogWrite(PIN_OUT_PWMELEV, 0);
}

void dplctElev(int dEl)
{
    setElev(getElevation() + dEl);
}

void interruptDAz()
{
    Serial.println("interrupt! AzD");//DEBUG
    digitalWrite(PIN_OUT_SENSAZIMUT, LOW);
    digitalWrite(PIN_OUT_RDYAZIMUT, HIGH);
    analogWrite(PIN_OUT_PWMAZIMUT, L_SPEED);
    FLAG_INTERRUPT = ON;
}

void interruptGAz()
{
    Serial.println("interrupt! AzG");//DEBUG
    digitalWrite(PIN_OUT_SENSAZIMUT, HIGH);
    digitalWrite(PIN_OUT_RDYAZIMUT, HIGH);
    analogWrite(PIN_OUT_PWMAZIMUT, L_SPEED);
    FLAG_INTERRUPT = ON;
}

void interruptHEl()
{
    Serial.println("interrupt! ElD"); //DEBUG
    digitalWrite(PIN_OUT_SENSELEV, LOW);
    digitalWrite(PIN_OUT_RDYELEV, HIGH);
    analogWrite(PIN_OUT_PWMELEV, L_SPEED);
    FLAG_INTERRUPT = ON;
}

void interruptBEl()
{
    Serial.println("interrupt! ElG"); //DEBUG
    digitalWrite(PIN_OUT_SENSELEV, HIGH);
    digitalWrite(PIN_OUT_RDYELEV, HIGH);
    analogWrite(PIN_OUT_PWMELEV, L_SPEED);
    FLAG_INTERRUPT = ON;
}
