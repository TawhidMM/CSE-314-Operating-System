#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "random.h"
#include "time_stamp.h"
#include "ansi_color.h"
#include "visitor_tracking.h"

using namespace std;

typedef pthread_mutex_t mutex;
void initialize();
void init_bool_array(bool* arr, int size);
void create_visitors(Visitor* visitors, int N, int M);
void print_action(int id, string action, string color);
void read_input(int argc, char* argv[]);

int N = 3;
int M = 2;
int HALLWAY_TIME = 2;
int GALLERY1_TIME = 6;
int BOOTH_TIME = 3;
int GALLERY2_TIME = 4;

volatile int standard_count = 0;
volatile int prem_count = 0;

mutex booth_mtx;
mutex premium_mtx;
mutex std_counter_mtx;
mutex prem_counter_mtx;
mutex step_mtx[STEP_NUM];
sem_t gallary1_sem;
sem_t corridor_sem;
mutex print_mtx;

void standard_gallary2(Visitor* visitor) {
    sleep(GALLERY2_TIME);
    print_action(visitor->id, ENTER_BOOTH, RED);
    
    pthread_mutex_lock(&premium_mtx);

    pthread_mutex_lock(&std_counter_mtx);

    standard_count++;
    if(standard_count == 1)
        pthread_mutex_lock(&booth_mtx);
    pthread_mutex_unlock(&premium_mtx);

    pthread_mutex_unlock(&std_counter_mtx);

    print_action(visitor->id, AT_BOOTH, GRN);
    sleep(BOOTH_TIME);

    pthread_mutex_lock(&std_counter_mtx);
    standard_count--;
    if(standard_count == 0)
        pthread_mutex_unlock(&booth_mtx);
    pthread_mutex_unlock(&std_counter_mtx);
    

}

void premium_gallary2(Visitor* visitor) {
    sleep(GALLERY2_TIME);
    print_action(visitor->id, ENTER_BOOTH, RED);

    pthread_mutex_lock(&prem_counter_mtx);
    prem_count++;
    if(prem_count == 1)
        pthread_mutex_lock(&premium_mtx);
    pthread_mutex_unlock(&prem_counter_mtx);

    pthread_mutex_lock(&booth_mtx);

    print_action(visitor->id, AT_BOOTH, GRN);
    sleep(BOOTH_TIME);

    pthread_mutex_unlock(&booth_mtx);

    pthread_mutex_lock(&prem_counter_mtx);
    prem_count--;
    if(prem_count == 0)
        pthread_mutex_unlock(&premium_mtx);
    pthread_mutex_unlock(&prem_counter_mtx);

}


void pass_steps(int step_index, Visitor* visitor) {
    pthread_mutex_lock(&step_mtx[step_index]);

    switch (step_index) {
    case 0:
        print_action(visitor->id, AT_STEP(1), WHT);
        break;
    case 1:
        print_action(visitor->id, AT_STEP(2), WHT);
        break;
    case 2:
        print_action(visitor->id, AT_STEP(3), WHT);
        break;
    default:
        break;
    }

    if(step_index > 0) {
        pthread_mutex_unlock(&step_mtx[step_index - 1]);
    }
    
    usleep(STEPS_DELAY);
}

void enter_gallary1(Visitor* visitor) {
    sem_wait(&gallary1_sem);
    pthread_mutex_unlock(&step_mtx[STEP_NUM - 1]);

    print_action(visitor->id, AT_GALLERY(C, 1), MAG);

    sleep(GALLERY1_TIME);
}

void pass_corridor(Visitor* visitor) {
    sem_wait(&corridor_sem);
    sem_post(&gallary1_sem);

    print_action(visitor->id, EXIT_GALLERY(D, 1), YEL);
    sleep(CORRIDOR_DELAY);

    print_action(visitor->id, AT_GALLERY(E, 2), BLU);

    sem_post(&corridor_sem);
}

void* start_visit(void* arg) {
    Visitor* visitor = (Visitor*)arg;

    print_action(visitor->id, ARRIVAL(A), RED);
    sleep(HALLWAY_TIME);
    print_action(visitor->id, ARRIVAL(B), BLU);

    for(int i = 0; i < STEP_NUM; i++) {
        pass_steps(i, visitor);
    }

    enter_gallary1(visitor);
    pass_corridor(visitor);

    if(visitor->state == STANDARD) {
        standard_gallary2(visitor);
    }
    else {
        premium_gallary2(visitor);
    }

    print_action(visitor->id, LEFT, CYN);
    
    return NULL;
}



int main(int argc, char* argv[]) {
    read_input(argc, argv);
    start_timer(2);
    
    int total_visitors = N + M;
    int entered_visitors = 0;
    bool entered[total_visitors];
    double delays[VISITOR_DELAY] = {5e5, 1e6, 1.5e6};

    Visitor visitors[total_visitors];
    pthread_t visitor_threads[total_visitors];

    initialize();
    init_bool_array(entered, total_visitors);
    
    create_visitors(visitors, N, M);


    while(entered_visitors < total_visitors) {
        int randomVisitor = get_random_number() % total_visitors;
        if(!entered[randomVisitor]) {
            entered[randomVisitor] = true;
            pthread_create(&visitor_threads[randomVisitor], NULL, 
                start_visit, &visitors[randomVisitor]);

            entered_visitors++;
            usleep(
                get_random_from_array(delays, VISITOR_DELAY)
            );
        }
    }
    
    for (int i = 0; i < N + M; i++) {
        pthread_join(visitor_threads[i], NULL); 
    }

    stop_timer();

    cout << "All visitors have left the museum at " << endl;

}

void initialize() {
    sem_init(&gallary1_sem, 0, GALLERY1_CAPACITY);
    sem_init(&corridor_sem, 0, CORRIDOR_CAPACITY);

    for(int i = 0; i < STEP_NUM; i++) {
        pthread_mutex_init(&step_mtx[i], NULL);
    }

    pthread_mutex_init(&booth_mtx, NULL);
    pthread_mutex_init(&premium_mtx, NULL);
    pthread_mutex_init(&std_counter_mtx, NULL);
    pthread_mutex_init(&prem_counter_mtx, NULL);  
    pthread_mutex_init(&print_mtx, NULL);
}

void init_bool_array(bool* arr, int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = false;
    }
}

void create_visitors(Visitor* visitors, int N, int M) {
    int standardID = STANDARD_ID;
    int premiumID = PREMIUM_ID;

    for(int i = 0; i < N + M; i++) {
        if(i < N) {
            visitors[i].id = ++standardID;
            visitors[i].state = STANDARD;
        }
        else {
            visitors[i].id = ++premiumID;
            visitors[i].state = PREMIUM;
        }
    }

}

void print_action(int id, string action, string color) {
    pthread_mutex_lock(&print_mtx);
    cout << color << "Visitor " << id << " " << action << 
        " at timestamp " << curr_time << RESET << endl;
    pthread_mutex_unlock(&print_mtx);
}

void read_input(int argc, char* argv[]) {
    if(argc < 7) {
        cout << "Running with default values -- " << endl;
        cout << "N = " << N << ", M = " << M << endl;
        cout << "Hallway time = " << HALLWAY_TIME << ", ";
        cout << "Gallery1 time = " << GALLERY1_TIME << ", ";
        cout << "Gallery2 time = " << GALLERY2_TIME << ", ";
        cout << "Booth time = " << BOOTH_TIME << endl;
        cout << endl;
    }
    else {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        HALLWAY_TIME = atoi(argv[3]);
        GALLERY1_TIME = atoi(argv[4]);
        GALLERY2_TIME = atoi(argv[5]);
        BOOTH_TIME = atoi(argv[6]);
    }
}