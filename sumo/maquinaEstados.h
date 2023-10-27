#ifndef maquinaEstados_h
#define maquinaEstados_h
/*Maquina de estados*/
  /*estructura*/
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

  /*pertenece a maquinaEstados.h*/
  /*funcion para asignar un nuevo estado para la maquina de estados*/
    void asignar(ESTsumo eleccion) {
    sumo = eleccion;
    }
#endif