#include "../include/matrix_csc.h"
#include "../include/matrix_utility.h"


void spmv_csc(const S_MAT_CSC *A, D_VECTOR *x, double *d) 
{
    if (!check_length(d_vec->len_vector, s_mat->mat_data.num_col))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(d_vec->len_vector);
    for (int32_t col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_col; iter_col_ptr++)
    {
        int32_t number_nnz_in_row = s_mat->col_ptr[iter_col_ptr + 1] - s_mat->col_ptr[iter_col_ptr];
        if (diff > 0)
        {
            int32_t start_row = s_mat->col_ptr[iter_col_ptr];
            int32_t end_row = start_row + number_nnz_in_row
            for (int32_t idx iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {
                result_dvec.vec_elements[s_mat->row_with_val[iter_nnz].index] += (A[iter_nnz].val *
                    x[idx];            }
        }
    }

    return result_dvec;
}

typedef int32_t  INT
D_VECTOR spmv_t_csc(S_MAT_CSC *s_mat, D_VECTOR *d_vec)
{
    if (!check_length(d_vec->len_vector, s_mat->mat_data.num_col))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(d_vec->len_vector);

    for (int32_t iter_col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_col; iter_col_ptr++)
    {
        int32_t diff = s_mat->col_ptr[iter_col_ptr + 1] - s_mat->col_ptr[iter_col_ptr];
        if (diff > 0)
        {
            int32_t start_p = s_mat->col_ptr[iter_col_ptr];
            int32_t end_p = start_p + diff;
            for (int32_t iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {
                result_dvec.vec_elements[iter_col_ptr] += (s_mat->row_with_val[iter_nnz].val *
                                                           d_vec->vec_elements[s_mat->row_with_val[iter_nnz].index]);
            }
        }
    }

    return result_dvec;
}

D_MATRIX spmm_csc(S_MAT_CSC *s_mat, D_MATRIX *d_mat)
{
    if (!check_length(s_mat->mat_data.num_col, d_mat->mat_data.num_row))
    {
        return (D_MATRIX){d_mat->mat_data, NULL};
    }

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat->mat_data.num_row,
            d_mat->mat_data.num_col,
            0,
            0});

    for (int32_t iter_col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_col; iter_col_ptr++)
    {
        int32_t start_p = s_mat->col_ptr[iter_col_ptr];
        int32_t end_p = s_mat->col_ptr[iter_col_ptr + 1];
        if (end_p > start_p)
        {
            for (int32_t iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {
                for (int32_t iter_d_mat_col = 0; iter_d_mat_col < d_mat->mat_data.num_col; iter_d_mat_col++)
                {
                    result_d_mat.matrix[s_mat->row_with_val[iter_nnz].index][iter_d_mat_col] += (s_mat->row_with_val[iter_nnz].val *
                                                                                                 d_mat->matrix[iter_col_ptr][iter_d_mat_col]);
                }
            }
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}

D_MATRIX spmm_t_csc(S_MAT_CSC *s_mat, D_MATRIX *d_mat)
{
    if (!check_length(s_mat->mat_data.num_row, d_mat->mat_data.num_row))
    {
        return (D_MATRIX){d_mat->mat_data, NULL};
    }

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat->mat_data.num_col,
            d_mat->mat_data.num_col,
            0,
            0});

    for (int32_t iter_col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_col; iter_col_ptr++)
    {
        int32_t start_p = s_mat->col_ptr[iter_col_ptr];
        int32_t end_p = s_mat->col_ptr[iter_col_ptr + 1];
        if (end_p > start_p)
        {

            for (int32_t iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {
                for (int32_t iter_d_mat_col = 0; iter_d_mat_col < d_mat->mat_data.num_col; iter_d_mat_col++)
                {
                    result_d_mat.matrix[iter_col_ptr][iter_d_mat_col] += (s_mat->row_with_val[iter_nnz].val *
                                                                          d_mat->matrix[s_mat->row_with_val[iter_nnz].index][iter_d_mat_col]);
                }
            }
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}

D_VECTOR spmspv_csc(S_MAT_CSC *s_mat, S_VECTOR *s_vec)
{
    if (!check_length(s_vec->len_vector, s_mat->mat_data.num_col))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(s_vec->len_vector);
    for (int32_t iter_col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_col; iter_col_ptr++)
    {
        int32_t diff = s_mat->col_ptr[iter_col_ptr + 1] - s_mat->col_ptr[iter_col_ptr];
        if (diff > 0)
        {
            int32_t start_p = s_mat->col_ptr[iter_col_ptr];
            int32_t end_p = start_p + diff;
            for (int32_t iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {
                int32_t indexing_s_vec = bin_search_s_vec(s_vec, iter_col_ptr);
                if (indexing_s_vec != -1)
                {
                    result_dvec.vec_elements[s_mat->row_with_val[iter_nnz].index] += (s_mat->row_with_val[iter_nnz].val *
                                                                                      s_vec->vec_elements[indexing_s_vec].val);
                }
            }
        }
    }

    return result_dvec;
}

D_VECTOR spmspv_t_csc(S_MAT_CSC *s_mat, S_VECTOR *s_vec)
{
    if (!check_length(s_vec->len_vector, s_mat->mat_data.num_row))
    {
        return (D_VECTOR){0, NULL};
    }

    D_VECTOR result_dvec = alloc_DVEC(s_vec->len_vector);
    for (int32_t iter_col_ptr = 0; iter_col_ptr < s_mat->mat_data.num_row; iter_col_ptr++)
    {
        int32_t start_p = s_mat->col_ptr[iter_col_ptr];
        int32_t end_p = s_mat->col_ptr[iter_col_ptr + 1];
        if (end_p > start_p)
        {
            for (int32_t iter_nnz = start_p; iter_nnz < end_p; iter_nnz++)
            {

                int32_t indexing_s_vec = bin_search_s_vec(s_vec, s_mat->row_with_val[iter_nnz].index);

                if (indexing_s_vec != -1)
                {
                    result_dvec.vec_elements[iter_col_ptr] += (s_mat->row_with_val[iter_nnz].val * s_vec->vec_elements[indexing_s_vec].val);
                }
            }
        }
    }

    return result_dvec;
}

D_MATRIX spmspm_csc(S_MAT_CSC *s_mat_1, S_MAT_CSC *s_mat_2)
{
    if (!check_length(s_mat_1->mat_data.num_col, s_mat_2->mat_data.num_row))
    {
        return (D_MATRIX){s_mat_1->mat_data, NULL};
    }

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat_1->mat_data.num_row,
            s_mat_2->mat_data.num_col,
            0,
            0});

    for (int32_t iter_c_ptr_1 = 0; iter_c_ptr_1 < s_mat_1->mat_data.num_col; iter_c_ptr_1++)
    {
        int32_t start_p_1 = s_mat_1->col_ptr[iter_c_ptr_1];
        int32_t end_p_1 = s_mat_1->col_ptr[iter_c_ptr_1 + 1];
        for (int32_t iter_nz_1 = start_p_1; iter_nz_1 < end_p_1; iter_nz_1++)
        {
            for (int32_t iter_c_ptr_2 = 0; iter_c_ptr_2 < s_mat_2->mat_data.num_col; iter_c_ptr_2++)
            {
                int32_t start_p_2 = s_mat_2->col_ptr[iter_c_ptr_2];
                int32_t end_p_2 = s_mat_2->col_ptr[iter_c_ptr_2 + 1];
                int32_t target_index = bin_search_s_mat(s_mat_2->row_with_val, start_p_2, end_p_2, iter_c_ptr_1);
                if (target_index != -1)
                {
                    result_d_mat.matrix[s_mat_1->row_with_val[iter_nz_1].index][iter_c_ptr_2] += (s_mat_1->row_with_val[iter_nz_1].val *
                                                                                                  s_mat_2->row_with_val[target_index].val);
                }
            }
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}

D_MATRIX spmspm_t_csc(S_MAT_CSC *s_mat_1, S_MAT_CSC *s_mat_2)
{
    if (!check_length(s_mat_1->mat_data.num_row, s_mat_2->mat_data.num_row))
    {
        return (D_MATRIX){s_mat_1->mat_data, NULL};
    }

    D_MATRIX result_d_mat = alloc_DENSE(
        &(MATRIX_INFO){
            "NULL",
            s_mat_1->mat_data.num_col,
            s_mat_2->mat_data.num_col,
            0,
            0});

    for (int32_t iter_c_ptr_1 = 0; iter_c_ptr_1 < s_mat_1->mat_data.num_col; iter_c_ptr_1++)
    {
        int32_t start_p_1 = s_mat_1->col_ptr[iter_c_ptr_1];
        int32_t end_p_1 = s_mat_1->col_ptr[iter_c_ptr_1 + 1];
        for (int32_t iter_nz_1 = start_p_1; iter_nz_1 < end_p_1; iter_nz_1++)
        {
            for (int32_t iter_c_ptr_2 = 0; iter_c_ptr_2 < s_mat_2->mat_data.num_col; iter_c_ptr_2++)
            {
                int32_t start_p_2 = s_mat_2->col_ptr[iter_c_ptr_2];
                int32_t end_p_2 = s_mat_2->col_ptr[iter_c_ptr_2 + 1];
                int32_t target_index = bin_search_s_mat(s_mat_2->row_with_val, start_p_2, end_p_2, s_mat_1->row_with_val[iter_nz_1].index);
                if (target_index != -1)
                {
                    result_d_mat.matrix[iter_c_ptr_1][iter_c_ptr_2] += (s_mat_1->row_with_val[iter_nz_1].val *
                                                                        s_mat_2->row_with_val[target_index].val);
                }
            }
        }
    }

    result_d_mat.mat_data.num_nnz = count_none_zero(&result_d_mat);

    return result_d_mat;
}
