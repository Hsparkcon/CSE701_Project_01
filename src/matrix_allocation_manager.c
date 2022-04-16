#include "../include/matrix_allocation_manager.h"

D_VECTOR alloc_DVEC(int32_t vector_length)
{
    D_VECTOR t_vec;
    t_vec.len_vector = vector_length;
    t_vec.vec_elements = (double *)calloc((size_t)vector_length, sizeof(double));

    return t_vec;
}

S_VECTOR alloc_SVEC(D_VECTOR *d_vec)
{
    S_VECTOR temp_svec;

    int32_t count_nnz = 0;
    for (int32_t iter_dvec = 0; iter_dvec < d_vec->len_vector; iter_dvec++)
    {
        if (d_vec->vec_elements[iter_dvec] != 0)
            count_nnz++;
    }

    temp_svec.len_vector = d_vec->len_vector;
    temp_svec.num_nnz = count_nnz;
    temp_svec.vector_sparsity = (double)count_nnz / d_vec->len_vector;
    temp_svec.vec_elements = (IND_VAL *)malloc(sizeof(IND_VAL) * (size_t)count_nnz);

    return temp_svec;
}

D_MATRIX alloc_DENSE(MATRIX_INFO *mat_info)
{
    D_MATRIX temp_mat;
    temp_mat.mat_data = *mat_info;
    temp_mat.matrix = malloc(sizeof(double *) * (size_t)mat_info->num_row);
    for (int32_t len_row = 0; len_row < mat_info->num_row; len_row++)
    {
        temp_mat.matrix[len_row] = calloc((size_t)mat_info->num_col, sizeof(double));
    }

    return temp_mat;
}

S_MAT_COO_TRIPLET alloc_COO(MATRIX_INFO *mat_info)
{
    S_MAT_COO_TRIPLET temp_mat;
    temp_mat.mat_data = *mat_info;
    temp_mat.mat_elements = (MELELMENT_DATA *)malloc(sizeof(MELELMENT_DATA) * (size_t)mat_info->num_nnz);

    return temp_mat;
}

S_MAT_CSR alloc_CSR(MATRIX_INFO *mat_info)
{
    S_MAT_CSR temp_mat;
    temp_mat.mat_data = *mat_info;
    temp_mat.row_ptr = (int32_t *)malloc(sizeof(int32_t) * (size_t)(mat_info->num_row + 1));
    temp_mat.col_with_val = (IND_VAL *)malloc(sizeof(IND_VAL) * (size_t)mat_info->num_nnz);

    return temp_mat;
}

S_MAT_CSC alloc_CSC(MATRIX_INFO *mat_info)
{
    S_MAT_CSC temp_mat;
    temp_mat.mat_data = *mat_info;
    temp_mat.col_ptr = (int32_t *)malloc(sizeof(int32_t) * (size_t)(mat_info->num_col + 1));
    temp_mat.row_with_val = (IND_VAL *)malloc(sizeof(IND_VAL) * (size_t)mat_info->num_nnz);

    return temp_mat;
}

void delete_DVEC(D_VECTOR *d_vec)
{
    free(d_vec->vec_elements);
    d_vec->vec_elements = NULL;
}

void delete_SVEC(S_VECTOR *s_vec)
{
    free(s_vec->vec_elements);
    s_vec->vec_elements = NULL;
}

void delete_DENSE(D_MATRIX *dense_matrix)
{
    for (int32_t track_row = 0; track_row < dense_matrix->mat_data.num_row; track_row++)
    {
        free(dense_matrix->matrix[track_row]);
    }
    free(dense_matrix->matrix);
}

void delete_COO(S_MAT_COO_TRIPLET *sparse_mat)
{
    free(sparse_mat->mat_elements);
}

void delete_CSR(struct sparse_matrix_CSR *sparse_mat)
{
    free(sparse_mat->row_ptr);
    free(sparse_mat->col_with_val);
}

void delete_CSC(struct sparse_matrix_CSC *sparse_mat)
{
    free(sparse_mat->col_ptr);
    free(sparse_mat->row_with_val);
}
