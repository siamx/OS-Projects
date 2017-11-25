//
// Created by ahmed on 11/24/17.
//

#include "Thread.h"

char *function_name[] = {
        "variable thread",
        "thread per row",
        "thread per element"
};

int (*function[])(int thread_cnt) = {
        &variable_threads,
        (int (*)(int)) &thread_per_row,
        (int (*)(int)) &thread_per_element
};

/**
 * @brief creates a thread pool of given number of threads
 * @param arguments
 * @return
 */
void *runner_multiply_row_variable_threads(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    for (int i = args->row; i < a.row; i += args->shift)
        multiply_row(a, b, c, i);
    pthread_exit(NULL);
    return NULL;
}

int variable_threads(int thread_cnt) {
    pthread_args args[thread_cnt];
    pthread_t thread[thread_cnt];
    int cnt = 0;
    for (int i = 0; i < thread_cnt; ++i) {
        args[i].row = i;
        args[i].shift = thread_cnt;
        int cur = pthread_create(&thread[i], NULL, runner_multiply_row_variable_threads, (void *) &args[i]);
        if (cur != 0) {
            printf("Uh-oh! Failed to create thread %d\n", i + 1);
            exit(0);
        } else {
            cnt++;
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < thread_cnt; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}

/**
 * @brief creates a new thread for each element in the new matrix
 * @param arguments
 * @return
 */
void *runner_multiply_row(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    multiply_row(a, b, c, args->row);
    pthread_exit(NULL);
    return NULL;
}

int thread_per_row() {
    pthread_args args[a.row];
    pthread_t thread[a.row];
    int cnt = 0;
    for (int i = 0; i < a.row; ++i) {
        args[i].row = i;
        int cur_thread = pthread_create(&thread[i], NULL, runner_multiply_row, (void *) &args[i]);
        if (cur_thread != 0) {
            printf("Uh-oh! Failed to create thread %d\n", i);
            exit(0);
        } else {
            cnt++;
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < cnt; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}

/**
 * @brief creates a new thread for each element in the new matrix
 * @param arguments
 * @return
 */
void *runner_multiply_element(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    multiply_element(a, b, c, args->row, args->col);
    pthread_exit(NULL);
    return NULL;
}

int thread_per_element() {
    pthread_args args[a.row * b.col];
    pthread_t thread[a.row * b.col];
    int cnt = 0;
    for (int i = 0; i < a.row; ++i) {
        for (int j = 0; j < b.col; ++j) {
            args[cnt].row = i;
            args[cnt].col = j;
            int cur = pthread_create(&thread[cnt], NULL, runner_multiply_element, (void *) &args[cnt]);
            if (cur != 0) {
                printf("Uh-oh! Failed to create thread %d\n", j);
                exit(0);
            } else {
                cnt++;
            }
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < cnt; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}
