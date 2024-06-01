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
    pthread_mutex_t toy_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex utilizado para cada brinquedo 
    toy_t *arr_toys;   // Array de briquedos
    // Thread que o brinquedo vai usar durante toda a simulacao do sistema
    
    void close_toys();

    void *turn_on(void *args) {
        toy_t *toy = (toy_t *)args; 
        int em_uso;
        debug("[ON] - O brinquedo [%d] foi ligado.\n", toy->id);

        pthread_mutex_lock(&toy_mutex); // Mutex para cada brinquedo que for acessar. REVER USO DO MUTEX

        while (toy->capacity == 0) { // Enquanto não houver clientes no brinquedo, ele ficará aguardando
            em_uso = 0;
        }

        if (toy->capacity == MAX_CAPACITY_TOY) { // Se encheu o brinquedo, inicio ele
            em_uso = 1;
        } else if (toy->capacity < MAX_CAPACITY_TOY) { // Se não encheu, mas já tenho clientes, espero e inicializo
            //sleep(1);
            em_uso = 1;
        }

        while (toy->capacity > MAX_CAPACITY_TOY) {
            em_uso = 0;                     // Não posso iniciar o brinquedo com mais clientes do que ele suporta
            toy->capacity--;
        }

        em_uso = 1; // Ao chegar aqui, toy->capacity é menor ou igual a MAX_CAPACITY_TOY
        if (em_uso == 1){
        debug("[RUNNING] - O brinquedo [%d] está em funcionamento.\n", toy->id);
        
        sleep(3); // Duração do brinquedo
        }
        em_uso = 0;
        toy->capacity = 0; // Resetar capacidade para próxima vez que for brincar
        
        debug("[FINISHED] - O brinquedo [%d] terminou.\n", toy->id);

        pthread_mutex_unlock(&toy_mutex); // Libero o mutex para o brinquedo que foi acessado
        
    

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
        //for (int i = 0; i < args->n; i++) {  // Sincronização dos brinquedos
        //    pthread_join(args->toys[i]->thread, NULL);
        //}
    }

    // Desligando os brinquedos
    void close_toys(){
        for (int i = 0; i < sizeof(arr_toys); i++) {
            pthread_join(arr_toys[i].thread, NULL);
        }
        // Sua lógica aqui
        free(arr_toys);
    }
