#ifndef bandera_motor_h
#define bandera_motor_h

#include "motores.h"
//extern long tiempo_bandera;
extern Servo bandera;
extern char posicion_bandera;
//1 no hay nada y 0 hay algo.
extern const int s5;

void bandera_posicion_inicial(){
  if(posicion_bandera != 1){// Envía el pulso PWM al pin del servo
  digitalWrite(s5, HIGH);
  delayMicroseconds(1500);
  digitalWrite(s5, LOW);
  delay(30);
  posicion_bandera = 1;}
  /*delay(15);
  bandera.write(90);
  delay(15);*/
}
void bandera_der(){
  if(sensores[0]==0 && posicion_bandera>0)
  {
  posicion_bandera=posicion_bandera-1;
  // Envía el pulso PWM al pin del servo
  digitalWrite(s5, HIGH);
  delayMicroseconds(500);
  digitalWrite(s5, LOW);
  delay(30);
  }
  /*delay(15);
  bandera.write(0);
  delay(15);*/
  /*if(tiempo_bandera == 0){tiempo_bandera = millis();}
  if((millis() - tiempo_bandera) < 135){bandera.write(0);}*/
  /*if(posicion_bandera<2)
  {
    posicion_bandera=posicion_bandera+1;
    bandera.write(0);
    delay(135);
  }*/
}
void bandera_izq(){
  if(sensores[3]==0 && posicion_bandera<2)
  {
    posicion_bandera=posicion_bandera+1;
    // Envía el pulso PWM al pin del servo
    digitalWrite(s5, HIGH);
    delayMicroseconds(2300);
    digitalWrite(s5, LOW);
    delay(30);
  }
  /*delay(15);
  bandera.write(180);
  delay(15);*/
  /*if(tiempo_bandera == 0){tiempo_bandera = millis();}
  if((millis() - tiempo_bandera) < 135){bandera.write(180);}*/
  /*if(posicion_bandera>0)
  {
    posicion_bandera=posicion_bandera-1;
      bandera.write(180);
    delay(135);
  }*/
}

#endif