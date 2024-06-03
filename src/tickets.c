/**
 * Esse arquivo tem como objetivo a implementação da bilheteria em um parque.
 * Você pode criar novas funções dentro desse arquivo caso julgue necessário.
 * ATENÇÃO: NÃO APAGUE OU EDITE O NOME OU O(S) ARGUMENTO(S) DAS FUNÇÕES FORNECIDAS.
*/
#include <stdio.h>
#include <stdlib.h>
#include <tickets.h>
#include <unistd.h>
#include <client.h>

#include <queue.h>
#include "shared.h"

ticket_t **ticket;
client_t **client;
//pthread_t **atendentes;
pthread_t *atendentes;
// Thread que implementa uma bilheteria
void *sell(void *args){
    ticket_t *atendente = (ticket_t *) args;

    debug("[INFO] - Bilheteria Abriu!\n");
    sleep(1);
    while (TRUE) {
        if (!is_queue_empty(gate_queue)) {
            int cliente_fila = dequeue(gate_queue);
            
            printf("----------%d", cliente_fila);
            debug("Cliente [%d] atendido pelo funcionário [%d]\n", ar_clients[cliente_fila]->id, ticket->id);
            buy_coins(ar_clients[cliente_fila]);
            ar_clients[cliente_fila]->em_fila = 0;
        }
        
        // pthread_mutex_lock(&gate_mutex);
        
        // pthread_mutex_unlock(&gate_mutex);
    }

    pthread_exit(NULL);
}

// Essa função recebe como argumento informações sobre a bilheteria e deve iniciar os atendentes.
void open_tickets(tickets_args *args){
    // Sua lógica aqui
    // ticket = (ticket_t *) malloc(args->n * sizeof(ticket_t));
    ar_tickets = args -> tickets;
    n_tickets = args -> n;
    pthread_t *atendentes = (pthread_t *) malloc(n_tickets * sizeof(pthread_t));
    //pthread_t *atendentes = (pthread_t *) malloc(args->n * sizeof(pthread_t));
    for (int i = 0; i < args->n; i++) {
        pthread_create(&atendentes[i], NULL, sell, (void *) args->tickets[i]);
    }
    pthread_mutex_lock(&bilheteria_aberta_mutex);
    bilheteria_aberta = 1;
    pthread_mutex_unlock(&bilheteria_aberta_mutex);
}

// Essa função deve finalizar a bilheteria
void close_tickets(){
    pthread_mutex_lock(&bilheteria_aberta_mutex);
    bilheteria_aberta = 0;
    pthread_mutex_unlock(&bilheteria_aberta_mutex);
    for (int i = 0; i < n_tickets; i++) {
        pthread_join(atendentes[i], NULL);
    }
    //Sua lógica aqui
    //free(ticket);
    
}