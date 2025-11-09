#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int readcount = 0, data = 0;

void* reader(void* arg) {
    long f = (long)arg;   // ✅ FIXED
    pthread_mutex_lock(&mutex);
    readcount++;
    if(readcount == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader %ld reads data = %d\n", f, data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;
    if(readcount == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* writer(void* arg) {
    long f = (long)arg;   // ✅ FIXED
    sem_wait(&wrt);
    data++;
    printf("Writer %ld writes data = %d\n", f, data);
    sem_post(&wrt);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for(long i=0; i<2; i++)     // ✅ use long instead of int
        pthread_create(&w[i], NULL, writer, (void*)i);

    for(long i=0; i<5; i++)
        pthread_create(&r[i], NULL, reader, (void*)i);

    for(int i=0; i<2; i++)
        pthread_join(w[i], NULL);

    for(int i=0; i<5; i++)
        pthread_join(r[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);
    return 0;
}
