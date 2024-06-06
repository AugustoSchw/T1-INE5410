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
    while (TRUE) {
        if (!sinalizador_close_gate) {
            pthread_mutex_lock(&gate_mutex); // Garante que apenas um atendente atenda um cliente por vez
            if (!is_queue_empty(gate_queue)) { // Se a fila não estiver vazia
                int cliente_fila = dequeue(gate_queue); // Pega o cliente que está na frente da fila
                pthread_mutex_unlock(&gate_mutex); // Libera o mutex para que outros atendentes possam atender outros clientes
                debug("Cliente [%d] atendido pelo funcionário [%d]\n", ar_clients[cliente_fila]->id, atendente->id); 
                buy_coins(ar_clients[cliente_fila]); // Função que executa a compra de moedas
                ar_clients[cliente_fila]->em_fila = 0; // Cliente não está mais na fila, pode entrar no parque
                sem_post(&ar_clients[cliente_fila]->semaforo); // Libera o cliente para entrar no parque
            } else {
                pthread_mutex_unlock(&gate_mutex); // Se a fila estiver vazia, libera o mutex
                sleep(1);
                continue;
            }
        } else {
            pthread_mutex_unlock(&gate_mutex); // Se o parque estiver fechando, libera o mutex
            break;
        }
    }

    pthread_exit(NULL);
}

// Essa função recebe como argumento informações sobre a bilheteria e deve iniciar os atendentes.
void open_tickets(tickets_args *args){
    // Sua lógica aqui
    ar_tickets = args -> tickets;
    n_tickets = args -> n;
    atendentes = (pthread_t *) malloc(args->n * sizeof(pthread_t));
    for (int i = 0; i < args->n; i++) {
        pthread_create(&atendentes[i], NULL, sell, (void *) args->tickets[i]);
    }
    for (int i = 0; i < n_clients; i++) {
        sem_post(&ar_clients[i]->semaforo_antes_fila); // Libera os clientes para entrar na fila
    }
    pthread_mutex_lock(&bilheteria_aberta_mutex); // Garante atomicidade da variável global com o mutex
    bilheteria_aberta = 1; // Bilheteria aberta
    pthread_mutex_unlock(&bilheteria_aberta_mutex); // Libera o mutex
}

// Essa função deve finalizar a bilheteria
void close_tickets(){

    pthread_mutex_lock(&bilheteria_aberta_mutex); // Garante atomicidade da variável global com o mutex
    bilheteria_aberta = 0; // Garante atomicidade da variável global com o mutex
    pthread_mutex_unlock(&bilheteria_aberta_mutex); // Libera o mutex
    for (int i = 0; i < n_tickets; i++) {
        pthread_join(atendentes[i], NULL);  // Sincronização de todas as threads dos funcionarios
    }
    //Sua lógica aqui
    //free(ticket);
    
}