    /**
     * Esse arquivo tem como objetivo a implementação de um brinquedo em um parque.
     * Você pode criar novas funções dentro desse arquivo caso julgue necessário.
     * ATENÇÃO: NÃO APAGUE OU EDITE O NOME OU O(S) ARGUMENTO(S) DAS FUNÇÕES FORNECIDAS
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h>
    #include "toy.h"
    #include "shared.h" 
    
    // Thread que o brinquedo vai usar durante toda a simulacao do sistema
    
    void *turn_on(void *args) {
        toy_t *toy = (toy_t *)args; 
        int em_uso;
        debug("[ON] - O brinquedo [%d] foi ligado.\n", toy->id);
        
        sleep(5); // Tempo suficiente pra alocar os clientes nos brinquedos
        while (TRUE) {
            if (ar_clients == NULL) {
                break;
            }
            pthread_mutex_lock(&toy->mutex); // Mutex para cada brinquedo que for acessar.

            while (toy->current_capacity == 0) { // Enquanto não houver clientes no brinquedo, ele ficará aguardando
                em_uso = 0;
            }

            if (toy->current_capacity == toy->capacity) { // Se encheu o brinquedo, inicio ele
                em_uso = 1;
            } else if (toy->current_capacity < toy->capacity) { // Se não encheu, mas já tenho clientes, espero e inicializo
                sleep(1);
                em_uso = 1;
            }

            while (toy->current_capacity > toy->capacity) {
                em_uso = 0;                     // Não posso iniciar o brinquedo com mais clientes do que ele suporta
                toy->current_capacity--;
            }

            em_uso = 1; // Ao chegar aqui, toy->capacity é menor ou igual a MAX_CAPACITY_TOY
            if (em_uso == 1){
            debug("[RUNNING] - O brinquedo [%d] está em funcionamento.\n", toy->id);
            
            sleep(tempo_exec_toy); // Duração do brinquedo
            }
            em_uso = 0;
            toy->current_capacity = 0; // Resetar capacidade para próxima vez que for brincar
            
            debug("[FINISHED] - O brinquedo [%d] terminou.\n", toy->id);

            pthread_mutex_unlock(&toy->mutex); // Libero o mutex para o brinquedo que foi acessado
        }
        
        debug("[OFF] - O brinquedo [%d] foi desligado.\n", toy->id);
        pthread_exit(NULL);
    }

        

    // Essa função recebe como argumento informações e deve iniciar os brinquedos.
    
    void open_toys(toy_args *args) {
        arr_toys = (toy_t **) malloc(args->n * sizeof(toy_t)); // Array de toys
        for (int i = 0; i < args->n; i++) {  // Criação de cada brinquedo
            arr_toys[i] = args->toys[i]; // Insere os argumentos no array de toys
            pthread_create(&args->toys[i]->thread, NULL, turn_on, (void *) arr_toys[i]);
        }

    }

    // Desligando os brinquedos
    void close_toys(){
        // Sua lógica aqui
        sleep(5);
        pthread_exit(NULL);
        free(arr_toys);
    }
