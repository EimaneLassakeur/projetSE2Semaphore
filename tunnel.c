#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NB_BUS_X 5
#define NB_BUS_Y 4
#define NB_TRAJETS 10

sem_t mutex;
sem_t tunnel;
int count_XY = 0;
int count_YX = 0;
int direction = 0; // 0: libre, 1: X->Y, 2: Y->X

void trajet(int id, char villeDepart, char villeArrivee, int trajet_num) {
    printf("Bus %d de %c : %c -> %c (Trajet %d)\n", id, villeDepart, villeDepart, villeArrivee, trajet_num);
    usleep((rand() % 500 + 1000) * 1000); // entre 1s et 1.5s
}

void entrer_tunnel_XY(int id) {
    while (1) {
        sem_wait(&mutex);
        if (direction == 0 || direction == 1) {
            count_XY++;
            direction = 1;
            sem_post(&mutex);
            break;
        }
        sem_post(&mutex);
        usleep(10000); // évite l'occupation CPU (attente active)
    }
}

void sortir_tunnel_XY(int id) {
    sem_wait(&mutex);
    count_XY--;
    if (count_XY == 0) {
        direction = 0;
    }
    sem_post(&mutex);
}

void entrer_tunnel_YX(int id) {
    while (1) {
        sem_wait(&mutex);
        if (direction == 0 || direction == 2) {
            count_YX++;
            direction = 2;
            sem_post(&mutex);
            break;
        }
        sem_post(&mutex);
        usleep(10000);
    }
}

void sortir_tunnel_YX(int id) {
    sem_wait(&mutex);
    count_YX--;
    if (count_YX == 0) {
        direction = 0;
    }
    sem_post(&mutex);
}

void* bus_X(void* arg) {
    int id = *(int*)arg;
    for (int i = 1; i <= NB_TRAJETS; i++) {
        entrer_tunnel_XY(id);
        trajet(id, 'X', 'Y', i);
        sortir_tunnel_XY(id);

        entrer_tunnel_YX(id);
        trajet(id, 'Y', 'X', i);
        sortir_tunnel_YX(id);
    }
    pthread_exit(NULL);
}

void* bus_Y(void* arg) {
    int id = *(int*)arg;
    for (int i = 1; i <= NB_TRAJETS; i++) {
        entrer_tunnel_YX(id);
        trajet(id, 'Y', 'X', i);
        sortir_tunnel_YX(id);

        entrer_tunnel_XY(id);
        trajet(id, 'X', 'Y', i);
        sortir_tunnel_XY(id);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    pthread_t threads[NB_BUS_X + NB_BUS_Y];
    int ids[NB_BUS_X + NB_BUS_Y];

    sem_init(&mutex, 0, 1);

    // Créer les threads des bus de X
    for (int i = 0; i < NB_BUS_X; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, bus_X, &ids[i]);
    }

    // Créer les threads des bus de Y
    for (int i = 0; i < NB_BUS_Y; i++) {
        ids[NB_BUS_X + i] = i + 1;
        pthread_create(&threads[NB_BUS_X + i], NULL, bus_Y, &ids[NB_BUS_X + i]);
    }

    for (int i = 0; i < NB_BUS_X + NB_BUS_Y; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    return 0;
}
