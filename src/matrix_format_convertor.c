#include "../include/matrix_format_convertor.h"

D_MATRIX COO_TO_DENSE(S_MAT_COO_TRIPLET *sparse_mat)
{
    D_MATRIX temp_matrix;
    temp_matrix.mat_data = sparse_mat->mat_data;

    temp_matrix.matrix = malloc(sizeof(double *) * (size_t)temp_matrix.mat_data.num_row);
    for (int32_t length_row = 0; length_row < temp_matrix.mat_data.num_row; length_row++)
    {
        temp_matrix.matrix[length_row] = calloc((size_t)temp_matrix.mat_data.num_col, sizeof(double));
    }

    for (int32_t track_nnz = 0; track_nnz < sparse_mat->mat_data.num_nnz; track_nnz++)
    {
        int32_t row = sparse_mat->mat_elements->row_index;
        int32_t col = sparse_mat->mat_elements->col_index;
        double val = sparse_mat->mat_elements->value;
        temp_matrix.matrix[row][col] = val;
    }

    return temp_matrix;
}

S_MAT_COO_TRIPLET DENSE_TO_COO(D_MATRIX *d_mat)
{

    S_MAT_COO_TRIPLET temp_matrix = alloc_COO(&d_mat->mat_data);

    int32_t index_nnz = 0;
    for (int32_t row = 0; row < d_mat->mat_data.num_row; row++)
    {
        for (int32_t col = 0; col < d_mat->mat_data.num_col; col++)
        {
            if (d_mat->matrix[row][col] != 0)
            {
                temp_matrix.mat_elements[index_nnz] =
                    (MELELMENT_DATA){col, row, d_mat->matrix[row][col]};
                index_nnz++;
            }
        }
    }

    return temp_matrix;
}

S_MAT_CSR COO_TO_CSR(S_MAT_COO_TRIPLET *s_mat)
{

    qsort_COO(*s_mat, 1); // not necessary if COO data read from .mtx directly

    S_MAT_CSR temp_matrix = alloc_CSR(&s_mat->mat_data);

    int32_t track_row_ind = -1;
    int32_t row_ptr_index = 0;
    for (int32_t iter_NNZ = 0; iter_NNZ < s_mat->mat_data.num_nnz; iter_NNZ++)
    {
        if (track_row_ind != s_mat->mat_elements[iter_NNZ].row_index)
        {
            track_row_ind = s_mat->mat_elements[iter_NNZ].row_index; // update current row index
            temp_matrix.row_ptr[row_ptr_index] = iter_NNZ;           // row pointer == numbers of nnz before row update
            row_ptr_index++;
        }

        temp_matrix.col_with_val[iter_NNZ] = (IND_VAL){
            s_mat->mat_elements[iter_NNZ].col_index,
            s_mat->mat_elements[iter_NNZ].value};
    }
    temp_matrix.row_ptr[s_mat->mat_data.num_row] = s_mat->mat_data.num_nnz;
    // Assign Last element for row_ptr, it needs to be NNZ.

    return temp_matrix;
}

S_MAT_CSC COO_TO_CSC(S_MAT_COO_TRIPLET *s_mat)
{

    /*
        Matrix should be sorted first as COO stored in .mtx format is sorted in ROW index
        For CSC, it COO needs to be sorted in COLUMN index
    */
    qsort_COO(*s_mat, 0);

    S_MAT_CSC temp_matrix = alloc_CSC(&s_mat->mat_data);

    uint32_t track_col_ind = NULL;
    uint32_t col_ptr_index = 0;
    for (int32_t iter_NNZ = 0; iter_NNZ < s_mat->mat_data.num_nnz; iter_NNZ++)
    {
        if (track_col_ind != s_mat->mat_elements[iter_NNZ].col_index)
        {
            track_col_ind = s_mat->mat_elements[iter_NNZ].col_index; // update current col index
            temp_matrix.col_ptr[col_ptr_index] = iter_NNZ;           // col pointer == numbers of nnz before col update
            col_ptr_index++;
        }

        temp_matrix.row_with_val[iter_NNZ] = (IND_VAL){
            s_mat->mat_elements[iter_NNZ].row_index,
            s_mat->mat_elements[iter_NNZ].value};
    }
    temp_matrix.col_ptr[s_mat->mat_data.num_col] = s_mat->mat_data.num_nnz;
    // Assign Last element for col_ptr, it needs to be NNZ.

    return temp_matrix;
}

S_MAT_COO_TRIPLET CSR_TO_COO(S_MAT_CSR *s_mat)
{

    S_MAT_COO_TRIPLET temp_matrix = alloc_COO(&s_mat->mat_data);

    int32_t track_nnz = 0;
    for (int32_t iter_row_ptr = 0; iter_row_ptr < s_mat->mat_data.num_row + 1; iter_row_ptr++)
    {
        int32_t row_ptr_diff = s_mat->row_ptr[iter_row_ptr + 1] - s_mat->row_ptr[iter_row_ptr];
        if (row_ptr_diff > 0)
        {
            for (int32_t expend_row_ptr = iter_row_ptr; expend_row_ptr < iter_row_ptr + row_ptr_diff; expend_row_ptr++)
            {
                temp_matrix.mat_elements[track_nnz].row_index = iter_row_ptr;
                track_nnz++;
            }
        }
    }

    for (int32_t iter_nnz = 0; iter_nnz < temp_matrix.mat_data.num_nnz; iter_nnz++)
    {
        temp_matrix.mat_elements[iter_nnz].col_index = s_mat->col_with_val[iter_nnz].index;
        temp_matrix.mat_elements[iter_nnz].value = s_mat->col_with_val[iter_nnz].val;
    }

    return temp_matrix;
}

S_MAT_CSC CSR_TO_CSC(S_MAT_CSR *s_mat)
{
    S_MAT_COO_TRIPLET temp_COO = CSR_TO_COO(s_mat);
    S_MAT_CSC temp_CSC = COO_TO_CSC(&temp_COO);
    delete_COO(&temp_COO);

    return temp_CSC;
}

S_MAT_COO_TRIPLET CSC_TO_COO(S_MAT_CSC *s_mat)
{

    S_MAT_COO_TRIPLET temp_matrix = alloc_COO(&s_mat->mat_data);

    int32_t track_nnz = 0;
    for (int32_t track_col_ptr = 0; track_col_ptr < temp_matrix.mat_data.num_col + 1; track_col_ptr++)
    {
        int32_t col_ptr_diff = s_mat->col_ptr[track_col_ptr + 1] - s_mat->col_ptr[track_col_ptr];
        if (col_ptr_diff > 0)
        {
            for (int32_t expend_col_ptr = track_col_ptr; expend_col_ptr < track_col_ptr + col_ptr_diff; expend_col_ptr++)
            {
                temp_matrix.mat_elements[track_nnz].col_index = track_col_ptr;
                track_nnz++;
            }
        }
    }

    for (int32_t iter_nnz = 0; iter_nnz < temp_matrix.mat_data.num_nnz; iter_nnz++)
    {
        temp_matrix.mat_elements[iter_nnz].row_index = s_mat->row_with_val[iter_nnz].index;
        temp_matrix.mat_elements[iter_nnz].value = s_mat->row_with_val[iter_nnz].val;
    }

    qsort_COO(temp_matrix, 1);

    return temp_matrix;
}

S_MAT_CSR CSC_TO_CSR(S_MAT_CSC *s_mat)
{
    S_MAT_COO_TRIPLET temp_COO = CSC_TO_COO(s_mat);
    S_MAT_CSR temp_CSR = COO_TO_CSR(&temp_COO);
    delete_COO(&temp_COO);

    return temp_CSR;
}

S_VECTOR DVEC_TO_SVEC(D_VECTOR *d_vec)
{
    S_VECTOR temp_svec = alloc_SVEC(d_vec);

    int32_t track_nnz = 0;
    for (int32_t iter_dvec = 0; iter_dvec < d_vec->len_vector; iter_dvec++)
    {
        if (d_vec->vec_elements[iter_dvec] != 0)
        {
            temp_svec.vec_elements[track_nnz] = (IND_VAL){
                iter_dvec,
                d_vec->vec_elements[iter_dvec]};
            track_nnz++;
        }
    }
    return temp_svec;
}