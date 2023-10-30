/* preguntas:
1) como debe inicializar los sumos en el doyo?
2) tiempo de espera minimo para empesar a buscar mientras espera activacion de los sensores?
3) mejorar busqueda o poner mas casos y modos de busqueda?
*/

#include <QTRSensors.h>
#include <Servo.h>
#include "maquinaEstados.h"
#include "motores.h"
#include "sensores.h"
#include "movimientos.h"
#include "declaraciones.h"
#include "bandera_motor.h"


  Servo bandera;
  /*para saber el modo en el que se encuentra
  */
  int modo = 0;

/*Pines Motor*/
  /*motor 1*/
    const int pinAIN1 = 8;
    const int pinAIN2 = 7;
    const int pinPWMA = 6;
  /*motor 2*/
    const int pinBIN1 = 11;
    const int pinBIN2 = 10;
    const int pinPWMB = 5;

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
  const int inter1 = 4;
  const int inter2 = 3;
  const int inter3 = A7;

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

  //para saber el tiempo que se demora en evitar linea
  long tiempo = 0;
  //para saver cuanto tiempo tiene para hacer una accion
  long tiempo_accion = 0;
  //caunto lleva en la misma accion para cambiar estrateguia
  long tiempo_recurrencia;

  //long tiempo_bandera = 0;
  //tiempo que tiene para quedarse en la ultima accion hecha
  int demora = 0;

  //para saber si andar o no (1 si / 0 no)
  int remoto = 0;

  /*tipos de modos para esquibar un oponente*/
  /*0 => disminuye la velocidad en el motor en el cual sintio la presencia*/
  /*1 => para la velocidad en el motor en el cual sintio la presencia*/
  /*2 => giro sobre su eje hacia el lado donde halla detectado algo*/
  /*3 => si detecta algun lado qira hacia el otro a una velocidad constante*/
  /*4 => si detecta algun lado qira hacia el otro en su eye*/
  /*5 => si detecta algun lado para*/
  /*6 => si detecta algun lado adelante*/
  /*7 => si detecta algun lado atras*/
  int esquiva = 2;

  //guarada los valores digitales de los interruptores
  int mod1=0,mod2=0,mod3=0;

  char posicion_bandera = 1;

void setup()
{
  Serial.begin(9600);
  millis();
  declaracion();
  bandera.attach(13);
  // inicializar tiempos
    tiempo = millis();
    tiempo_recurrencia = 0;
    tiempo_accion = millis();
}

void loop()
{
  switch (sumo)
  {
    //para empesar el codigo con el control
    case encendido:
      barrido_sensores();
      control();
      modos();Serial.println(modo);
      tiempo = millis();
      tiempo_accion = millis();
    break;

//busqueda del sumo en la pista
    case busqueda:
      barrido_sensores();
      control();
      desicion();
    break;

//ataca cuando cualquiera de los dos sensores esten en 1
    case ataque: 
        tiempo_accion=millis();
        pelea();// tiene los modos de pelea
        asignar(busqueda);
    break;
    
//evade cuando cualquiera de los sensores de los lados esten en 1
    case evacion:
        tiempo_accion=millis();
        esquivar();
        asignar(busqueda);
    break;

//cuando cualquiera de los sensores de piso este en 1 se quita del camino y permanece medio segundo en esta accion
    case limite_pista:
        pista_limite();
    break;

//apaga los motores con señal del modulo de inicio en 0
    case apagado:
      motores_off();
      asignar(encendido);
    break;
    
  } 
}