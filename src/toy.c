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
    //pthread_mutex_t toy_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex utilizado para cada brinquedo 
    
    // Thread que o brinquedo vai usar durante toda a simulacao do sistema
    
    void *turn_on(void *args) {
        toy_t *toy = (toy_t *)args; 
        debug("[ON] - O brinquedo [%d] foi ligado.\n", toy->id);
        while(!sinalizador_close_toy) {
        
            //pthread_mutex_lock(&toy_mutex); // Mutex para cada brinquedo que for acessar. REVER USO DO MUTEX

            // Tem que adicionar um semáforo para o toys pois quando o current_Capacity é att dps da linha 26, a att é sobrescrita por zero, entao tem que fazer um sistema de espera para o current capacity

            if (toy->current_capacity <= MAX_CAPACITY_TOY && toy->current_capacity >= MIN_CAPACITY_TOY) { // Se encheu o brinquedo, inicio ele
                toy->em_uso = 1;
            } else {
                toy->em_uso = 0;
                sleep(tempo_espera_toy);
            }

            while (toy->current_capacity > MAX_CAPACITY_TOY) {
                // Não posso iniciar o brinquedo com mais clientes do que ele suporta
                toy->current_capacity--;
            }

            toy->em_uso = 1; // Ao chegar aqui, toy->capacity é menor ou igual a MAX_CAPACITY_TOY
            if (toy->em_uso == 1 && toy->current_capacity != 0){
                debug("[RUNNING] - O brinquedo [%d] está em funcionamento com [%d] passageiro(s).\n", toy->id, toy->current_capacity);
                sleep(tempo_exec_toy); // Duração do brinquedo
                debug("[FINISHED] - O brinquedo [%d] terminou.\n", toy->id);
            }
            //while(toy->em_uso) {
            //    sleep(tempo_exec_toy); // Duração do brinquedo
            //}
            toy->em_uso = 0;
            toy->current_capacity = 0; // Resetar capacidade para próxima vez que for brincar
            

            //pthread_mutex_unlock(&toy_mutex); // Libero o mutex para o brinquedo que foi acessado
        }
        
        debug("[OFF] - O brinquedo [%d] foi desligado.\n", toy->id);
        pthread_exit(NULL);
    }

        

    // Essa função recebe como argumento informações e deve iniciar os brinquedos.
    
    void open_toys(toy_args *args) {
        //ar_toys = (toy_t **) malloc(args->n * sizeof(toy_t)); // Array de toys
        pthread_mutex_lock(&sinalizador_close_toy_mutex);
        sinalizador_close_toy = 0;
        pthread_mutex_unlock(&sinalizador_close_toy_mutex);
        ar_toys = args->toys;
        n_toys = args -> n;
        for (int i = 0; i < n_toys; i++) {  // Criação de cada brinquedo
            //ar_toys[i] = args->toys[i]; // Insere os argumentos no array de toys
            pthread_create(&args->toys[i]->thread, NULL, turn_on, (void *) ar_toys[i]);
        }

    }

    // Desligando os brinquedos
    void close_toys(){
        // Sua lógica aqui
        for(int i = 0; i < n_toys; i ++) {
            pthread_join(ar_toys[i]->thread, NULL);
        }
    }
