#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix_Ops.h"

Matrix a, b, c;

typedef struct {
    int row;
    int col;
    int shift;
} pthread_args;

void write(int row, int col);

int thread_per_element(Matrix a, Matrix b);

int thread_per_row(Matrix a);

int variable_threads(int thread_count);

int main() {
//    write(20, 20);

    a = read_matrix("matrix_A");
    b = read_matrix("matrix_B");
    c = new_matrix(a.row, b.col);

    clock_t time;


    time = clock();
    c = multiply_matrix(a, b);
    time = clock() - time;
    double run_time = ((double) time) / CLOCKS_PER_SEC; // in seconds
    printf(" single thread: took %f seconds to execute \n", run_time);
//    print_matrix(c);


    time = clock();
    thread_per_row(a);
    time = clock() - time;
    run_time = ((double) time) / CLOCKS_PER_SEC; // in seconds
    printf("thread per row: took %f seconds to execute \n", run_time);
//    print_matrix(c);


    time = clock();
    int threads = 4;
    variable_threads(threads);
    time = clock() - time;
    run_time = ((double) time) / CLOCKS_PER_SEC; // in seconds
    printf("%6d threads: took %f seconds to execute \n", threads, run_time);
//    print_matrix(c);


//    time = clock();
//    c = thread_per_element(a, b);
//    time = clock() - time;
//    run_time = ((double) time) / CLOCKS_PER_SEC; // in seconds
//    printf("thread per elem: took %f seconds to execute \n", run_time);
//    print_matrix(c);
}

void *runner_multiply_element(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    multiply_element(a, b, c, args->row, args->col);
    pthread_exit(NULL);
    return NULL;
}

void *runner_multiply_row(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    multiply_row(a, b, c, args->row);
    pthread_exit(NULL);
    return NULL;
}

void *runner_multiply_row_variable_threads(void *arguments) {
    pthread_args *args = (pthread_args *) arguments;
    for (int i = args->row; i < a.row; i += args->shift)
        multiply_row(a, b, c, i);
    pthread_exit(NULL);
    return NULL;
}

int thread_per_element(Matrix a, Matrix b) {
    pthread_args args[a.row * b.col];
    pthread_t thread[a.row * b.col];
    int cnt = 0;
    for (int i = 0; i < a.row; ++i) {
        for (int j = 0; j < b.col; ++j) {
            args[i].row = i;
            args[i].col = j;
            int cur_thread = pthread_create(&thread[i], NULL, runner_multiply_element, (void *) &args[i]);
            if (cur_thread != 0) {
                printf("Uh-oh! Failed to create thread %d\n", i);
                exit(0);
            } else {
                cnt++;
            }
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < a.row * b.col; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}

int thread_per_row(Matrix a) {
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
    for (int i = 0; i < a.row; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}

int variable_threads(int thread_count) {
    pthread_args args[thread_count];
    pthread_t thread[thread_count];
    int cnt = 0;
    for (int i = 0; i < thread_count; ++i) {
        args[i].row = i;
        args[i].shift = thread_count;
        int cur_thread = pthread_create(&thread[i], NULL, runner_multiply_row_variable_threads, (void *) &args[i]);
        if (cur_thread != 0) {
            printf("Uh-oh! Failed to create thread %d\n", i + 1);
            exit(0);
        } else {
            cnt++;
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < thread_count; ++i) {
        pthread_join(thread[i], NULL);
    }

    return cnt;
}

void write(int row, int col) {
    freopen("matrix_A", "w", stdout);

    printf("%d %d\n", row, col);
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            printf("%lf ", (double) j);
        }
        printf("\n");
    }
    fclose(stdout);

    freopen("matrix_B", "w", stdout);
    printf("%d %d\n", col, row);
    for (int i = 1; i <= col; ++i) {
        for (int j = 1; j <= row; ++j) {
            printf("%lf ", (double) j);
        }
        printf("\n");
    }
    fclose(stdout);
    exit(0);
}
