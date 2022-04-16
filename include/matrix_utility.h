#pragma once
#include "PCH.h"
#include "matrix_struct.h"

/**
    @brief
        check_file_format checks input file format matches with the operation
    @param input
        char * - name of input file
    @param target
        char * - required format
    @return
        @retval true if input file format matches with operations
        @retval false if input file format not matches with operations
*/
bool check_file_format(char *input, char *target, int32_t input_number);

/**
    @brief
    comp_func_CSC is comparing function used by qsort to sort
    COO format before converting into CSR format matrix.
    @param e_one
        const void * - first value
    @param e_two
        const void * - second value
    @return
        @retval
        1 if row index of e_one is bigger than row index of e_two
        @retval
        -1 if row index of e_one is bigger than row index of e_two or
        indices are but the value of e_two is bigger.
*/
int32_t comp_func_CSR(const void *e_one, const void *e_two);

/**
    @brief
        comp_func_CSC is comparing function used by qsort to sort
        COO format before converting into CSC format matrix.
    @param e_one
        const void * - first value
    @param e_two
        const void * - second value
    @return
        @retval
        1 if col index of e_one is bigger than col index of e_two
        @retval
        -1 if row index of e_one is bigger than col index of e_two or
        indices are but the value of e_two is bigger.
*/
int32_t comp_func_CSC(const void *e_one, const void *e_two);

/**
    @brief
        qsort_COO uses C standard qsort() to sort COO for before converting into CSR or CSC.
    @param input_mat
        S_MAT_COO_TRIPLET * - COO format matrix to be sorted
    @param mode
        int8_t - target mode,
        0 will sort the COO matrix for CSC format,
        1 will sort the COO matrix for CSR format.
*/
void qsort_COO(S_MAT_COO_TRIPLET input_mat, int8_t mode);

/**
    @brief
        bin_search_s_vec is binary search function to search sparse vector.
    @param s_vec
        S_VECTOR * - pointer to sparse vector to be searched
    @param target_index
        int32_t - target index
    @return returns int32_t
        @retval - if exists, index of the target.
        @retval - if not exists, -1.
*/
int32_t bin_search_s_vec(S_VECTOR *s_vec, int32_t target_index);

/**
    @brief
        bin_search_s_mat is binary search function to search sparse matrix.
    @param ind_and_ele
        IND_VAL * - pointer to the array of INV_VAL to be searched.
    @param l_ptr
        int32_t - lower starting pointer in the array
    @param u_ptr
        int32_t - upper starting pointer in the array
    @param target_index
        int32_t - targeted index value

    @return returns int32_t
        @retval - if exists, index of the target.
        @retval - if not exists, -1.
*/
int32_t bin_search_s_mat(IND_VAL *ind_and_ele, int32_t l_ptr, int32_t u_ptr, int32_t target_index);

/**
    @brief
        count_none_zero counts none zero in the dense matrix.
        It is required to be used after matrix * matrix operation.
    @param d_mat
        D_MATRIX * - pointer to the dense matrix to be checked.
    @return
        returns int32_t - number of none zero in the dense matrix
*/
int32_t count_none_zero(D_MATRIX *d_mat);

/**
    @brief
        check_length checks length of two input matches.
    @param len_vector
        int32_t - length of vector.
    @param row_matrix
        int32_t - length of row
    @return bool type
        @retval true, if length matches
        @retval false, if length not matches
*/
bool check_length(int32_t len_vector, int32_t row_matrix);

/**
    @brief
        Prints elements of dense vector
    @param d_vec
        D_VECTOR * - Pointer to the dense vector
    @return
        None
*/
void vector_element_printer_dense(D_VECTOR *d_vec);

/**
    @brief
        Prints elements of sparse vector
    @param s_vec
        S_VECTOR * - Pointer to the sparse vector
    @return
        None
*/
void vector_element_printer_sparse(S_VECTOR *s_vec);

/**
    @brief
        Prints matrix information
    @param input_matrix
        MATRIX_INFO - struct MATRIX_INFO
    @return
        None
*/
void matrix_information_printer(MATRIX_INFO input_matrix);

/**
    @brief
        Prints elements of dense matrix
    @param dense_matrix
        D_MATRIX * - Pointer to the dense matrix
    @return
        None
*/
void matrix_element_printer_Dense(D_MATRIX *dense_matrix);

/**
    @brief
        Prints elements of COO format (in TRIPLET) sparse matrix
    @param sparse_matrix
        S_MAT_COO_TRIPLET * - Pointer to the COO format (in TRIPLET) sparse matrix
    @return
        None
*/
void matrix_element_printer_Triplet(S_MAT_COO_TRIPLET *sparse_matrix);

/**
    @brief
        Prints elements of COO format (in Arrays) sparse matrix
    @param sparse_matrix
        S_MAT_COO_ARRAYS * - Pointer to the COO format (in Arrays) sparse matrix
    @return
        None
*/
void matrix_element_printer_Array(S_MAT_COO_ARRAYS *sparse_matrix);

/**
    @brief
        Prints elements of CSR format sparse matrix
    @param sparse_matrix
        S_MAT_CSR * - Pointer to the CSR format sparse matrix
    @return
        None
*/
void matrix_element_printer_CSR(S_MAT_CSR *sparse_matrix);

/**
    @brief
        Prints elements of CSC format sparse matrix
    @param sparse_matrix
        S_MAT_CSC * - Pointer to the CSR format sparse matrix
    @return
        None
*/
void matrix_element_printer_CSC(S_MAT_CSC *sparse_matrix);