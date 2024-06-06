#include "shared.h"

#include <queue.h>


// Você pode declarar novas funções (ou variaveis compartilhadas) aqui


/**********************************
 *          ATENÇÃO               *
 *   NÃO EDITAR ESSAS VARIAVEIS   *
 *          ATENÇÃO               *
 *********************************/


// Variáveis para guardar o tamanho de cada array:

int n_clients = 0;  // Numero de clientes

int n_tickets = 0;  // Numero de funcionarios

int n_toys = 0;     // Numero de brinquedos


// Variáveis para controle de tempo:

int tempo_espera_cliente = 2;   // Tempo de espera pela abertura da bilheteria

int tempo_exec_toy = 2;         // Tempo de execução do brinquedo

int tempo_espera_toy = 1;       // Tempo de espera para os clientes entrarem no brinquedo

int tempo_ate_toy = 3;

// Mutexes:

pthread_mutex_t gate_mutex = PTHREAD_MUTEX_INITIALIZER;                     // Mutex para proteger as filas quando as funções enqueue e dequeue são executadas

pthread_mutex_t sinalizador_close_toy_mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para alteração da variavel sinalizador_close_toy

pthread_mutex_t bilheteria_aberta_mutex = PTHREAD_MUTEX_INITIALIZER;        // Mutex para alteração da variavel bilheteria_aberta

pthread_mutex_t sinalizador_close_gate_mutex = PTHREAD_MUTEX_INITIALIZER;   // Mutex para alteração da variavel sinalizador_close_gate

// Semáforos:

//sem_t semaforo_toys;            // Semáforo utilizado para informar todos os passageiros que o brinquedo foi finalizado

// sem_t semaforo_clients;

// Ponteiros e ponteiros de ponteiros:

Queue *gate_queue = NULL;       // Fila de clientes 

client_t **ar_clients;          // Array de clientes

ticket_t **ar_tickets;          // Array de funcionarios

toy_t **ar_toys;                // Array de briquedos

// Variáveis usadas como parametro para que o while loop de alguma thread acabe:

int sinalizador_close_gate;     // Variavel para sinalizar quando fechar o portao

int sinalizador_close_toy = 0;  // Variavel para sinalizar quando fechar os brinquedos

int sinalizador_close_park = 0; // Variavel para sinalizar quando fechar o parque

int bilheteria_aberta = 0;      // Variavel para sinalizar quando fehcar a bilheteria