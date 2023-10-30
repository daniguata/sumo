#ifndef bandera_motor_h
#define bandera_motor_h

#include "declaraciones.h"
#include <Servo.h>

void vandera_der(){
  bandera.write(0);
  delay(135);
  bandera.write(90);
}
void vandera_izq(){
  bandera.write(180);
  delay(135);
  bandera.write(90);
}
#endif