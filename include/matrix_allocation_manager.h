#pragma once
#include "PCH.h"
#include "matrix_struct.h"

/**
    @brief
    alloc_DVEC function allocates sizeof(double) * length of vector bytes for dense vector on heap memory space.
    @param vector_length
    length of vector
    @return
    return D_VECTOR including
    @retval int32_t - length of vector
    @retval double* - pointer to the allocated array.
*/
D_VECTOR alloc_DVEC(int32_t vector_length);

/**
    @brief
    alloc_SVEC function allocates sizeof(double) * number of none zero elements in vector bytes for sparse vector on heap memory space.
    @param d_vec
    struct D_VECTOR including dense vector information
    @return
    return S_VECTOR including
    @retval int32_t - Length of vector
    @retval int32_t - Number of none zero
    @retval double* - Pointer to the allocated array.
*/
S_VECTOR alloc_SVEC(D_VECTOR *d_vec);

/**
    @brief
    alloc_DENSE function allocates sizeof(double) * (Column * Row) bytes for dense vector on heap memory space.
    @param d_vec
    struct MATRIX_INFO including required matrix information
    @return
    return struct D_MATRIX including
    @retval MATRIX_INFO - Matrix information
    @retval double ** - pointer to allocated 2D array
*/
D_MATRIX alloc_DENSE(MATRIX_INFO *mat_info);

/**
    @brief
    alloc_COO function allocates sizeof(MELELMENT_DATA) * number of none zero bytes for COO format sparse matrix on heap memory space.
    @param mat_info
    struct MATRIX_INFO including required matrix information
    @return
    return struct S_MAT_COO_TRIPLET including
    @retval MATRIX_INFO mat_data - Matrix information
    @retval MELELMENT_DATA *mat_elements - pointer to array which includes column, row, value data
*/
S_MAT_COO_TRIPLET alloc_COO(MATRIX_INFO *mat_info);

/**
    @brief
    alloc_CSR function allocates
    sizeof(IND_VAL) * number of none zero + sizeof(int32_t) * (row + 1)
    bytes for CSR format sparse matrix on heap memory space.
    @param mat_info
    struct MATRIX_INFO including required matrix information
    @return
    return struct S_MAT_CSR including
    @retval MATRIX_INFO mat_data - Matrix information
    @retval int32_t *row_ptr - pointer to row pointer
    @retval IND_VAL *col_with_val - pointer to struct array which includes column index and value
*/
S_MAT_CSR alloc_CSR(MATRIX_INFO *mat_info);

/**
    @brief
    alloc_CSC function allocates
    sizeof(IND_VAL) * number of none zero + sizeof(int32_t) * (col + 1)
    bytes for CSC format sparse matrix on heap memory space.
    @param mat_info
    struct MATRIX_INFO including required matrix information
    @return
    return struct S_MAT_CSC including
    @retval MATRIX_INFO mat_data - Matrix information
    @retval int32_t *col_ptr - pointer to row pointer
    @retval IND_VAL *row_with_val - pointer to struct array which includes row index and value
*/
S_MAT_CSC alloc_CSC(MATRIX_INFO *mat_info);

/**
    @brief
    delete_DVEC frees memory allocated for D_VECTOR and set pointer to NULL.
    @param d_vec
    Pointer to dense vector address to be delete.
    @return
    None
*/
void delete_DVEC(D_VECTOR *d_vec);

/**
    @brief
    delete_SVEC frees memory allocated for S_VECTOR and set pointer to NULL.
    @param sparse_mat
    Pointer to sparse vector address to be delete.
    @return
    None
*/
void delete_SVEC(S_VECTOR *s_vec);

/**
    @brief
    delete_DENSE frees memory allocated for D_MATRIX and set pointer to NULL.
    @param dense_matrix
    Pointer to dense matrix address to be delete.
    @return
    None
*/
void delete_DENSE(D_MATRIX *dense_matrix);

/**
    @brief
    delete_COO frees memory allocated for sparse_matrix_COO_triplet and set pointer to NULL.
    @param sparse_mat
    Pointer to coo format sparse matrix address to be delete.
    @return
    None
*/
void delete_COO(struct sparse_matrix_COO_triplet *sparse_mat);

/**
    @brief
    delete_CSR frees memory allocated for sparse_matrix_CSR and set pointer to NULL.
    @param sparse_mat
    Pointer to csr format sparse matrix address to be delete.
    @return
    None
*/
void delete_CSR(struct sparse_matrix_CSR *sparse_mat);

/**
    @brief
    delete_CSC frees memory allocated for sparse_matrix_CSC and set pointer to NULL.
    @param sparse_mat
    Pointer to csc format sparse matrix address to be delete.
    @return
    None
*/
void delete_CSC(struct sparse_matrix_CSC *sparse_mat);
