#ifndef movimientos_h
#define movimientos_h

  #include "maquinaEstados.h"
  #include "bandera_motor.h"

  /*para saber el modo en el que se encuentra
  */
  extern int modo;

  /*tipos de modos para esquibar un oponente*/
    /*0 => disminuye la velocidad en el motor en el cual sintio la presencia*/
    /*1 => para la velocidad en el motor en el cual sintio la presencia*/
    /*2 => giro sobre su eje hacia el lado donde halla detectado algo*/
    /*3 => si detecta algun lado qira hacia el otro a una velocidad constante*/
    /*4 => si detecta algun lado qira hacia el otro en su eye*/
    /*5 => si detecta algun lado para*/
    /*6 => si detecta algun lado adelante*/
    /*7 => si detecta algun lado atras*/
  extern int esquiva;

  /*me sirve para saber el valor que tiene entre negro y blanco*/
  extern int linea;

  //para saber el tiempo que se demora en evitar linea
  extern long tiempo;
  //para saver cuanto tiempo tiene para hacer una accion
  extern long tiempo_accion;
  //caunto lleva en la misma accion para cambiar estrateguia
  extern long tiempo_recurrencia;
  //tiempo que tiene para quedarse en la ultima accion hecha
  extern int demora;

  /*pertenece a movimientos.h*/
/*metodo de busqueda y movimiento que tiene*/
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

void desicion()
{
  //si los sensores de piso estan en la sona limite del doyo
  if((sensores[4] < linea) || (sensores[5] < linea))
  {
    demora=1000;
    esquiva = 2;
    tiempo_recurrencia = 0;
    asignar(limite_pista);
  }
  //para mandar a atacar si detecta algo alfrente
  else if((sensores[2] == 0) || (sensores[1] == 0))
  {
    tiempo_recurrencia = 0;
    esquiva = 2;
    demora = 1000;
    tiempo_accion = millis();
    asignar(ataque);
  }
  //si detecta algo a los costados
  else if((sensores[0] == 0) || (sensores[3] == 0))
  {
    demora=1000;
    tiempo_accion = millis();
    //evita estar actualizando todo el tiempo
    if(tiempo_recurrencia==0){tiempo_recurrencia = millis(); esquiva = 2;}
    asignar(evacion);
  }
  //movimiento en el doyon para bvuscar enemigo y espera de un segundo en caso de aber detectado algo;
  else if((millis() - tiempo_accion) > demora)
  {
    demora=1000;
    buscando();//terminar funcionde buscar
  }
}

/*pertenece a movimientos.h*/
/*funcion para como va a reaccionar al sumo contricante por los lados*/
/*tipos de modos para esquibar al oponente*/
/*0 => disminuye la velocidad en el motor en el cual sintio la presencia*/
/*1 => para la velocidad en el motor en el cual sintio la presencia*/
/*2 => giro sobre su eje hacia el lado donde halla detectado algo*/
/*3 => si detecta algun lado qira hacia el otro a una velocidad constante*/
/*4 => si detecta algun lado qira hacia el otro en su eye*/
/*5 => si detecta algun lado para*/
/*6 => si detecta algun lado adelante*/
/*7 => si detecta algun lado atras*/
void esquivar()
{
  switch(modo)
  {
    case 0:
      if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;
    case 1:
      if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;
    case 2:
    if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    modo = 0;
    break;
    case 3:
    if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;

    case 4:
      if(sensores[0]==0)
      {
        bandera_der();
      }
      else if(sensores[3]==0)
      {
        bandera_izq();
      }
    break;

    case 5:
    if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;
    case 6:
    if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;
    case 7:
    if((millis() - tiempo_recurrencia) > 1500)
      {
        switch(esquiva)
        {
          case 2:
            esquiva = 6;
          break;

          case 6:
            esquiva = 7;
          break;
          
          case 7:
            esquiva = 2;
          break;
        }
        tiempo_recurrencia = millis();
      }
    break;
  }
  

  switch(esquiva)
  {
    case 0:
      if(sensores[0]==0)
      {
        motor_comtrolado(1, 0, 50, 1, 0, 255);
      }
      else if(sensores[3]==0)
      {
        motor_comtrolado(1, 0, 255, 1, 0, 50);
      }
    break;

    case 1:
      //para la velocidad en un motor para quedar defrente 
      if(sensores[0]==0)
      {
        motor_comtrolado(0, 0, 0, 1, 0, 255);
      }
      else if(sensores[3]==0)
      {
        motor_comtrolado(1, 0, 255, 0, 0, 0);
      }
    break;

    case 2:
      if(sensores[0]==0)
      {
        motor_comtrolado(0, 1, 255, 1, 0, 255);
      }
      else if(sensores[3]==0)
      {
        motor_comtrolado(1, 0, 255, 0, 1, 255);
      }
    break;

    case 3:
      if(sensores[0]==0)
      {
        motor_comtrolado(1, 0, 255, 0, 1, 50);
      }
      else if(sensores[3]==0)
      {
        motor_comtrolado(0, 1, 50, 1, 0, 255);
      }
    break;

    case 4:
      //para la velocidad en un motor para quedar defrente 
      if(sensores[0]==0)
      {
        motor_comtrolado(1, 0, 255, 0, 1, 255);
      }
      else if(sensores[3]==0)
      {
        motor_comtrolado(0, 1, 255, 1, 0, 255);
      }
    break;

    case 5:
      motores_off();
    break;

    case 6:
      motores_delante(150);
    break;

    case 7:
      motores_atras(150);
    break;
  }
}

/*pertenece a movimientos.h*/
/*tipos de pelea dependiendo de que caso se tenga, es cambiable desde la variable modo*/
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
      motor_comtrolado( 1, 0, 50,  1, 0, 255);
      break;
    }
    else if(sensores[2] == 0)
    {
      motor_comtrolado( 1, 0, 255,  1, 0, 50);
      break;
    }
  break;

  case 1://choca con ambos sensores en 1
    if((sensores[1] == 0) && (sensores[2] == 0))
    {
      motor_comtrolado( 1, 0, 50,  1, 0, 255);
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
    if((sensores[1] == 0) && (sensores[2] == 0))
    {
      motor_comtrolado( 1, 0, 50,  1, 0, 255);
      break;
    }
    else if(sensores[1] == 0)
    {
      motor_comtrolado( 1, 0, 255,  1, 0, 100);
      break;
    }
    else if(sensores[2] == 0)
    {
      motor_comtrolado( 1, 0, 100,  1, 0, 255);
      break;
    }
    else 
    {
      motores_delante(150);
    }
    if((millis() - tiempo_accion) > demora)
    {
      modo = 0;
    }
  break;

  case 3:
    modo=0;
  break;

  case 4:
    motores_off();
  break;

  case 5:
    modo=0;
  break;

  case 6:
    modo=0;
  break;

  case 7:
    modo=0;
  break;
  }
}

/*pertenece a movimientos.h*/
/*movimientos del sumo cuando detecta limite de pista*/
void pista_limite()
{
  tiempo = millis();
  while((millis()-tiempo) < 500)
  { 
    remoto = digitalRead(p1);
    control();
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
}
#endif