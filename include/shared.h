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
extern client_t **ar_clients;
extern int n_clients;
extern int n_tickets;
extern int bilheteria_aberta;

extern pthread_mutex_t gate_mutex;
extern ticket_t **ar_tickets;

extern pthread_mutex_t bilheteria_aberta_mutex;
extern pthread_mutex_t sinalizador_close_gate_mutex;


#endif