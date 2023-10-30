#ifndef bandera_motor_h
#define bandera_motor_h

#include "motores.h"
//extern long tiempo_bandera;
extern Servo bandera;
extern char posicion_bandera;
void bandera_der(){
  /*if(tiempo_bandera == 0){tiempo_bandera = millis();}
  if((millis() - tiempo_bandera) < 135){bandera.write(0);}*/
  if(posicion_bandera<2)
  {
    posicion_bandera=posicion_bandera+1;
    bandera.write(0);
    delay(135);
  }
}
void bandera_izq(){
  /*if(tiempo_bandera == 0){tiempo_bandera = millis();}
  if((millis() - tiempo_bandera) < 135){bandera.write(180);}*/
  if(posicion_bandera>0)
  {
    posicion_bandera=posicion_bandera-1;
      bandera.write(180);
    delay(135);
  }
}
#endif