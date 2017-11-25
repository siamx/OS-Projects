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

/**
 * @brief Array of function names
 */
char *function_name[3];

/**
 * @brief function pointer
 * @param thread_cnt
 * @return The return value of the pointed to function
 */
int (*function[3])(int thread_cnt);

/**
 * @brief Multiplies two matrices by creating new thread for each element in the resulting matrix
 * @return Number of created threads
 */
int thread_per_element();

/**
 * @brief Multiplies two matrices by creating new thread for each row in the resulting matrix
 * @return Number of created threads
 */
int thread_per_row();

/**
 * @brief Multiplies two matrices by creating given number of threads
 * @param thread_cnt Number of threads to be created
 * @return Number of created threads
 */
int variable_threads(int thread_cnt);

#endif //MATRIX_MULTIPLY_THREAD_H
