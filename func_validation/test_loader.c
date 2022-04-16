#include "test_cases.h"
#include "../include/matrix_loader.h"
#include "../include/matrix_utility.h"
#include "../include/matrix_allocation_manager.h"

int main()
{

    char *sample_mtx_path = "sample_mtx.mtx";
    char *sample_d_vec_path = "sample_dvec.dvec";
    char *sample_s_vec_path = "sample_svec.svec";

    S_MAT_COO_TRIPLET sample_mat;
    load_matrix_mtx_format_by_fscanf_TRIPLET(sample_mtx_path, &sample_mat);
    for (int32_t iter_nz = 0; iter_nz < sample_mat.mat_data.num_nnz; iter_nz++)
    {
        assert(sample_mat.mat_elements[iter_nz].col_index == coo_desired_col_ind[iter_nz]);
        assert(sample_mat.mat_elements[iter_nz].row_index == coo_desired_row_ind[iter_nz]);
        assert((int32_t)sample_mat.mat_elements[iter_nz].value == (int32_t)coo_desired_val[iter_nz]);
    }
    printf("Load COO format - in TRIPLET - passed the tests.\n");
    delete_COO(&sample_mat);

    S_MAT_COO_ARRAYS sample_mat_array;
    load_matrix_mtx_format_by_fscanf_ARRAYS(sample_mtx_path, &sample_mat_array);
    for (int32_t iter_nz = 0; iter_nz < sample_mat_array.mat_data.num_nnz; iter_nz++)
    {
        assert(sample_mat_array.col_index[iter_nz] == coo_desired_col_ind[iter_nz]);
        assert(sample_mat_array.row_index[iter_nz] == coo_desired_row_ind[iter_nz]);
        assert((int32_t)sample_mat_array.value[iter_nz] == (int32_t)coo_desired_val[iter_nz]);
    }
    printf("Load COO format - in ARRAY - passed the tests.\n");
    free(sample_mat_array.col_index);
    free(sample_mat_array.row_index);
    free(sample_mat_array.value);

    D_VECTOR sample_d_vec;
    load_dense_vector(sample_d_vec_path, &sample_d_vec);
    for (int32_t iter_vec = 0; iter_vec < sample_d_vec.len_vector; iter_vec++)
    {
        assert((int32_t)sample_d_vec.vec_elements[iter_vec] == (int32_t)dense_vector[iter_vec]);
    }
    printf("Load Dense Vector passed the tests.\n");
    delete_DVEC(&sample_d_vec);

    S_VECTOR sample_s_vec;
    load_sparse_vector(sample_s_vec_path, &sample_s_vec);
    for (int32_t iter_nz = 0; iter_nz < sample_s_vec.num_nnz; iter_nz++)
    {
        assert(sample_s_vec.vec_elements[iter_nz].index == desired_index[iter_nz]);
        assert((int32_t)sample_s_vec.vec_elements[iter_nz].val == (int32_t)desired_ele[iter_nz]);
    }
    printf("Load Sparse Vector passed the tests.\n\n");
    delete_SVEC(&sample_s_vec);

    return 0;
}