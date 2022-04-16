#pragma once
#include "PCH.h"
#include "matrix_struct.h"
#include "matrix_utility.h"
#include "matrix_allocation_manager.h"

/**
    @brief
        DENSE_TO_COO converts dense matrix into COO format sparse matrix
    @param d_mat
        pointer to the dense matrix to be converted into sparse matrix
    @return
        struct S_MAT_COO_TRIPLET including
        @retval MATRIX_INFO mat_data - matrix information
        @retval MELELMENT_DATA *mat_elements - pointer to struct contains col, row, value data
*/
S_MAT_COO_TRIPLET DENSE_TO_COO(D_MATRIX *d_mat);

/**
    @brief
        COO_TO_DENSE converts COO format sparse matrix into Dense matrix
    @param smat
        pointer to the COO format sparse matrix to be converted into dense matrix
    @return
        struct D_MATRIX including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval double **matrix - pointer to allocated 2D array
*/
D_MATRIX COO_TO_DENSE(S_MAT_COO_TRIPLET *smat);

/**
    @brief
        COO_TO_CSR converts COO format sparse matrix into CSR format sparse matrix
    @param smat
        pointer to the COO format sparse matrix to be converted into CSR format sparse matrix
    @return
        struct S_MAT_CSR including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval int32_t *row_ptr - pointer to row pointer array
        @retval IND_VAL *col_with_val - pointer to array of INV_VAL containing column index and value
*/
S_MAT_CSR COO_TO_CSR(S_MAT_COO_TRIPLET *s_mat);

/**
    @brief
        COO_TO_CSC converts COO format sparse matrix into CSC format sparse matrix
    @param smat
        pointer to the COO format sparse matrix to be converted into CSC format sparse matrix
    @return
        struct S_MAT_CSC including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval int32_t *col_ptr - pointer to col pointer array
        @retval IND_VAL *row_with_val - pointer to array of INV_VAL containing row index and value
*/
S_MAT_CSC COO_TO_CSC(S_MAT_COO_TRIPLET *s_mat);

/**
    @brief
        CSR_TO_COO converts CSR format sparse matrix into COO format sparse matrix
    @param smat
        pointer to the CSR format sparse matrix to be converted into COO format sparse matrix
    @return
       struct S_MAT_COO_TRIPLET including
        @retval MATRIX_INFO mat_data - matrix information
        @retval MELELMENT_DATA *mat_elements - pointer to struct contains col, row, value data
*/
S_MAT_COO_TRIPLET CSR_TO_COO(S_MAT_CSR *s_mat);

/**
    @brief
        CSR_TO_CSC converts CSR format sparse matrix into CSC format sparse matrix
    @param smat
        pointer to the CSR format sparse matrix to be converted into CSC format sparse matrix
    @return
        struct S_MAT_CSC including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval int32_t *col_ptr - pointer to col pointer array
        @retval IND_VAL *row_with_val - pointer to array of INV_VAL containing row index and value
*/
S_MAT_CSC CSR_TO_CSC(S_MAT_CSR *s_mat);

/**
    @brief
        CSC_TO_COO converts CSR format sparse matrix into COO format sparse matrix
    @param smat
        pointer to the CSC format sparse matrix to be converted into COO format sparse matrix
    @return
       struct S_MAT_COO_TRIPLET including
        @retval MATRIX_INFO mat_data - matrix information
        @retval MELELMENT_DATA *mat_elements - pointer to struct contains col, row, value data
*/
S_MAT_COO_TRIPLET CSC_TO_COO(S_MAT_CSC *s_mat);

/**
    @brief
        CSC_TO_CSR converts CSC format sparse matrix into CSR format sparse matrix
    @param smat
        pointer to the CSC format sparse matrix to be converted into CSR format sparse matrix
    @return
        struct S_MAT_CSR including
        @retval MATRIX_INFO mat_data - Matrix information
        @retval int32_t *row_ptr - pointer to row pointer array
        @retval IND_VAL *col_with_val - pointer to array of INV_VAL containing col index and value
*/
S_MAT_CSR CSC_TO_CSR(S_MAT_CSC *s_mat);

/**
    @brief
        DVEC_TO_SVEC converts dense vector into sparse vector
    @param smat
        pointer to the dense vector to be converted into the sparse vector
    @return
    return S_VECTOR including
    @retval int32_t len_vector - Length of vector
    @retval int32_t num_nnz - Number of none zero
    @retval IND_VAL *vec_elements - Pointer to array of IND_VAL contains index and value.
*/
S_VECTOR DVEC_TO_SVEC(D_VECTOR *d_vec);