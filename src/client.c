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
    debug("[ENTER] - O turista entrou no parque.\n"); 
    while (TRUE){
        if (ar_clients[(cliente->id - 1)]->coins <= 0) {  // Se o cliente nao tiver mais moedas, sai do parque
            break;
        }
        sleep(1); 
        ar_clients[(cliente->id - 1)]->coins -= 1;   // Decrementa a quantidade de moedas do cliente por brinquedo usado
        sleep(tempo_ate_toy);
        debug("[INFO] O turista [%d] gastou uma moeda e está com [%d] moedas.\n", cliente->id, cliente->coins);
        int escolha_toy = rand() % cliente->number_toys; // Escolha aleatoria de brinquedos
        //pthread_mutex_lock(&ar_toys[escolha_toy]->mutex);
        if(ar_toys[escolha_toy]->current_capacity >= ar_toys[escolha_toy]->capacity) {
            ar_clients[(cliente->id - 1)]-> coins += 1;
            //pthread_mutex_unlock(&ar_toys[escolha_toy]->mutex);
            debug("[INFO] O turista [%d] tentou entrar no brinquedo [%d] mas ja estava lotado!\n", cliente -> id, cliente->toys[escolha_toy]->id);
            continue;
        }
        
        debug("[INFO] O turista [%d] está no brinquedo [%d]\n", cliente -> id, cliente->toys[escolha_toy]->id);
        pthread_mutex_lock(&ar_toys[escolha_toy]->mutex);
        ar_toys[escolha_toy]->current_capacity += 1;  // Incrementa a capacidade atual do brinquedo escolhido
        pthread_mutex_unlock(&ar_toys[escolha_toy]->mutex);
        sem_wait(&ar_toys[escolha_toy]->semaforo_toys);
        //sem_post(&semaforo_clients);
        
    }

    debug("[EXIT] - O turista saiu do parque.\n");
    pthread_exit(NULL);
}

// Funcao onde o cliente compra as moedas para usar os brinquedos
void buy_coins(client_t *self){
    // Sua lógica aqui
    //ar_clients[self->id - 1]->coins = (rand() % MAX_COINS) + 1; // Cede um valor aleatório de moedas ao cliente
    ar_clients[self->id - 1]->coins = 2;
}

// Função onde o cliente espera a liberacao da bilheteria para adentrar ao parque.
void wait_ticket(client_t *self){
    // Sua lógica aqui
    while (!bilheteria_aberta){ // Enquanto a bilheteria não estiver aberta, o cliente espera
        debug(" Turista [%d] esperando a bilheteria abrir.\n", self->id);
        sleep(tempo_espera_cliente);
    }
    queue_enter(self);   // Entra na fila da bilheteria
}

// Funcao onde o cliente entra na fila da bilheteria
void queue_enter(client_t *self){
    // Sua lógica aqui.

    debug("[WAITING] - Turista [%d] entrou na fila do portao principal\n", self->id);
    // Logica da fila

    pthread_mutex_lock(&gate_mutex);
    enqueue(gate_queue, (self->id - 1));    // Entra na fila da bilheteria
    pthread_mutex_unlock(&gate_mutex);

    ar_clients[self->id - 1]->em_fila = 1;    // Adiciona o cliente ao array de clientes
    
    while ((ar_clients[self->id - 1]->em_fila) == 1){  // Enquanto o cliente estiver na fila, ele espera
       sleep(1);
    }

    debug("[CASH] - Turista [%d] comprou [%d] moedas.\n", self->id, self->coins);
}

// Essa função recebe como argumento informações sobre o cliente e deve iniciar os clientes.
void open_gate(client_args *args){
    pthread_mutex_lock(&sinalizador_close_gate_mutex);
    sinalizador_close_gate = 0;
    pthread_mutex_unlock(&sinalizador_close_gate_mutex);
    n_clients = args->n; // Numero de clientes
    ar_clients = (client_t **) malloc(args->n * sizeof(client_t)); // Array de toys
    client_thread = (pthread_t *) malloc(n_clients * sizeof(pthread_t)); // Aloca memoria para a thread do cliente
    for (int i = 0; i < n_clients; i++) { // Inicializa os clientes
        ar_clients[i] = args->clients[i]; // Insere os argumentos no array de clientes
        pthread_create(&client_thread[i], NULL, enjoy, (void *) ar_clients[i]); // Cria a thread do cliente
        
    }
}

// Essa função deve finalizar os clientes
void close_gate(){
   //Sua lógica aqui
    for (int i = 0; i < n_clients; i++) { // Finaliza os clientes
        pthread_join(client_thread[i], NULL); // Finaliza a thread do cliente
    }
    ar_clients = NULL;
    pthread_mutex_lock(&sinalizador_close_gate_mutex);
    sinalizador_close_gate = 1;
    pthread_mutex_unlock(&sinalizador_close_gate_mutex);

    pthread_mutex_lock(&sinalizador_close_toy_mutex);
    sinalizador_close_toy = 1;
    pthread_mutex_unlock(&sinalizador_close_toy_mutex);

    //free(gate_queue);   // Desaloca a memoria da fila
    //pthread_exit(NULL);
    
    // Sua lógica aqui
    

}