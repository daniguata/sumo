#ifndef motores_h
#define motores_h

/*Pines Motor*/
  /*motor 1*/
  extern const int pinAIN1;
  extern const int pinAIN2;
  extern const int pinPWMA;
  /*motor 2*/
  extern const int pinBIN1;
  extern const int pinBIN2;
  extern const int pinPWMB;

/*pertenece a motores.h*/
/*para mandar el sumo asia delante a cierta velocidad por defecto a 255*/
void motores_delante(int velocidad = 255)
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, HIGH);
    digitalWrite(pinAIN2, LOW);
    analogWrite(pinPWMA, velocidad);
    /*motor 2*/
    digitalWrite(pinBIN1, HIGH);
    digitalWrite(pinBIN2, LOW);
    analogWrite(pinPWMB, velocidad);
}

/*pertenece a motores.h*/
/*para mandar el sumo en reversa a cierta velocidad por defecto a 255*/
void motores_atras(int velocidad = 255)
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, HIGH);
    analogWrite(pinPWMA, velocidad);
    /*motor 2*/
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, HIGH);
    analogWrite(pinPWMB, velocidad);
}

/*pertenece a motores.h*/
/*permite que el robot gire sobre su eje asia la derecha a maxima velocidad por defecto*/
void motores_der_eje(int velocidad = 255)
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, HIGH);
    analogWrite(pinPWMA, velocidad);
    /*motor 2*/
    digitalWrite(pinBIN1, HIGH);
    digitalWrite(pinBIN2, LOW);
    analogWrite(pinPWMB, velocidad);
}

/*pertenece a motores.h*/
/*permite que el robot gire sobre su eje asia la izquierda a maxima velocidad por defecto*/
void motores_izq_eje(int velocidad = 255)
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, HIGH);
    digitalWrite(pinAIN2, LOW);
    analogWrite(pinPWMA, velocidad);
    /*motor 2*/
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, HIGH);
    analogWrite(pinPWMB, velocidad);
}

/*pertenece a motores.h*/
/*apaga los motores direccion y velocidad*/
void motores_off()
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, LOW);
    digitalWrite(pinAIN2, LOW);
    analogWrite(pinPWMA, LOW);
    /*motor 2*/
    digitalWrite(pinBIN1, LOW);
    digitalWrite(pinBIN2, LOW);
    analogWrite(pinPWMB, LOW);
}

/*pertenece a motores.h*/
/*ENTRAN LOS PW PARA CADA MOTOR Y SU RESPECTIVA DIRACCION*/
/*su orden es motor hacia delante, atras, y velocidad que tendra
y en ese mismo orden primero el derecho y despues el izquierdo*/
void motor_comtrolado(int AI1 = 1, int AI2 = 0, int PWA=255, int BI1 = 1, int BI2 = 0, int PWB=255)
{
  /* declaracion de pines de motor y susu valores iniciales*/
    /*motor 1*/
    digitalWrite(pinAIN1, AI1);
    digitalWrite(pinAIN2, AI2);
    analogWrite(pinPWMA, PWA);
    /*motor 2*/
    digitalWrite(pinBIN1, BI1);
    digitalWrite(pinBIN2, BI2);
    analogWrite(pinPWMB, PWB);
}

#endif