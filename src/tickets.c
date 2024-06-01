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
pthread_mutex_t *mutex;

// Thread que implementa uma bilheteria
void *sell(void *args){
    //ticket_t *ticket = (ticket_t *) args;
    debug("[INFO] - Bilheteria Abriu!\n");
    sleep(2);
    while (TRUE){
        // Sua lógica aqui
        // Logica da bilheteria
        int id_cliente;
        id_cliente = dequeue(gate_queue);
        client_t *cliente = &ar_clients[id_cliente];
        //pthread_mutex_lock(&mutex[ticket->id]);
        buy_coins(cliente);
        //debug("[CASH] - Turista [%d] comprou [%d] moedas.\n", id_cliente, cliente->coins);
        //pthread_mutex_unlock(&mutex[ticket->id]);
        if (is_queue_empty(gate_queue)){
            continue;
        }


    }

    // ticket_t * ticket = (ticket_t *) args;

    // client = dequeue(gate_queue);     <----ERRO
    // buy_coins(client);

    pthread_exit(NULL);
}

// Essa função recebe como argumento informações sobre a bilheteria e deve iniciar os atendentes.
void open_tickets(tickets_args *args){
    gate_queue = create_queue(); // Inicia a fila
    // Sua lógica aqui
    // ticket = (ticket_t *) malloc(args->n * sizeof(ticket_t));
    mutex = (pthread_mutex_t *) malloc(args->n * sizeof(pthread_mutex_t));
    for (int i = 0; i < args->n; i++){
        pthread_mutex_init(&mutex[i], NULL);
    }
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