#include "test_cases.h"
#include "../include/matrix_format_convertor.h"

int main()
{
    MATRIX_INFO sample_info = (MATRIX_INFO){
        "NULL",
        TESTING_MAT_SIZE,
        TESTING_MAT_SIZE,
        18,
        0.18};

    D_MATRIX sample_den = alloc_DENSE(&sample_info);
    for (int32_t row = 0; row < sample_den.mat_data.num_row; row++)
    {
        for (int32_t col = 0; col < sample_den.mat_data.num_col; col++)
        {
            sample_den.matrix[row][col] = square_matrix[row][col];
        }
    }

    S_MAT_COO_TRIPLET sample_coo = DENSE_TO_COO(&sample_den);
    for (int32_t iter_coo = 0; iter_coo < sample_coo.mat_data.num_nnz; iter_coo++)
    {
        assert(sample_coo.mat_elements[iter_coo].col_index == coo_desired_col_ind[iter_coo]);
        assert(sample_coo.mat_elements[iter_coo].row_index == coo_desired_row_ind[iter_coo]);
        assert((int32_t)sample_coo.mat_elements[iter_coo].value == (int32_t)coo_desired_val[iter_coo]);
    }
    printf("DENSE_TO_COO passed the tests.\n");

    S_MAT_CSR sample_csr = COO_TO_CSR(&sample_coo);
    for (int32_t iter_row_ptr = 0; iter_row_ptr < sample_csr.mat_data.num_row; iter_row_ptr++)
    {
        assert(sample_csr.row_ptr[iter_row_ptr] == csr_desired_row_ptr[iter_row_ptr]);
    }
    for (int32_t iter_csr = 0; iter_csr < sample_csr.mat_data.num_nnz; iter_csr++)
    {
        assert(sample_csr.col_with_val[iter_csr].index == csr_desired_col_ind[iter_csr]);
        assert((int32_t)sample_csr.col_with_val[iter_csr].val == (int32_t)csr_desired_val[iter_csr]);
    }
    printf("COO_TO_CSR passed the tests.\n");

    S_MAT_CSC sample_csc = COO_TO_CSC(&sample_coo);
    for (int32_t iter_col_ptr = 0; iter_col_ptr < sample_csr.mat_data.num_col; iter_col_ptr++)
    {
        assert(sample_csc.col_ptr[iter_col_ptr] == csc_desired_col_ptr[iter_col_ptr]);
    }
    for (int32_t iter_csc = 0; iter_csc < sample_csc.mat_data.num_nnz; iter_csc++)
    {
        assert(sample_csc.row_with_val[iter_csc].index == csc_desired_row_ind[iter_csc]);
        assert((int32_t)sample_csc.row_with_val[iter_csc].val == (int32_t)csc_desired_val[iter_csc]);
    }
    printf("COO_TO_CSC passed the tests.\n");
    delete_COO(&sample_coo);

    S_MAT_COO_TRIPLET sample_csr_to_coo = CSR_TO_COO(&sample_csr);
    for (int32_t iter_coo = 0; iter_coo < sample_csr_to_coo.mat_data.num_nnz; iter_coo++)
    {
        assert(sample_csr_to_coo.mat_elements[iter_coo].col_index == coo_desired_col_ind[iter_coo]);
        assert(sample_csr_to_coo.mat_elements[iter_coo].row_index == coo_desired_row_ind[iter_coo]);
        assert((int32_t)sample_csr_to_coo.mat_elements[iter_coo].value == (int32_t)coo_desired_val[iter_coo]);
    }
    printf("CSR_TO_COO passed the tests.\n");
    delete_COO(&sample_csr_to_coo);

    S_MAT_CSC sample_csr_to_csc = CSR_TO_CSC(&sample_csr);
    for (int32_t iter_col_ptr = 0; iter_col_ptr < sample_csr.mat_data.num_col; iter_col_ptr++)
    {
        assert(sample_csr_to_csc.col_ptr[iter_col_ptr] == csc_desired_col_ptr[iter_col_ptr]);
    }
    for (int32_t iter_csc = 0; iter_csc < sample_csc.mat_data.num_nnz; iter_csc++)
    {
        assert(sample_csr_to_csc.row_with_val[iter_csc].index == csc_desired_row_ind[iter_csc]);
        assert((int32_t)sample_csr_to_csc.row_with_val[iter_csc].val == (int32_t)csc_desired_val[iter_csc]);
    }
    printf("CSR_TO_CSC passed the tests.\n");
    delete_CSC(&sample_csr_to_csc);
    delete_CSR(&sample_csr);

    S_MAT_COO_TRIPLET sample_csc_to_coo = CSC_TO_COO(&sample_csc);
    for (int32_t iter_coo = 0; iter_coo < sample_csc_to_coo.mat_data.num_nnz; iter_coo++)
    {
        assert(sample_csc_to_coo.mat_elements[iter_coo].col_index == coo_desired_col_ind[iter_coo]);
        assert(sample_csc_to_coo.mat_elements[iter_coo].row_index == coo_desired_row_ind[iter_coo]);
        assert((int32_t)sample_csc_to_coo.mat_elements[iter_coo].value == (int32_t)coo_desired_val[iter_coo]);
    }
    printf("CSC_TO_COO passed the tests.\n");
    delete_COO(&sample_csc_to_coo);

    S_MAT_CSR sample_csc_to_csr = CSC_TO_CSR(&sample_csc);
    for (int32_t iter_row_ptr = 0; iter_row_ptr < sample_csc_to_csr.mat_data.num_row; iter_row_ptr++)
    {
        assert(sample_csc_to_csr.row_ptr[iter_row_ptr] == csr_desired_row_ptr[iter_row_ptr]);
    }
    for (int32_t iter_csr = 0; iter_csr < sample_csc_to_csr.mat_data.num_nnz; iter_csr++)
    {
        assert(sample_csc_to_csr.col_with_val[iter_csr].index == csr_desired_col_ind[iter_csr]);
        assert((int32_t)sample_csc_to_csr.col_with_val[iter_csr].val == (int32_t)csr_desired_val[iter_csr]);
    }
    printf("CSC_TO_CSR passed the tests.\n\n");
    delete_CSR(&sample_csc_to_csr);
    delete_CSC(&sample_csc);

    return 0;
}
