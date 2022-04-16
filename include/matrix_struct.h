#pragma once
#include "PCH.h"

/**
    @brief struct which contains
    @param matrix_name char * - name of matrix
    @param num_col int32_t - length of column
    @param num_row int32_t - length of row
    @param num_nnz int32_t - number of none zero
*/
typedef struct matrix_information
{
    char *matrix_name;
    int32_t num_col;
    int32_t num_row;
    int32_t num_nnz;
    double matrix_sparsity;
} MATRIX_INFO;

/**
    @brief struct which contains
    @param mat_data MATRIX_INFO - Matrix information
    @param matrix double ** - pointer to 2D array
*/
typedef struct dense_matrix
{
    MATRIX_INFO mat_data;
    double **matrix;
} D_MATRIX;

/**
    @brief struct which contains
    @param col_index int32_t
    @param row_index int32_t
    @param value double
*/
typedef struct matrix_element_data
{
    int32_t col_index;
    int32_t row_index;
    double value;
} MELELMENT_DATA;

/**
    @brief struct which contains
    @param mat_data MATRIX_INFO - Matrix information
    @param mat_elements MELELMENT_DATA * - pointer array of MELELMENT_DATA
*/
typedef struct sparse_matrix_COO_triplet
{
    MATRIX_INFO mat_data;
    MELELMENT_DATA *mat_elements;
} c_COO;

/**
    @brief struct which contains
    @param index int32_t - index of value
    @param val double - value at that index
*/
typedef struct INDEX_AND_VAL
{
    int32_t index;
    double val;
} IND_VAL;

/**
    @brief struct which contains
    @param mat_data MATRIX_INFO - Matrix information
    @param row_ptr int32_t * - Pointer to row poiter array
    @param col_with_val IND_VAL * - pointer array of IND_VAL contains column index and value
*/
typedef struct sparse_matrix_CSR
{
    MATRIX_INFO mat_data;
    int32_t *row_ptr;
    IND_VAL *col_with_val;
} c_CSR;

/**
    @brief struct which contains
    @param mat_data MATRIX_INFO - Matrix information
    @param row_ptr int32_t * - Pointer to column poiter array
    @param row_with_val IND_VAL * - pointer array of IND_VAL contains row index and value
*/
typedef struct sparse_matrix_CSC
{
    MATRIX_INFO mat_data;
    int32_t *col_ptr;
    IND_VAL *row_with_val;
} c_CSC;

/**
    @brief struct which contains
    @param len_vector int32_t - length of vector
    @param vec_elements double * - pointer array of vector value
*/
typedef struct dense_vector
{
    int32_t len_vector;
    double *vec_elements;
} D_VEC;

/**
    @brief struct which contains
    @param len_vector int32_t - length of vector
    @param num_nnz int32_t - number of none zero in vector
    @param vec_elements IND_VAL * - pointer array of IND_VAL contains index and value
*/
typedef struct sparse_vector
{
    int32_t len_vector;
    int32_t num_nnz;
    double vector_sparsity;
    IND_VAL *vec_elements;
} S_VEC;