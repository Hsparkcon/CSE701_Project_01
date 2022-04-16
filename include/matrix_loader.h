#pragma once
#include "PCH.h"
#include "matrix_struct.h"

/**
    @brief
        load_matrix_mtx_format_by_fscanf_TRIPLET loads .mtx file into COO format sparse matrix.
    @param[in] file_path
        path to the .mtx file location
    @param[out] s_matrix_coo
        S_MAT_COO_TRIPLET which contains a pointer that will be assigned to the loaded data
    @return
        @retval true if the load is succeed
        @retval false if the load is succeed
*/
bool load_matrix_mtx_format_by_fscanf_TRIPLET(char *file_path, S_MAT_COO_TRIPLET *s_matrix_coo);

/**
    @brief
        load_matrix_mtx_format_by_fscanf_TRIPLET loads .mtx file into COO format sparse matrix.
        It uses three separate arrays which is expected to show low performance compares to the other loader.
    @param[in] file_path
        path to the .mtx file location
    @param[out] s_matrix_coo
        S_MAT_COO_TRIPLET which contains a pointer that will be assigned to the loaded data
    @return
        @retval true if the load is succeed
        @retval false if the load is succeed
*/
bool load_matrix_mtx_format_by_fscanf_ARRAYS(char *file_path, S_MAT_COO_ARRAYS *s_matrix_coo);

/**
    @brief
        load_dense_vector loads .dvec file into dense vector.
    @param[in] file_path
        path to the .mtx file location
    @param[out] d_vec
        D_VECTOR which contains a pointer that will be assigned to the loaded data
    @return
        @retval true if the load is succeed
        @retval false if the load is succeed
*/
bool load_dense_vector(char *file_path, D_VECTOR *d_vec);

/**
    @brief
        load_sparse_vector loads .svec file into sparse vector.
    @param[in] file_path
        path to the .mtx file location
    @param[out] s_vec
        S_VECTOR which contains a pointer that will be assigned to the loaded data
    @return
        @retval true if the load is succeed
        @retval false if the load is succeed
*/
bool load_sparse_vector(char *file_path, S_VECTOR *s_vec);