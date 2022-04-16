#include "../include/matrix_utility.h"

bool check_file_format(char *input, char *target, int32_t input_number)
{
    char *target_ptr = strstr(input, target);

    if (target_ptr != NULL)
    {
        return true;
    }
    else
    {
        printf(
            "ERROR IN INPUT %d FILE FORMAT\n"
            "EXPECTED - %s format\n"
            "RECEIVED - %s\n\n",
            input_number,
            target,
            input);
        return false;
    }
}

int comp_func_CSR(const void *e_one, const void *e_two)
{
    MELELMENT_DATA *element_one = (MELELMENT_DATA *)e_one;
    int32_t e_one_row_ind = element_one->row_index;
    int32_t e_one_col_ind = element_one->col_index;

    MELELMENT_DATA *element_two = (MELELMENT_DATA *)e_two;
    int32_t e_two_row_ind = element_two->row_index;
    int32_t e_two_col_ind = element_two->col_index;

    if (e_one_row_ind > e_two_row_ind)
    {
        return 1;
    }
    else if (e_one_row_ind == e_two_row_ind)
    {
        return e_one_col_ind - e_two_col_ind;
    }
    else
    {
        return -1;
    }
}

int comp_func_CSC(const void *e_one, const void *e_two)
{
    MELELMENT_DATA *element_one = (MELELMENT_DATA *)e_one;
    int32_t e_one_row_ind = element_one->row_index;
    int32_t e_one_col_ind = element_one->col_index;

    MELELMENT_DATA *element_two = (MELELMENT_DATA *)e_two;
    int32_t e_two_row_ind = element_two->row_index;
    int32_t e_two_col_ind = element_two->col_index;

    if (e_one_col_ind > e_two_col_ind)
    {
        return 1;
    }
    else if (e_one_col_ind == e_two_col_ind)
    {
        return e_one_row_ind - e_two_row_ind;
    }
    else
    {
        return -1;
    }
}

void qsort_COO(S_MAT_COO_TRIPLET input_mat, int8_t mode)
{
    if (mode == 1)
    {
        qsort(
            input_mat.mat_elements,
            (size_t)input_mat.mat_data.num_nnz,
            sizeof(MELELMENT_DATA),
            comp_func_CSR);
    }
    else
    {
        qsort(
            input_mat.mat_elements,
            (size_t)input_mat.mat_data.num_nnz,
            sizeof(MELELMENT_DATA),
            comp_func_CSC);
    }
}

int32_t bin_search_s_vec(S_VECTOR *s_vec, int32_t target_index)
{
    int32_t low_ptr = 0;
    int32_t upper_ptr = s_vec->num_nnz - 1;
    int32_t mid_ptr = 0;

    while (low_ptr <= upper_ptr)
    {
        mid_ptr = (low_ptr + upper_ptr) / 2;

        if (s_vec->vec_elements[mid_ptr].index == target_index)
        {
            return mid_ptr;
        }
        else if (s_vec->vec_elements[mid_ptr].index > target_index)
        {
            upper_ptr = mid_ptr - 1;
        }
        else
        { // s_vec->vec_elements[mid_ptr].index < target_index
            low_ptr = mid_ptr + 1;
        }
    }
    return -1;
}

int32_t bin_search_s_mat(IND_VAL *ind_and_ele, int32_t l_ptr, int32_t u_ptr, int32_t target_index)
{
    int32_t low_ptr = l_ptr;
    int32_t upper_ptr = u_ptr - 1;
    int32_t mid_ptr = 0;

    if (upper_ptr == low_ptr)
    {
        if (target_index == ind_and_ele[l_ptr].index)
        {
            return l_ptr;
        }
        else
        {
            return -1;
        }
    }

    while (low_ptr <= upper_ptr)
    {
        mid_ptr = (low_ptr + upper_ptr) / 2;

        if (ind_and_ele[mid_ptr].index == target_index)
        {
            return mid_ptr;
        }
        else if (ind_and_ele[mid_ptr].index > target_index)
        {
            upper_ptr = mid_ptr - 1;
        }
        else
        { // s_vec->vec_elements[mid_ptr].index < target_index
            low_ptr = mid_ptr + 1;
        }
    }
    return -1;
}

int32_t count_none_zero(D_MATRIX *d_mat)
{
    int32_t count_nz = 0;
    for (int32_t iter_row = 0; iter_row < d_mat->mat_data.num_row; iter_row++)
    {
        for (int32_t iter_col = 0; iter_col < d_mat->mat_data.num_col; iter_col++)
        {
            if (d_mat->matrix[iter_row][iter_col] != 0)
            {
                count_nz++;
            }
        }
    }
    return count_nz;
}

bool check_length(int32_t len_vector, int32_t row_matrix)
{
    if (len_vector != row_matrix)
    {
        printf(
            "ERROR - DIMENSION MISMATCH"
            "row/column of Matrix(Input One) does not match with Length of Vector, row/column of Matrix (Input Two).\n"
            "INPUT ONE LENGTH: %d\n"
            "INPUT TWO LENGTH: %d\n",
            row_matrix,
            len_vector

        );
        return false;
    }
    return true;
}

void vector_element_printer_dense(D_VECTOR *d_vec)
{
    for (int32_t iter_vec = 0; iter_vec < d_vec->len_vector; iter_vec++)
    {
        printf("%.2lf ", d_vec->vec_elements[iter_vec]);
    }
    printf("\n\n");
}

void vector_element_printer_sparse(S_VECTOR *s_vec)
{
    printf("Index\t Val\n");
    for (int32_t iter_s_vec = 0; iter_s_vec < s_vec->num_nnz; iter_s_vec++)
    {
        printf("%d\t %lg\n", s_vec->vec_elements[iter_s_vec].index, s_vec->vec_elements[iter_s_vec].val);
    }
    printf("\n\n");
}

void matrix_information_printer(MATRIX_INFO input_matrix)
{
    printf(
        "Name of Matrix: %s\n"
        "Length of Row: %d\n"
        "Length of Column: %d\n"
        "Number of None Zero: %d\n"
        "Matrix Sparsity: %lf\n",
        input_matrix.matrix_name,
        input_matrix.num_row,
        input_matrix.num_col,
        input_matrix.num_nnz,
        input_matrix.matrix_sparsity);
}

void matrix_element_printer_Dense(D_MATRIX *dense_matrix)
{
    for (int32_t row = 0; row < dense_matrix->mat_data.num_row; row++)
    {
        for (int32_t col = 0; col < dense_matrix->mat_data.num_col; col++)
        {
            printf("%3.0lf ", dense_matrix->matrix[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_element_printer_Triplet(S_MAT_COO_TRIPLET *sparse_matrix)
{

    printf("Sparse matrix in COO Format\n");
    printf("col\t row\t element\n");
    for (int i = 0; i < sparse_matrix->mat_data.num_nnz; i++)
    {
        printf(
            "%d\t %d\t %.2lf\n",
            sparse_matrix->mat_elements[i].col_index,
            sparse_matrix->mat_elements[i].row_index,
            sparse_matrix->mat_elements[i].value);
    }
    printf("\n");
}

void matrix_element_printer_Array(S_MAT_COO_ARRAYS *sparse_matrix)
{

    printf("col\t row\t element\n");
    for (int i = 0; i < sparse_matrix->mat_data.num_nnz; i++)
    {
        printf(
            "%d\t %d\t %lf\n",
            sparse_matrix->col_index[i],
            sparse_matrix->row_index[i],
            sparse_matrix->value[i]);
    }
    printf("\n\n");
}

void matrix_element_printer_CSR(S_MAT_CSR *sparse_matrix)
{
    printf("ROW PTR:\n");
    for (int32_t track_row_ptr = 0; track_row_ptr < sparse_matrix->mat_data.num_row + 1; track_row_ptr++)
    {
        printf("%d ", sparse_matrix->row_ptr[track_row_ptr]);
    }
    printf("\n\n");

    printf("COL INDEX AND Value:\n");
    for (int32_t track_nnz = 0; track_nnz < sparse_matrix->mat_data.num_nnz; track_nnz++)
    {
        printf("%d\t %.2lf\n",
               sparse_matrix->col_with_val[track_nnz].index,
               sparse_matrix->col_with_val[track_nnz].val);
    }
    printf("\n\n");
}

void matrix_element_printer_CSC(S_MAT_CSC *sparse_matrix)
{
    printf("COL PTR:\n");
    for (int32_t track_col_ptr = 0; track_col_ptr < sparse_matrix->mat_data.num_col + 1; track_col_ptr++)
    {
        printf("%d ", sparse_matrix->col_ptr[track_col_ptr]);
    }

    printf("\n\n");

    printf("ROW INDEX and Value:\n");
    for (int32_t track_nnz = 0; track_nnz < sparse_matrix->mat_data.num_nnz; track_nnz++)
    {
        printf("%d\t %.2lf\n",
               sparse_matrix->row_with_val[track_nnz].index,
               sparse_matrix->row_with_val[track_nnz].val);
    }

    printf("\n\n");
}
