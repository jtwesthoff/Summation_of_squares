
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 20

long accum = 0;
pthread_mutex_t accum_mutex;

// Function prototype for the thread function
void* square(void*);

// Thread function to compute the square of the parameter
void *square(void *param) {
    int num = *(int *)param; // Dereference the void pointer to get the integer parameter
    long thread_result = num * num;
    
    // Lock the mutex to update the global accumulator safely
    pthread_mutex_lock(&accum_mutex);
    accum += thread_result;
    pthread_mutex_unlock(&accum_mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int* params[NUM_THREADS];

    // Initialize mutex and check for errors
    if (pthread_mutex_init(&accum_mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (long t = 0; t < NUM_THREADS; t++) {
        params[t] = (int*)malloc(sizeof(int));
        if (params[t] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        *params[t] = t + 1;
        // Create thread and check for errors
        if (pthread_create(&threads[t], NULL, square, (void*)params[t]) != 0) {
            fprintf(stderr, "Thread creation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // Join thread and check for errors
    for (long t = 0; t < NUM_THREADS; t++) {
        if (pthread_join(threads[t], NULL) != 0) {
            fprintf(stderr, "Thread joining failed\n");
            exit(EXIT_FAILURE);
        }
        free(params[t]); //Free memory for thread parameters
    }
    // Destroy mutex and check for errors
    if (pthread_mutex_destroy(&accum_mutex) != 0) {
        fprintf(stderr, "Mutex destruction failed\n");
        exit(EXIT_FAILURE);
    }
    //Output
    printf("Sum of squares = %ld\n", accum);
    pthread_exit(NULL);
}