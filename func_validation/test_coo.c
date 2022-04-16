#include "test_cases.h"
#include "../include/matrix_struct.h"
#include "../include/matrix_format_convertor.h"
#include "../include/matrix_allocation_manager.h"
#include "../include/matrix_utility.h"
#include "../include/matrix_coo.h"

int main()
{
    MATRIX_INFO sample_mat_info;
    sample_mat_info = sample_mat_data;

    D_MATRIX sample_d_mat = alloc_DENSE(&sample_mat_info);
    for (int32_t row = 0; row < sample_d_mat.mat_data.num_row; row++)
    {
        for (int32_t col = 0; col < sample_d_mat.mat_data.num_col; col++)
        {
            sample_d_mat.matrix[row][col] = square_matrix[row][col];
        }
    }

    S_MAT_COO_TRIPLET sample_coo = DENSE_TO_COO(&sample_d_mat);

    D_VECTOR sample_d_vec = alloc_DVEC(d_vec_length);
    for (int32_t iter_vec = 0; iter_vec < sample_d_vec.len_vector; iter_vec++)
    {
        sample_d_vec.vec_elements[iter_vec] = dense_vector[iter_vec];
    }

    printf("Testing CSC computations\n");

    D_VECTOR test_spmv_coo = spmv_coo(&sample_coo, &sample_d_vec);
    check_D_VECTOR_result(&test_spmv_coo, desired_spmv_result, "SpMV");
    delete_DVEC(&test_spmv_coo);

    D_VECTOR sample_spmv_t_coo = spmv_t_coo(&sample_coo, &sample_d_vec);
    check_D_VECTOR_result(&sample_spmv_t_coo, desired_spmv_t_result, "SpMV_T");
    delete_DVEC(&sample_spmv_t_coo);

    D_MATRIX sample_spmm_coo = spmm_coo(&sample_coo, &sample_d_mat);
    check_D_MATRIX_result(&sample_spmm_coo, desired_spmm_result, "SpMM");
    delete_DENSE(&sample_spmm_coo);

    D_MATRIX sample_spmm_t_coo = spmm_t_coo(&sample_coo, &sample_d_mat);
    check_D_MATRIX_result(&sample_spmm_t_coo, desired_spmm_t_result, "SpMM_T");
    delete_DENSE(&sample_spmm_t_coo);

    delete_DENSE(&sample_d_mat);
    delete_DVEC(&sample_d_vec);
    delete_COO(&sample_coo);

    printf("Testing CSC computations Completed\n\n");

    return 0;
}
