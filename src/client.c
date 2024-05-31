/**
 * Esse arquivo tem como objetivo a implementação do cliente em um parque.
 * Você pode criar novas funções dentro desse arquivo caso julgue necessário.
 * ATENÇÃO: NÃO APAGUE OU EDITE O NOME OU O(S) ARGUMENTO(S) DAS FUNÇÕES FORNECIDAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defs.h"
#include "client.h"
#include "queue.h"
#include "shared.h"
pthread_t dispatcher;
void queue_enter(client_t *self);
// Thread que implementa o fluxo do cliente no parque.
void *enjoy(void *arg){
    client_t *cliente = (client_t *) arg;

    queue_enter(cliente);
    debug("[ENTER] - O turista entrou no parque.\n");
    while (TRUE){
        if (cliente->coins == 0){
            break;
        }
        cliente->coins -= 1;
        //int escolha_toy = rand() % cliente->number_toys;
        //cliente->toys[escolha_toy]->capacity -= 1;

        // Logica da escolha de brinquedos
    }

    debug("[EXIT] - O turista saiu do parque.\n");
    pthread_exit(NULL);
}

// Funcao onde o cliente compra as moedas para usar os brinquedos
void buy_coins(client_t *self){
    // Sua lógica aqui
    self->coins = rand() % MAX_COINS;
}

// Função onde o cliente espera a liberacao da bilheteria para adentrar ao parque.
void wait_ticket(client_t *self){
    // Sua lógica aqui
    // Logica da fila
}

// Funcao onde o cliente entra na fila da bilheteria
void queue_enter(client_t *self){
    // Sua lógica aqui.
    debug("[WAITING] - Turista [%d] entrou na fila do portao principal\n", self->id);
    // Logica da fila
    wait_ticket(self);
    // Logica da fila

    // Sua lógica aqui.
    buy_coins(self);    // Cede um valor aleatório de moedas ao cliente.

    // Sua lógica aqui.
    debug("[CASH] - Turista [%d] comprou [%d] moedas.\n", self->id, self->coins);
}

// Essa função recebe como argumento informações sobre o cliente e deve iniciar os clientes.
void open_gate(client_args *args){
    client_t *ar_clients = (client_t *) malloc(args->n * sizeof(client_t));
    int num_clients = args->n;
    for (int i = 0; i < num_clients; i++) {
        pthread_t thread_client;
        pthread_create(&thread_client, NULL, enjoy, (void *) &ar_clients[i]);
    }
}

// Essa função deve finalizar os clientes
void close_gate(){
   //Sua lógica aqui
    sleep(1);
    pthread_join(dispatcher, NULL);
    free(gate_queue);
    pthread_exit(NULL);
    
    // Sua lógica aqui
    

}
