#include "shared.h"

#include <queue.h>


// Você pode declarar novas funções (ou variaveis compartilhadas) aqui


/**********************************
 *          ATENÇÃO               *
 *   NÃO EDITAR ESSAS VARIAVEIS   *
 *          ATENÇÃO               *
 *********************************/


// Variáveis para guardar o tamanho de cada array:

int n_clients = 0; // Numero de clientes

int n_tickets = 0; // Numero de funcionarios

int n_toys = 0;


// Variáveis para controle de tempo:

int tempo_espera_cliente = 1;

int tempo_exec_toy = 2;

int tempo_espera_toy = 2;


// Mutexes:

pthread_mutex_t gate_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t sinalizador_close_toy_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t bilheteria_aberta_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para alteração da variavel bilheteria_aberta

pthread_mutex_t sinalizador_close_gate_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para alteração da variavel sinalizador_close_gate

pthread_mutex_t toy_mutex;

// Ponteiros e ponteiros de ponteiros:

Queue *gate_queue = NULL;

client_t **ar_clients; // Array de clientes

ticket_t **ar_tickets; // Array de funcionarios

toy_t **ar_toys;   // Array de briquedos

// Variáveis usadas como parametro para que o while loop de alguma thread acabe:
int sinalizador_close_gate; // Variavel para sinalizar o fechamento do portao

int sinalizador_close_toy = 0;

int sinalizador_close_park = 0;

int bilheteria_aberta = 0;