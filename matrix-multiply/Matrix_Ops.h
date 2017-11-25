//
// Created by ahmed on 11/23/17.
//

#ifndef MATRIX_MULTIPLY_MATRIX_OP_H
#define MATRIX_MULTIPLY_MATRIX_OP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    double **matrix;
} Matrix;

/**
 * @brief Dynamically allocates new matrix of size row * col
 * @param row
 * @param col
 * @return Matrix, the allocated matrix
 */
Matrix new_matrix(int row, int col);

/**
 * @brief Reads a matrix file and loads it into Matrix struct
 * @param file_name
 * @return Matrix, the loaded matrix from the disk
 */
Matrix read_matrix(char *file_name);

/**
 * @brief Calculates element value of the new matrix
 * @param a Matrix 1
 * @param b Matrix 2
 * @param c Resulting matrix
 * @param i Element row
 * @param j Element col
 */
void multiply_element(Matrix a, Matrix b, Matrix c, int i, int j);

/**
 * @brief Calculates a row value of the new matrix
 * @param a Matrix 1
 * @param b Matrix 2
 * @param c Resulting matrix
 * @param i Row to be calculated
 */
void multiply_row(Matrix a, Matrix b, Matrix c, int i);

/**
 * @brief Multiplies tow matrices a & b
 * @param a
 * @param b
 * @return Matrix, the value of multiplication
 */
Matrix multiply_matrix(Matrix a, Matrix b);

/**
 * @brief Prints a matrix struct to the stdout
 * @param mat
 */
void print_matrix(Matrix mat, char *file_name);

#endif //MATRIX_MULTIPLY_MATRIX_OP_H
