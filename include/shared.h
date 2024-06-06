#ifndef __SHARED_H__
#define __SHARED_H__

#include <defs.h>

// Você pode declarar novas funções (ou variaveis compartilhadas) aqui



/**********************************
 *          ATENÇÃO               *
 *   NÃO EDITAR ESSAS VARIAVEIS   *
 *          ATENÇÃO               *
 *********************************/
extern Queue *gate_queue;
extern int sinalizador_close_gate;
extern int n_clients;
extern int n_tickets;
extern int n_toys;
extern int bilheteria_aberta;
extern int tempo_espera_toy;
extern int sinalizador_close_toy;
extern int sinalizador_close_park;

extern ticket_t **ar_tickets;
extern client_t **ar_clients;
extern toy_t **ar_toys;

extern pthread_mutex_t gate_mutex;
extern pthread_mutex_t bilheteria_aberta_mutex;
extern pthread_mutex_t sinalizador_close_gate_mutex;
extern pthread_mutex_t sinalizador_close_toy_mutex;

//extern sem_t semaforo_toys;
//extern sem_t semaforo_clients;

extern int tempo_espera_cliente;
extern int tempo_exec_toy;


#endif