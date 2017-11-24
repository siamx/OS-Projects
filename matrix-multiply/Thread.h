//
// Created by ahmed on 11/24/17.
//

#ifndef MATRIX_MULTIPLY_THREAD_H
#define MATRIX_MULTIPLY_THREAD_H

#include "Matrix_Ops.h"
#include <pthread.h>

Matrix a, b, c;

typedef struct {
    int row;
    int col;
    int shift;
} pthread_args;

char *function_name[3];

int (*function[3])(int thread_cnt);

int thread_per_element();

int thread_per_row();

int variable_threads(int thread_cnt);

#endif //MATRIX_MULTIPLY_THREAD_H
