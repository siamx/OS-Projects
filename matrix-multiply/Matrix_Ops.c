//
// Created by ahmed on 11/23/17.
//

#include "Matrix_Ops.h"

Matrix new_matrix(int row, int col) {
    Matrix mat;
    mat.col = col;
    mat.row = row;

    mat.matrix = (double **) malloc(mat.row * sizeof(double *));

    if (!mat.matrix) {
        fprintf(stderr, "allocation error");
        exit(0);
    }

    mat.matrix[0] = (double *) malloc(2 * sizeof(double));
    if (!mat.matrix[0]) {
        fprintf(stderr, "allocation error");
        exit(0);
    }

    for (int i = 0; i < mat.row; ++i) {
        mat.matrix[i] = (double *) malloc(mat.col * sizeof(double));
        if (!mat.matrix[i]) {
            fprintf(stderr, "allocation error");
            exit(0);
        }
    }

    return mat;
}

Matrix read_matrix(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stdout, "Failed to write output matrix to file.");
        exit(1);
    }

    int row, col;
    fscanf(file, "%d %d", &row, &col); // NOLINT

    Matrix mat = new_matrix(row, col);

    for (int i = 0; i < mat.row; ++i)
        for (int j = 0; j < mat.col; ++j)
            fscanf(file, " %lf", &(mat.matrix[i][j])); // NOLINT

    fclose(file);
    return mat;
}

void print_matrix(Matrix matrix, char *file_name) {
    FILE *file = fopen(file_name, "w+");
    if (!file) {
        fprintf(stdout, "Failed to write output matrix to file.");
        exit(1);
    }

    fprintf(file, "%d %d\n", matrix.row, matrix.col);

    for (int i = 0; i < matrix.row; ++i) {
        for (int j = 0; j < matrix.col; ++j) {
            fprintf(file, "%-2lf ", matrix.matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

Matrix multiply_matrix(Matrix a, Matrix b) {
    if (a.col != b.row) {
        fprintf(stderr, "Can not multiply the two matrices");
        exit(1);
    }

    Matrix c = new_matrix(a.row, b.col);
    for (int i = 0; i < a.row; ++i)
        multiply_row(a, b, c, i);

    return c;
}

void multiply_element(Matrix a, Matrix b, Matrix c, int i, int j) {
    c.matrix[i][j] = 0;
    for (int k = 0; k < b.row; ++k) {
        c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
    }
}

void multiply_row(Matrix a, Matrix b, Matrix c, int i) {
    for (int j = 0; j < c.col; ++j) {
        multiply_element(a, b, c, i, j);
    }
}
