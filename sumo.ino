#include <QTRSensors.h>

/*Pines Motor*/
  /*motor 1*/
    const int pinAIN1 = 10;
    const int pinAIN2 = 11;
    const int pinPWMA = 5;
  /*motor 2*/
    const int pinBIN1 = 7;
    const int pinBIN2 = 8;
    const int pinPWMB = 6;

/* pines sensores S*/
  //1 no hay nada y 0 hay algo
  const int s1 = A0;
  //1 no hay nada y 0 hay algo
  const int s2 = A3;
  //1 no hay nada y 0 hay algo
  const int s3 = A4;
  //1 no hay nada y 0 hay algo
  const int s4 = A2;
  //1 no hay nada y 0 hay algo
  const int s5 = 13;

/* pines sensores SP*/
  //sp1 12
  //sp2 2
  QTRSensorsRC sp1;
  unsigned int SP1[1];
  QTRSensorsRC sp2;
  unsigned int SP2[1];

/* demas*/
  const int AUX = 9;
  const int p1 = A1;

/* interruptores*/
  const int modo1 = 4;
  const int modo2 = 3;
  const int modo3 = A7;

/*Maquina de estados*/
  /*estructura*/
    enum ESTsumo{
      encendido,
      busqueda,
      ataque,
      evacion,
      limite_pista,
      apagado
    };

    /*variable del estado*/
    ESTsumo sumo;

    /*funcion para asignar un nuevo estado para la maquina de estados*/
    void asignar(ESTsumo eleccion) {
    sumo = eleccion;
    }

/*VARIABLES*/
  /*lee los sensores y los guarda en el arreglo global sensores:*/
  /*->sensores alrededor 1 no detecta y 0 detecta*/
  /*--->[0] lado derecho*/
  /*--->[1] frente derecho*/
  /*--->[2]frente izquierdo*/
  /*--->[3] lado izquierdo*/
  /*->sensores piso: blanco(0<100 masomenos) < negro(1000<2500 masomenos)*/
  /*--->[4] piso derecho*/
  /*--->[5] piso izquierdo*/
  unsigned int sensores[] = {0,0,0,0,0,0};

  /*me sirve para saber el valor que tiene entre negro y blanco*/
  int linea = 500;

  //para saber el tiempo de inicio
  long tiempo = 0;

  /*para saber el modo en el que se encuentra
  */
  int modo = 0;

  //para saber si andar o no (1 si / 0 no)
  int remoto = 0;
void setup()
{
  Serial.begin(9600);
  millis();
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
    pinMode(s5, INPUT);

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
    pinMode(modo1, INPUT);
    pinMode(modo2, INPUT);
    pinMode(modo3, INPUT);

  // inicializar tiempo
    tiempo = millis();
}

/*FUNCIONES*/
  void motores_delante(int velocidad = 255);
  void motores_atras(int velocidad = 255);
  void motores_der_eje(int velocidad = 255);
  void motores_izq_eje(int velocidad = 255);
  void motores_off();
  void motor_comtrolado(int AI1 = 1, int AI2 = 0, int PWA=255, int BI1 = 1, int BI2 = 0, int PWB=255);
  void barrido_sensores();
  void modos();
  void buscando();
  void control();
  void pelea();
  void esquivar();
  void pista_limite();

void loop()
{
  switch (sumo)
  {
    //para empesar el codigo con el control
    case encendido:
      barrido_sensores();
      control();
    break;

    case busqueda:
      barrido_sensores();
      control();
      //si los sensores de piso estan en la sona limite del doyo
      if((sensores[4] < linea) || (sensores[5] < linea))
      {
        asignar(limite_pista);
        break;
      }
      //para mandar a atacar si detecta algo alfrente
      else if((sensores[2] == 0) || (sensores[1] == 0))
      {
        asignar(ataque);
        break;
      }
      //si detecta algo a los costados
      else if((sensores[0] == 0) || (sensores[3] == 0))
      {
        asignar(evacion);
        break;
      }
      //movimiento en el doyon para bvuscar enemigo;
      else
      {
      buscando();//terminar funcionde buscar
      }
    break;
    case ataque: 
        pelea();// tiene los modos de pelea
        asignar(busqueda);
    break;
    case evacion:
        esquivar();
        asignar(busqueda);
    break;
    case limite_pista:
        pista_limite();
    break;
    case apagado:
      motores_off();
      asignar(encendido);
    break;
  } 
}

void esquivar()
{
  if(sensores[0]==0)
  {
    motor_comtrolado(1, 0, 30, 1, 0, 255);
  }
  else if(sensores[3]==0)
  {
    motor_comtrolado(1, 0, 255, 1, 0, 30);
  }
}

void pelea()
{
  //modos();
  switch (modo)
  {
    
  case 0://choca con ambos sensores en 1
    if((sensores[1] == 0) && (sensores[2] == 0))
    {
      motores_delante(255);
      break;
    }
    else if(sensores[1] == 0)
    {
      motor_comtrolado( 1, 0, 200,  1, 0, 255);
      break;
    }
    else if(sensores[2] == 0)
    {
      motor_comtrolado( 1, 0, 255,  1, 0, 200);
      break;
    }
  break;

  case 1://choca con ambos sensores en 1
    if((sensores[1] == 0) && (sensores[2] == 0))
    {
      motor_comtrolado( 1, 0, 200,  1, 0, 255);
      break;
    }
    else if(sensores[1] == 0)
    {
      motores_delante(255);
      break;
    }
    else if(sensores[2] == 0)
    {
      motores_delante(255);
      break;
    }
  break;
  case 2:

  break;
  /*case 3:

  break;*/
  }
}

/*me asigna dependiendo de si esta el remoto en 1 o 0*/
/* 0 apagado*/
/* 1 busqueda*/
void control()
{
  switch(remoto)
  {
    case 0:
      asignar(apagado);
    break;
    case 1:
      asignar(busqueda);
    break;
  } 

}

void pista_limite()
{
  
  tiempo = millis();
  while((millis()-tiempo) < 500)
  { 
    if((0 < sensores[4] < linea) && (linea < sensores[5]))
    {
      motor_comtrolado(0,1,255,0,1,100);
      remoto = digitalRead(p1);
      control();
    }
    else if((linea < sensores[4]) && (0 < sensores[5] < linea))
    {
      motor_comtrolado(0,1,100,0,1,255);
      remoto = digitalRead(p1);
      control();
    } 
    else if((0 < sensores[4] < linea) && (0 < sensores[5] < linea))
    {
      motor_comtrolado(0,1,255,0,1,50);
      remoto = digitalRead(p1);
      control();
    }

    barrido_sensores();
    control();    
  }
  tiempo = millis();
  asignar(busqueda);
}

void buscando()
{
  if((millis()-tiempo) > 5000)
  {
    tiempo = millis();
  }
  if((millis()-tiempo) < 3000)
  {
    motores_delante(150);
  }
  else if((millis()-tiempo) < 5000)
  {
    motores_izq_eje(100);
  }
}

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

/*permite que el robot gire sobre su eje asia la derecha*/
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

/*permite que el robot gire sobre su eje asia la izquierda*/
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

/*apaga los motores para parar*/
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

/*ENTRAN LOS PW PARA CADA MOTOR Y SU RESPECTIVA DIRACCION*/
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

/*lee los sensores y los guarda en el arreglo global sensores:
[0] lado derecho
[1] frente derecho
[2] frente izquierdo
[3] lado izquierdo
[4] piso derecho
[5] piso izquierdo
*/
void barrido_sensores()
{
  sp1.read(SP1);
  sensores[4] = SP1[0];

  sp2.read(SP2);
  sensores[5] = SP2[0];

  sensores[0] = digitalRead(s5);
  sensores[1] = digitalRead(s2);
  sensores[2] = digitalRead(s3);
  sensores[3] = digitalRead(s4);
  remoto = digitalRead(p1);
}

void modos()
{
  if(digitalRead(modo1) == 0)
  {
    modo = 1;
  }
  else if(digitalRead(modo2) == 0)
  {
    modo = 2;
  }
  else if(digitalRead(modo3) == 0)
  {
    modo = 3;
  }
  else 
  {
    modo = 0;
  }
}
