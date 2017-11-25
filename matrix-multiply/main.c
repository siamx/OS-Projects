#include "Thread.h"

void write(int row, int col);

int main() {
//    write(30, 30);

    a = read_matrix("tests/A1.txt");
    b = read_matrix("tests/B1.txt");
    c = new_matrix(a.row, b.col);
    clock_t time;


    time = clock();
    c = multiply_matrix(a, b);
    time = clock() - time;
    print_matrix(c);
    free(c.matrix);
    printf("%20s,    1 thread: %lf sec.\n\n", "single thread", (double) time / CLOCKS_PER_SEC);

    int thread_count = 4;
    for (int i = 0; i < 3; ++i) {
        c = new_matrix(a.row, b.col);
        time = clock();
        int created_threads = function[i](thread_count);
        time = clock() - time;
//        print_matrix(c);
        free(c.matrix);
        printf("%20s, %4d thread: %lf sec.\n\n", function_name[i], created_threads, (double) time / CLOCKS_PER_SEC);
    }
}

/**
 * @brief fills the two input matrices with random numbers
 * @param row
 * @param col
 */
void write(int row, int col) {
    const int max_rand = 101;

    freopen("tests/A1.txt", "w", stdout);
    printf("%d %d\n", row, col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int number = rand() % max_rand; // NOLINT
            printf("%lf ", (double) number);
        }
        printf("\n");
    }
    fclose(stdout);

    freopen("tests/B1.txt", "w", stdout);
    printf("%d %d\n", col, row);
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            int number = rand() % max_rand; // NOLINT
            printf("%lf ", (double) number);
        }
        printf("\n");
    }
    fclose(stdout);

    exit(0);
}
