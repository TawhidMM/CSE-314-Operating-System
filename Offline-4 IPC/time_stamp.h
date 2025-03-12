#include <pthread.h>
#include <unistd.h>


volatile int timer_running = 0;
volatile int curr_time = 0;
pthread_t timer_thread;

void* update_time(void* arg) {
    while (timer_running) {
        sleep(1);
        curr_time++;
    }

    return NULL;
}


void start_timer(int start_time) {
    curr_time = start_time;
    timer_running = 1;

    pthread_create(&timer_thread, NULL, update_time, NULL);
}

void stop_timer() {
    timer_running = 0;
    pthread_join(timer_thread, NULL);
}