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
        sem_init(&semaforo_toys, 0, 0);
        debug("[ON] - O brinquedo [%d] foi ligado.\n", toy->id);
        while(!sinalizador_close_toy) {
        
            // Tem que adicionar um semáforo para o toys pois quando o current_Capacity é att dps da linha 26, a att é sobrescrita por zero, entao tem que fazer um sistema de espera para o current capacity

            while (toy->current_capacity > toy->capacity) {
                // Não posso iniciar o brinquedo com mais clientes do que ele suporta
                pthread_mutex_lock(&toy->mutex);
                toy->current_capacity--;
                pthread_mutex_unlock(&toy->mutex);
            }

            if (toy->current_capacity <= toy->capacity && toy->current_capacity != 0) { // Se encheu o brinquedo, inicio ele
                debug("[RUNNING] - O brinquedo [%d] está em funcionamento com [%d] passageiro(s).\n", toy->id, toy->current_capacity);
                sleep(tempo_exec_toy); // Duração do brinquedo
                debug("[FINISHED] - O brinquedo [%d] terminou.\n", toy->id);
                
                toy->current_capacity = 0; // Resetar capacidade para próxima vez que for brincar
            } else {
                sleep(tempo_espera_toy);
                
                //debug("1239012830918301928310")
            }
            for (int i = 0; i < toy->current_capacity; i++) {
                sem_post(&semaforo_toys);
            }

        }
        
        debug("[OFF] - O brinquedo [%d] foi desligado.\n", toy->id);
        pthread_exit(NULL);
    }

        

    // Essa função recebe como argumento informações e deve iniciar os brinquedos.
    
    void open_toys(toy_args *args) {
        pthread_mutex_lock(&sinalizador_close_toy_mutex);
        sinalizador_close_toy = 0;
        pthread_mutex_unlock(&sinalizador_close_toy_mutex);
        ar_toys = args->toys;
        n_toys = args -> n;
        for (int i = 0; i < n_toys; i++) {  // Criação de cada brinquedo
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
