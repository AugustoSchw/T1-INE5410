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
pthread_t *client_thread; // Threads do cliente


void queue_enter(client_t *self);  // Funcao onde o cliente entra na fila da bilheteria 

void wait_ticket(client_t *self);  // Funcao onde o cliente espera a liberacao da bilheteria para adentrar ao parque

// Thread que implementa o fluxo do cliente no parque.
void *enjoy(void *arg){
    client_t *cliente = (client_t *) arg;   // Cliente

    wait_ticket(arg);   // Espera a liberacao da bilheteria
    while (TRUE){
        debug("[ENTER] - O turista entrou no parque.\n"); 
        if (ar_clients[(cliente->id - 1)]->coins <= 0){  // Se o cliente nao tiver mais moedas, sai do parque
            break;
        }
        ar_clients[(cliente->id - 1)]->coins -= 1;   // Decrementa a quantidade de moedas do cliente por brinquedo usado
       int escolha_toy = rand() % cliente->number_toys; // Escolha aleatoria de brinquedos
        cliente->toys[escolha_toy]->current_capacity += 1;  // Incrementa a capacidade atual do brinquedo escolhido

        // Logica da escolha de brinquedos
    }

    debug("[EXIT] - O turista saiu do parque.\n");
    pthread_exit(NULL);
}

// Funcao onde o cliente compra as moedas para usar os brinquedos
void buy_coins(client_t *self){
    // Sua lógica aqui
    ar_clients[self->id - 1]->coins = rand() % MAX_COINS; // Cede um valor aleatório de moedas ao cliente
}

// Função onde o cliente espera a liberacao da bilheteria para adentrar ao parque.
void wait_ticket(client_t *self){
    // Sua lógica aqui
    while (!bilheteria_aberta){ // Enquanto a bilheteria não estiver aberta, o cliente espera
        debug(" Turista [%d] esperando a bilheteria abrir.\n", self->id);
        sleep(1);
    }
    queue_enter(self);   // Entra na fila da bilheteria
}

// Funcao onde o cliente entra na fila da bilheteria
void queue_enter(client_t *self){
    // Sua lógica aqui.
    debug("[WAITING] - Turista [%d] entrou na fila do portao principal\n", self->id);
    // Logica da fila
    if (self != NULL) { // Verificar se cliente não é um ponteiro nulo

    enqueue(gate_queue, (self->id));    // Entra na fila da bilheteria
    ar_clients[self->id - 1]->em_fila = 1;    // Adiciona o cliente ao array de clientes
    
    while ((ar_clients[self->id - 1]->em_fila) == 1){  // Enquanto o cliente estiver na fila, ele espera
       sleep(1);
    }
    debug("cu\n\n\ncu\n\n\n\n\ncu");
    
    debug("[CASH] - Turista [%d] comprou [%d] moedas.\n", self->id, self->coins);
    }
}

// Essa função recebe como argumento informações sobre o cliente e deve iniciar os clientes.
void open_gate(client_args *args){
    ar_clients = args->clients; // Array de clientes
    n_clients = args->n; // Numero de clientes
    pthread_t *client_thread = (pthread_t *) malloc(n_clients * sizeof(pthread_t)); // Aloca memoria para a thread do cliente
    for (int i = 0; i < n_clients; i++) { // Inicializa os clientes
        pthread_create(&client_thread[i], NULL, enjoy, (void *) ar_clients[i]); // Cria a thread do cliente
    }
}

// Essa função deve finalizar os clientes
void close_gate(){
   //Sua lógica aqui
    sleep(1); 
    
    for (int i = 0; i < n_clients; i++) { // Finaliza os clientes
        pthread_join(client_thread[i], NULL); // Finaliza a thread do cliente
    }

    free(gate_queue);   // Desaloca a memoria da fila
    pthread_exit(NULL);
    
    // Sua lógica aqui
    

}