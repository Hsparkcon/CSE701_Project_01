#pragma once
#include <assert.h>
#include "../include/PCH.h"
#include "../include/matrix_struct.h"

#define TESTING_MAT_SIZE 10
double square_matrix[TESTING_MAT_SIZE][TESTING_MAT_SIZE] = {
    {1, 0, 0, 4, 0, 0, 7, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 6, 0, 0, 0, 0},
    {0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 5, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 6, 0, 0, 0, 10},
    {0, 0, 0, 0, 0, 0, 7, 0, 0, 0},
    {0, 0, 0, 0, 5, 0, 0, 8, 0, 0},
    {0, 0, 0, 0, 0, 0, 7, 8, 9, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 10},
};

// TEST CASES
// TEST MATRIX INFO
MATRIX_INFO sample_mat_data = (MATRIX_INFO){
    "test_case",
    10,
    10,
    18,
    0.18};

// TEST for COO
int32_t coo_desired_col_ind[] = {0, 3, 6, 1, 2, 5, 3, 1, 4, 5, 9, 6, 4, 7, 6, 7, 8, 9};
int32_t coo_desired_row_ind[] = {0, 0, 0, 1, 2, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 8, 9};
double coo_desired_val[] = {1, 4, 7, 2, 3, 6, 4, 2, 5, 6, 10, 7, 5, 8, 7, 8, 9, 10};

// TEST for CSR
int32_t csr_desired_row_ptr[] = {0, 3, 4, 6, 7, 9, 11, 12, 14, 17, 18};
int32_t csr_desired_col_ind[] = {0, 3, 6, 1, 2, 5, 3, 1, 4, 5, 9, 6, 4, 7, 6, 7, 8, 9};
double csr_desired_val[] = {1, 4, 7, 2, 3, 6, 4, 2, 5, 6, 10, 7, 5, 8, 7, 8, 9, 10};

// TEST for CSC
int32_t csc_desired_col_ptr[] = {0, 1, 3, 4, 6, 8, 10, 13, 15, 16, 18};
int32_t csc_desired_row_ind[] = {0, 1, 4, 2, 0, 3, 4, 7, 2, 5, 0, 6, 8, 7, 8, 8, 5, 9};
double csc_desired_val[] = {1, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 10, 10};

// TESTING MATRIX * VECTOR MULTIPLICATION
//// DENSE VECTOR VER.
int32_t d_vec_length = 10;
double dense_vector[] = {1, 3, 0, 4, 6, 9, 10, 5, 7, 0};
//// SPARSE VECTOR VER.
int32_t s_vec_length = 10;
int32_t num_nnz = 8;
int32_t desired_index[] = {0, 1, 3, 4, 5, 6, 7, 8};
int32_t desired_ele[] = {1, 3, 4, 6, 9, 10, 5, 7};
//// DESIRED RESULTS
double desired_spmv_result[] = {87, 6, 54, 16, 36, 54, 70, 70, 173, 0};
double desired_spmv_t_result[] = {1, 18, 0, 20, 55, 54, 126, 96, 63, 90};

// TESTING MATRIX * MATRIX MULTIPLICATION
double desired_spmm_result[TESTING_MAT_SIZE][TESTING_MAT_SIZE] = {
    {1, 0, 0, 20, 0, 0, 56, 0, 0, 0},
    {0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 54, 0, 0, 0, 60},
    {0, 0, 0, 16, 0, 0, 0, 0, 0, 0},
    {0, 14, 0, 0, 25, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 36, 0, 0, 0, 160},
    {0, 0, 0, 0, 0, 0, 49, 0, 0, 0},
    {0, 10, 0, 0, 65, 0, 0, 64, 0, 0},
    {0, 0, 0, 0, 40, 0, 112, 136, 81, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 100},
};

double desired_spmm_t_result[TESTING_MAT_SIZE][TESTING_MAT_SIZE] = {
    {1, 0, 0, 4, 0, 0, 7, 0, 0, 0},
    {0, 8, 0, 0, 10, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 18, 0, 0, 0, 0},
    {4, 0, 0, 32, 0, 0, 28, 0, 0, 0},
    {0, 10, 0, 0, 50, 0, 0, 40, 0, 0},
    {0, 0, 18, 0, 0, 72, 0, 0, 0, 60},
    {7, 0, 0, 28, 0, 0, 147, 56, 63, 0},
    {0, 0, 0, 0, 40, 0, 56, 128, 72, 0},
    {0, 0, 0, 0, 0, 0, 63, 72, 81, 0},
    {0, 0, 0, 0, 0, 60, 0, 0, 0, 200}};

void check_D_VECTOR_result(D_VECTOR *comp_result, double *expected_result, char *target_comp)
{
    for (int32_t iter_d_vec = 0; iter_d_vec < comp_result->len_vector; iter_d_vec++)
    {
        assert((int32_t)comp_result->vec_elements[iter_d_vec] == (int32_t)expected_result[iter_d_vec]);
    }
    printf("%s computation passed the tests.\n", target_comp);
}

void check_D_MATRIX_result(D_MATRIX *comp_result, double expected_result[][TESTING_MAT_SIZE], char *target_comp)
{
    for (int32_t iter_row = 0; iter_row < comp_result->mat_data.num_row; iter_row++)
    {
        for (int32_t iter_col = 0; iter_col < comp_result->mat_data.num_col; iter_col++)
        {
            assert((int32_t)comp_result->matrix[iter_row][iter_col] == (int32_t)expected_result[iter_row][iter_col]);
        }
    }
    printf("%s computation passed the tests.\n", target_comp);
}
