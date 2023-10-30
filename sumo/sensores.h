#ifndef sensores_h
#define sensores_h

#include "maquinaEstados.h"
/* pines sensores SP*/
//sp1 12
//sp2 2
extern QTRSensorsRC sp1;
extern unsigned int SP1[1];
extern QTRSensorsRC sp2;
extern unsigned int SP2[1];

extern const int p1;

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

/*lee los sensores y los guarda en el arreglo global sensores:*/
/*->sensores alrededor 1 no detecta y 0 detecta*/
/*--->[0] lado derecho*/
/*--->[1] frente derecho*/
/*--->[2]frente izquierdo*/
/*--->[3] lado izquierdo*/
/*->sensores piso: blanco(0<100 masomenos) < negro(1000<2500 masomenos)*/
/*--->[4] piso derecho*/
/*--->[5] piso izquierdo*/
extern unsigned int sensores[];

//para saber si andar o no (1 si / 0 no)
extern int remoto;

/*para saber el modo en el que se encuentra
  */
extern int modo;
/* interruptores*/
extern const int inter1, inter2, inter3;
//guarada los valores digitales de los interruptores
extern int mod1, mod2, mod3;


/*pertenece a sensores.h*/
/*me asigna dependiendo de si esta el remoto en 1 o 0*/
/* 0 apagado*/
/* 1 busqueda*/
void control() {
  switch (remoto) {
    case 0:
      asignar(apagado);
      break;
    case 1:
      asignar(busqueda);
      break;
  }
}

/*pertenece a sensores.h*/
/*lee y guarda los valores que tengan los sensores en ese momento*/
void barrido_sensores() {
  sp1.read(SP1);
  sensores[4] = SP1[0];

  sp2.read(SP2);
  sensores[5] = SP2[0];

  sensores[0] = digitalRead(s4);
  sensores[1] = digitalRead(s2);
  sensores[2] = digitalRead(s1);
  sensores[3] = digitalRead(s3);
  remoto = digitalRead(p1);
}

/*pertenece a sensores.h*/
/*asigna el valor decimal de los interruptores que se encuentren seleccionados*/
void modos() {
  mod1 = digitalRead(inter1);
  mod2 = digitalRead(inter2);
  if (analogRead(inter3) == 0) {
    mod3 = 0;
  } else {
    mod3 = 1;
  }
  modo = ((mod3 * 1) + (mod2 * 2) + (mod1 * 4));
}

#endif