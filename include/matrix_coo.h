#pragma once
#include "PCH.h"
#include "matrix_struct.h"
#include "matrix_allocation_manager.h"
#include "matrix_format_convertor.h"

/**
    @brief
        spmv_coo multiplies sparse matrix (in COO format) with dense vector and
        returns the result in dense vector form.
    @param mat_A
        pointer to sparse matrix in COO format
    @param vec_x
        pointer to dense vector
    @return
        struct D_VEC including
        @retval int32_t len_vector
        @retval double *vec_elements
*/
void spmv_coo(c_COO *mat_A, D_VEC *vec_x, D_VEC *vec_b);

/**
    @brief
        spmv_t_coo transposes sparse matrix (in COO format) and multiplies with dense vector and
        returns the result in dense vector form.
    @param mat_A
        pointer to sparse matrix in COO format
    @param vec_x
        pointer to dense vector
    @return
        struct D_VEC including
        @retval int32_t len_vector
        @retval double *vec_elements
*/
void spmv_t_coo(c_COO *mat_A, D_VEC *vec_x,  D_VEC *vec_b);

/**
    @brief
        spmm_coo multiplies sparse matrix (in COO format) with dense matrix and
        returns the result in dense matrix form.
    @param mat_A
        pointer to sparse matrix in COO format
    @param d_mat
        pointer to dense matrix
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
void spmm_coo(c_COO *mat_A, D_MATRIX *mat_B, c_COO *mat_X);

/**
    @brief
        spmm_t_coo transposes sparse matrix (in COO format) and multiplies with dense matrix and
        returns the result in dense matrix form.
    @param mat_A
        pointer to sparse matrix in COO format
    @param d_mat
        pointer to dense matrix
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
void spmm_t_coo(c_COO *mat_A, D_MATRIX *mat_B, c_COO *mat_X);
