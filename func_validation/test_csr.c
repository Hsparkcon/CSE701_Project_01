#include "test_cases.h"
#include "../include/matrix_struct.h"
#include "../include/matrix_format_convertor.h"
#include "../include/matrix_allocation_manager.h"
#include "../include/matrix_utility.h"
#include "../include/matrix_csr.h"

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

    D_VECTOR sample_d_vec = alloc_DVEC(d_vec_length);
    for (int32_t iter_vec = 0; iter_vec < sample_d_vec.len_vector; iter_vec++)
    {
        sample_d_vec.vec_elements[iter_vec] = dense_vector[iter_vec];
    }

    S_VECTOR sample_s_vec = DVEC_TO_SVEC(&sample_d_vec);

    S_MAT_COO_TRIPLET sample_coo = DENSE_TO_COO(&sample_d_mat);
    S_MAT_CSR sample_csr = COO_TO_CSR(&sample_coo);
    delete_COO(&sample_coo);

    printf("Testing CSR computations\n");

    D_VECTOR test_spmv_csr = spmv_csr(&sample_csr, &sample_d_vec);
    check_D_VECTOR_result(&test_spmv_csr, desired_spmv_result, "SpMV");
    delete_DVEC(&test_spmv_csr);

    D_VECTOR sample_spmv_t_csr = spmv_t_csr(&sample_csr, &sample_d_vec);
    check_D_VECTOR_result(&sample_spmv_t_csr, desired_spmv_t_result, "SpMV_T");
    delete_DVEC(&sample_spmv_t_csr);

    D_MATRIX sample_spmm_csr = spmm_csr(&sample_csr, &sample_d_mat);
    check_D_MATRIX_result(&sample_spmm_csr, desired_spmm_result, "SpMM");
    delete_DENSE(&sample_spmm_csr);

    D_MATRIX sample_spmm_t_csr = spmm_t_csr(&sample_csr, &sample_d_mat);
    check_D_MATRIX_result(&sample_spmm_t_csr, desired_spmm_t_result, "SpMM_T");
    delete_DENSE(&sample_spmm_t_csr);

    D_VECTOR sample_spmspv_csr = spmspv_csr(&sample_csr, &sample_s_vec);
    check_D_VECTOR_result(&sample_spmspv_csr, desired_spmv_result, "SpM_SpV");
    delete_DVEC(&sample_spmspv_csr);

    D_VECTOR sample_spmspv_t_csr = spmspv_t_csr(&sample_csr, &sample_s_vec);
    check_D_VECTOR_result(&sample_spmspv_t_csr, desired_spmv_t_result, "SpM_SpV_T");
    delete_DVEC(&sample_spmspv_t_csr);

    D_MATRIX smaple_spmspm_csr = spmspm_csr(&sample_csr, &sample_csr);
    check_D_MATRIX_result(&smaple_spmspm_csr, desired_spmm_result, "SpM_SpM");
    delete_DENSE(&smaple_spmspm_csr);

    D_MATRIX smaple_spmspm_t_csr = spmspm_t_csr(&sample_csr, &sample_csr);
    check_D_MATRIX_result(&smaple_spmspm_t_csr, desired_spmm_t_result, "SpM_SpM_T");
    delete_DENSE(&smaple_spmspm_t_csr);

    delete_DENSE(&sample_d_mat);
    delete_DVEC(&sample_d_vec);
    delete_SVEC(&sample_s_vec);
    delete_CSR(&sample_csr);

    printf("Testing CSR computations Completed\n\n");

    return 0;
}
