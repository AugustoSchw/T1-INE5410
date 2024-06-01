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


// Thread que implementa uma bilheteria
void *sell(void *args){

    debug("[INFO] - Bilheteria Abriu!\n");

    // ticket_t * ticket = (ticket_t *) args;

    // client = dequeue(gate_queue);     <----ERRO
    // buy_coins(client);

    pthread_exit(NULL);
}

// Essa função recebe como argumento informações sobre a bilheteria e deve iniciar os atendentes.
void open_tickets(tickets_args *args){
    // Sua lógica aqui
    // ticket = (ticket_t *) malloc(args->n * sizeof(ticket_t));
    ticket = args -> tickets;
    pthread_t atendentes[args->n];
    for (int i = 0; i < args->n - 1; i++) {
        pthread_create(&atendentes[i], NULL, sell, (void *) args->tickets[i]);
    }

}

// Essa função deve finalizar a bilheteria
void close_tickets(){
    //Sua lógica aqui
    free(ticket);
    
}