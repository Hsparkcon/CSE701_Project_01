#pragma once
#include "PCH.h"
#include "matrix_struct.h"
#include "matrix_allocation_manager.h"
#include "matrix_format_convertor.h"

/**
    @brief
        spmv_csc multiplies sparse matrix (in CSC format) with dense vector and
        returns the result in dense vector form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param d_vec
        pointer to dense vector
    @return
        struct D_VECTOR including
        @retval int32_t len_vector
        @retval double *vec_elements
*/
D_VECTOR spmv_csc(S_MAT_CSC *s_mat, D_VECTOR *d_vec);

/**
    @brief
        spmv_t_csc transposes sparse matrix (in CSC format) and multiplies with dense vector and
        returns the result in dense vector form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param d_vec
        pointer to dense vector
    @return
        struct D_VECTOR including
        @retval int32_t len_vector
        @retval double *vec_elements
*/
D_VECTOR spmv_t_csc(S_MAT_CSC *s_mat, D_VECTOR *d_vec);

/**
    @brief
        spmm_csc multiplies sparse matrix (in CSC format) with dense matrix and
        returns the result in dense matrix form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param d_mat
        pointer to dense matrix
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_MATRIX spmm_csc(S_MAT_CSC *s_mat, D_MATRIX *d_mat);

/**
    @brief
        spmm_t_csc transposes sparse matrix (in CSC format) and multiplies with dense matrix and
        returns the result in dense matrix form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param d_mat
        pointer to dense matrix
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_MATRIX spmm_t_csc(S_MAT_CSC *s_mat, D_MATRIX *d_mat);

/**
    @brief
        spmspv_csc multiplies sparse matrix (in CSC format) with sparse vector and
        returns the result in dense matrix form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param s_vec
        pointer to sparse vector
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_VECTOR spmspv_csc(S_MAT_CSC *s_mat, S_VECTOR *s_vec);

/**
    @brief
        spmspv_t_csc transposes sparse matrix (in CSC format) and multiplies with sparse vector and
        returns the result in dense matrix form.
    @param s_mat
        pointer to sparse matrix in CSC format
    @param s_vec
        pointer to sparse vector
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_VECTOR spmspv_t_csc(S_MAT_CSC *s_mat, S_VECTOR *s_vec);

/**
    @brief
        spmspm_csc multiplies sparse matrix (in CSC format) with sparse matrix (in CSC format) and
        returns the result in dense matrix form.
    @param s_mat_1
        pointer to first sparse matrix in CSC format
    @param s_mat_2
        pointer to second sparse matrix in CSC format
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_MATRIX spmspm_csc(S_MAT_CSC *s_mat_1, S_MAT_CSC *s_mat_2);

/**
    @brief
        spmm_t_csc transposes sparse matrix (in CSC format) and
        multiplies with sparse matrix (in CSC format) and
        returns the result in dense matrix form.
    @param s_mat_1
        pointer to first sparse matrix in CSC format
    @param s_mat_2
        pointer to second sparse matrix in CSC format
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_MATRIX spmspm_t_csc(S_MAT_CSC *s_mat_1, S_MAT_CSC *s_mat_2);
