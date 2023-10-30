#ifndef declaraciones_h
#define declaraciones_h

/*Pines Motor*/
  /*motor 1*/
    extern const int pinAIN1;
    extern const int pinAIN2;
    extern const int pinPWMA;
  /*motor 2*/
    extern const int pinBIN1;
    extern const int pinBIN2;
    extern const int pinPWMB;
/* pines sensores S*/
  //1 no hay nada y 0 hay algo
  extern const int s1;
  //1 no hay nada y 0 hay algo
  extern const int s2;
  //1 no hay nada y 0 hay algo
  extern const int s3;
  //1 no hay nada y 0 hay algo
  extern const int s4;
  //1 no hay nada y 0 hay algo
  extern const int s5;
/* pines sensores SP*/
  //sp1 12
  //sp2 2
  extern QTRSensorsRC sp1;
  extern unsigned int SP1[1];
  extern QTRSensorsRC sp2;
  extern unsigned int SP2[1];

/* demas*/
  extern const int AUX;
  extern const int p1;

/* interruptores*/
  extern const int inter1;
  extern const int inter2;
  extern const int inter3;

void declaracion(){
    /* declaracion de pines de motor y susu valores iniciales*/
      /*motor 1*/
      pinMode(pinAIN2, OUTPUT);
      pinMode(pinAIN1, OUTPUT);
      pinMode(pinPWMA, OUTPUT);
      digitalWrite(pinAIN1, LOW);
      digitalWrite(pinAIN2, LOW);
      analogWrite(pinPWMA, LOW);
      /*motor 2*/
      pinMode(pinBIN1, OUTPUT);
      pinMode(pinBIN2, OUTPUT);
      pinMode(pinPWMB, OUTPUT);
      digitalWrite(pinBIN1, LOW);
      digitalWrite(pinBIN2, LOW);
      analogWrite(pinPWMB, LOW);
  
  /*declaracion de sensores*/
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    pinMode(s3, INPUT);
    pinMode(s4, INPUT);
    //pinMode(s5, INPUT);

  /*servo motor*/
    //bandera.attach(s5);

  /*declaracion de SP*/
    //pinMode(sp1, INPUT);
    //pinMode(sp2, INPUT);
    int Pinps1[] = {12}; // Ajusta el pin según tu configuración.
    sp1.init((unsigned char*)Pinps1, 2);
    int Pinps2[] = {2}; // Ajusta el pin según tu configuración.
    sp2.init((unsigned char*)Pinps2, 2);

  /*declaracion de demas*/
    pinMode(AUX, INPUT);
    pinMode(p1, INPUT);

  /*declaracion de interructores*/
    pinMode(inter1, INPUT);
    pinMode(inter2, INPUT);
    pinMode(inter3, INPUT);
}
#endif