#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dispatch/dispatch.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int count = 0;

dispatch_semaphore_t semEmpty;
dispatch_semaphore_t semFull;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg) {
    while (1) {
        dispatch_semaphore_wait(semEmpty, DISPATCH_TIME_FOREVER);

        pthread_mutex_lock(&mutex);
        buffer[count++] = rand() % 100;
        printf("Produced: %d\n", buffer[count - 1]);
        pthread_mutex_unlock(&mutex);

        dispatch_semaphore_signal(semFull);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        dispatch_semaphore_wait(semFull, DISPATCH_TIME_FOREVER);

        pthread_mutex_lock(&mutex);
        printf("Consumed: %d\n", buffer[--count]);
        pthread_mutex_unlock(&mutex);

        dispatch_semaphore_signal(semEmpty);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    semEmpty = dispatch_semaphore_create(BUFFER_SIZE);
    semFull = dispatch_semaphore_create(0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    dispatch_release(semEmpty);
    dispatch_release(semFull);

    pthread_mutex_destroy(&mutex);

    return 0;
}

