#include "actionsParabole.h"

#define UNIT_TO_DEG_AZ 0.1760
#define PWM_TO_DEG_AZ 0.4167
#define UNIT_TO_DEG_EL 0.0880
#define PWM_TO_DEG_EL 2.8333

#define OFF 0
#define ON 1

int FLAG_INTERRUPT = OFF;

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
    if (az < getAzimut()) digitalWrite(PIN_OUT_SENSAZIMUT, LOW);
    else if (az > getAzimut()) digitalWrite(PIN_OUT_SENSAZIMUT, HIGH);
    else
    return;
    // Placement
    int distance = abs(az - getAzimut());
    while(distance > 0 && FLAG_INTERRUPT == OFF)
    {
        // Déplacement proportionnel à la distance à parcourir
        analogWrite(PIN_OUT_PWMAZIMUT, distance*PWM_TO_DEG_AZ);
        distance = abs(az - getAzimut()); // Recalcul de la distance à parcourir
    }
    FLAG_INTERRUPT = OFF;
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
        // Déplacement proportionnel à la distance à parcourir
        analogWrite(PIN_OUT_PWMELEV, distance*PWM_TO_DEG_EL);
        distance = abs(el - getElevation()); // Recalcul de la distance à parcourir
    }
    FLAG_INTERRUPT = OFF;
}

void dplctElev(int dEl)
{
    setElev(getElevation() + dEl);
}

void interruptAzD()
{
    digitalWrite(PIN_OUT_SENSAZIMUT, LOW);
    digitalWrite(PIN_OUT_RDYAZIMUT, HIGH);
    analogWrite(PIN_OUT_PWMAZIMUT, 10);
    FLAG_INTERRUPT = ON;
}

void interruptAzG()
{
    digitalWrite(PIN_OUT_SENSAZIMUT, HIGH);
    digitalWrite(PIN_OUT_RDYAZIMUT, HIGH);
    analogWrite(PIN_OUT_PWMAZIMUT, 10);
    FLAG_INTERRUPT = ON;
}

void interruptElD()
{
    digitalWrite(PIN_OUT_SENSELEV, LOW);
    digitalWrite(PIN_OUT_RDYELEV, HIGH);
    analogWrite(PIN_OUT_PWMELEV, 10);
    FLAG_INTERRUPT = ON;
}

void interruptElG()
{
    digitalWrite(PIN_OUT_SENSELEV, HIGH);
    digitalWrite(PIN_OUT_RDYELEV, HIGH);
    analogWrite(PIN_OUT_PWMELEV, 10);
    FLAG_INTERRUPT = ON;
}
