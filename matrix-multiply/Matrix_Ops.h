//
// Created by ahmed on 11/23/17.
//

#ifndef MATRIX_MULTIPLY_MATRIX_OP_H
#define MATRIX_MULTIPLY_MATRIX_OP_H

typedef struct {
    int row;
    int col;
    double **matrix;
} Matrix;

Matrix new_matrix(int row, int col);

Matrix read_matrix(char *file_name);

void multiply_element(Matrix a, Matrix b, Matrix c, int i, int j);

void multiply_row(Matrix a, Matrix b, Matrix c, int i);

Matrix multiply_matrix(Matrix a, Matrix b);

void print_matrix(Matrix mat);

#endif //MATRIX_MULTIPLY_MATRIX_OP_H
