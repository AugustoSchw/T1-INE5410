#include "shared.h"

#include <queue.h>


// Você pode declarar novas funções (ou variaveis compartilhadas) aqui


/**********************************
 *          ATENÇÃO               *
 *   NÃO EDITAR ESSAS VARIAVEIS   *
 *          ATENÇÃO               *
 *********************************/
Queue *gate_queue = NULL;

client_t **ar_clients; // Array de clientes

ticket_t **ar_tickets; // Array de funcionarios

int n_clients = 0; // Numero de clientes

int n_tickets = 0; // Numero de funcionarios

int sinalizador_close_gate; // Variavel para sinalizar o fechamento do portao

int bilheteria_aberta = 0;

pthread_mutex_t gate_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t bilheteria_aberta_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para alteração da variavel bilheteria_aberta

pthread_mutex_t sinalizador_close_gate_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para alteração da variavel sinalizador_close_gate

int tempo_espera_cliente = 1;

int tempo_exec_toy = 2;
