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
    pthread_mutex_t toy_mutex; // Mutex utilizado para cada brinquedo 
    toy_t *arr_toys;   // Array de briquedos

    // Thread que o brinquedo vai usar durante toda a simulacao do sistema
    void *turn_on(void *args) {
        toy_t *toy = (toy_t *)args;
        pthread_mutex_init(&toy_mutex, NULL); 

        debug("[ON] - O brinquedo [%d] foi ligado.\n", toy->id);
        
        while (TRUE) { 
            pthread_mutex_lock(&toy_mutex); // Mutex para cada brinquedo que for acessar

            // Implementar lógica do brinquedo (que é uma thread que vai executar essa função) aqui
            debug("[RUNNING] - O brinquedo [%d] está em funcionamento.\n", toy->id);
            
            // Se cliente quiser brincar aqui, deve esperar, pois já está em funcionamento
            debug("[FINISHED] - O brinquedo [%d] terminou.\n", toy->id);

            toy->capacity = 0; // Resetar capacidade para próxima vez que for brincar
            pthread_mutex_unlock(&toy_mutex); // Libero o mutex para o brinquedo que foi acessado
        }

        debug("[OFF] - O brinquedo [%d] foi desligado.\n", toy->id);
        pthread_exit(NULL);
    }


    // Essa função recebe como argumento informações e deve iniciar os brinquedos.
    void open_toys(toy_args *args) {
        arr_toys = (toy_t *) malloc(args->n * sizeof(toy_t)); // Array de toys
        for (int i = 0; i < args->n; i++) {  // Criação de cada brinquedo
        arr_toys[i] = *args->toys[i]; // Insere os argumentos no array de toys
            pthread_create(&args->toys[i]->thread, NULL, turn_on, (void *) &arr_toys[i]);
        }
        for (int i = 0; i < args->n; i++) {  // Sincronização dos brinquedos
            pthread_join(&args->toys[i]->thread, NULL);
        }
    }

    // Desligando os brinquedos
    void close_toys(){
        // Sua lógica aqui
        pthread_exit(NULL);
        free(arr_toys);
    }
