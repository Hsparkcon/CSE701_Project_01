#include "../include/matrix_coo.h"
#include "../include/matrix_utility.h"

D_VECTOR spmv_coo(S_MAT_COO_TRIPLET *s_mat, D_VECTOR *d_vec)
{
    if (!check_length(d_vec->len_vector, s_mat->mat_data.num_row))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(d_vec->len_vector);
    for (int32_t iter_nnz = 0; iter_nnz < s_mat->mat_data.num_nnz; iter_nnz++)
    {
        result_dvec.vec_elements[s_mat->mat_elements[iter_nnz].row_index] +=
            (s_mat->mat_elements[iter_nnz].value *
             d_vec->vec_elements[s_mat->mat_elements[iter_nnz].col_index]);
    }

    return result_dvec;
}

D_VECTOR spmv_t_coo(S_MAT_COO_TRIPLET *s_mat, D_VECTOR *d_vec)
{
    if (!check_length(d_vec->len_vector, s_mat->mat_data.num_col))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(d_vec->len_vector);
    for (int32_t iter_nnz = 0; iter_nnz < s_mat->mat_data.num_nnz; iter_nnz++)
    {
        result_dvec.vec_elements[s_mat->mat_elements[iter_nnz].col_index] +=
            (s_mat->mat_elements[iter_nnz].value *
             d_vec->vec_elements[s_mat->mat_elements[iter_nnz].row_index]);
    }

    return result_dvec;
}

D_MATRIX spmm_coo(S_MAT_COO_TRIPLET *s_mat, D_MATRIX *d_mat)
{
    if (!check_length(s_mat->mat_data.num_col, d_mat->mat_data.num_row))
    {
        return (D_MATRIX){d_mat->mat_data, NULL};
    }

    qsort_COO(*s_mat, 1);

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat->mat_data.num_row,
            d_mat->mat_data.num_col,
            0,
            0});

    int32_t track_row_index = -1;
    int32_t current_row = -1;
    for (int32_t iter_nz = 0; iter_nz < s_mat->mat_data.num_nnz; iter_nz++)
    {
        if (track_row_index != s_mat->mat_elements[iter_nz].row_index)
        {
            track_row_index = s_mat->mat_elements[iter_nz].row_index;
            current_row++;
        }
        for (int32_t iter_d_col = 0; iter_d_col < d_mat->mat_data.num_col; iter_d_col++)
        {
            result_d_mat.matrix[current_row][iter_d_col] += (s_mat->mat_elements[iter_nz].value *
                                                             d_mat->matrix[s_mat->mat_elements[iter_nz].col_index][iter_d_col]);
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}

D_MATRIX spmm_t_coo(S_MAT_COO_TRIPLET *s_mat, D_MATRIX *d_mat)
{
    if (!check_length(s_mat->mat_data.num_row, d_mat->mat_data.num_row))
    {
        return (D_MATRIX){d_mat->mat_data, NULL};
    }

    qsort_COO(*s_mat, 0);

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat->mat_data.num_row,
            d_mat->mat_data.num_col,
            0,
            0});

    int32_t track_col_index = -1;
    int32_t current_col = -1;
    for (int32_t iter_nz = 0; iter_nz < s_mat->mat_data.num_nnz; iter_nz++)
    {
        if (track_col_index != s_mat->mat_elements[iter_nz].col_index)
        {
            track_col_index = s_mat->mat_elements[iter_nz].col_index;
            current_col++;
        }

        for (int32_t iter_d_col = 0; iter_d_col < d_mat->mat_data.num_col; iter_d_col++)
        {

            result_d_mat.matrix[current_col][iter_d_col] += (s_mat->mat_elements[iter_nz].value *
                                                             d_mat->matrix[s_mat->mat_elements[iter_nz].row_index][iter_d_col]);
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}
