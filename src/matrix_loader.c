#include "../include/matrix_loader.h"

bool load_matrix_mtx_format_by_fscanf_TRIPLET(char *file_path, S_MAT_COO_TRIPLET *s_matrix_coo)
{
    FILE *load_mtx;

    load_mtx = fopen(file_path, "r");
    if (load_mtx == NULL)
    {
        printf("Failed to open file\n");
        return false;
    }

#define read_max 256
    char read_line[read_max] = {'0'};

    int32_t length_col = 0;
    int32_t length_row = 0;
    int32_t num_none_zero = 0;
    while (1)
    {
        int retrived = fgetc(load_mtx);
        if (retrived == '%')
        {
            fgets(read_line, read_max, load_mtx);
        }
        else
        {
            ungetc(retrived, load_mtx);
            fscanf(load_mtx, "%d %d %d\n", &length_col, &length_row, &num_none_zero);
            break;
        }
    }

    MELELMENT_DATA *temp_mat_element = (MELELMENT_DATA *)malloc((size_t)num_none_zero * sizeof(MELELMENT_DATA));
    if (temp_mat_element == NULL)
    {
        printf(
            "Failed to allocate memory for the matrix.\n"
            "There is not enough space to allocate %lu bytes.\n"
            "Please, try smaller matrix.\n",
            ((size_t)num_none_zero * sizeof(MELELMENT_DATA)));
        return false;
    }

    for (int32_t i = 0; i < num_none_zero; i++)
    {
        fscanf(load_mtx, "%d %d %lg\n",
               &temp_mat_element[i].col_index,
               &temp_mat_element[i].row_index,
               &temp_mat_element[i].value);
        temp_mat_element[i].col_index--;
        temp_mat_element[i].row_index--;
    }

    fclose(load_mtx);

    s_matrix_coo->mat_data = (MATRIX_INFO){
        "NULL",
        length_col,
        length_row,
        num_none_zero,
        (double)num_none_zero / (length_col * length_row)};

    s_matrix_coo->mat_elements = temp_mat_element;

    return true;
}

bool load_matrix_mtx_format_by_fscanf_ARRAYS(char *file_path, S_MAT_COO_ARRAYS *s_matrix_coo)
{
    FILE *load_mtx;

    load_mtx = fopen(file_path, "r");
    if (load_mtx == NULL)
    {
        printf("Failed to open file\n");
        return false;
    }

#define read_max 256
    char read_line[read_max] = {'0'};

    int32_t length_col = 0;
    int32_t length_row = 0;
    int32_t num_none_zero = 0;
    while (1)
    {
        int retrived = fgetc(load_mtx);
        if (retrived == '%')
        {
            fgets(read_line, read_max, load_mtx);
        }
        else
        {
            ungetc(retrived, load_mtx);
            fscanf(load_mtx, "%d %d %d\n", &length_col, &length_row, &num_none_zero);
            break;
        }
    }

    int32_t *col_index = (int32_t *)malloc((size_t)num_none_zero * sizeof(int32_t));
    int32_t *row_index = (int32_t *)malloc((size_t)num_none_zero * sizeof(int32_t));
    double *value = (double *)malloc((size_t)num_none_zero * sizeof(double));

    if ((col_index == NULL) || (row_index == NULL) || (value == NULL))
    {
        printf(
            "Failed to allocate memory for the matrix.\n"
            "There is not enough space to allocate %lu bytes.\n"
            "Please, try smaller matrix.\n",
            ((size_t)num_none_zero * sizeof(MELELMENT_DATA)));
        return false;
    }

    for (int32_t i = 0; i < num_none_zero; i++)
    {
        fscanf(load_mtx, "%d %d %lg\n",
               &col_index[i],
               &row_index[i],
               &value[i]);
        col_index[i]--;
        row_index[i]--;
    }

    fclose(load_mtx);

    s_matrix_coo->mat_data = (MATRIX_INFO){
        "NULL",
        length_col,
        length_row,
        num_none_zero,
        (double)num_none_zero / (length_col * length_row)};

    s_matrix_coo->col_index = col_index;
    s_matrix_coo->row_index = row_index;
    s_matrix_coo->value = value;

    return true;
}

bool load_dense_vector(char *file_path, D_VECTOR *d_vec)
{
    FILE *load_d_vec;

    load_d_vec = fopen(file_path, "r");
    if (load_d_vec == NULL)
    {
        printf("Failed to open file\n");
        return false;
    }

#define read_max 256
    char read_line[read_max] = {'0'};

    int32_t num_none_zero = 0;
    int32_t vector_length = 0;
    while (1)
    {
        int retrived = fgetc(load_d_vec);
        if (retrived == '%')
        {
            fgets(read_line, read_max, load_d_vec);
        }
        else
        {
            ungetc(retrived, load_d_vec);
            fscanf(load_d_vec, "%d %d\n", &num_none_zero, &vector_length);
            break;
        }
    }

    double *temp_d_vec_element = (double *)malloc((size_t)vector_length * sizeof(double));
    if (temp_d_vec_element == NULL)
    {
        printf(
            "Failed to allocate memory for the matrix.\n"
            "There is not enough space to allocate %lu bytes.\n"
            "Please, try smaller matrix.\n",
            ((size_t)vector_length * sizeof(double)));
        return false;
    }

    for (int32_t i = 0; i < vector_length; i++)
    {
        fscanf(load_d_vec, "%lg\n", &temp_d_vec_element[i]);
    }

    fclose(load_d_vec);

    d_vec->len_vector = vector_length;
    d_vec->vec_elements = temp_d_vec_element;

    return true;
}

bool load_sparse_vector(char *file_path, S_VECTOR *s_vec)
{
    FILE *load_s_vec;

    load_s_vec = fopen(file_path, "r");
    if (load_s_vec == NULL)
    {
        printf("Failed to open file\n");
        return false;
    }

#define read_max 256
    char read_line[read_max] = {'0'};

    int32_t num_none_zero = 0;
    int32_t vector_length = 0;
    while (1)
    {
        int retrived = fgetc(load_s_vec);
        if (retrived == '%')
        {
            fgets(read_line, read_max, load_s_vec);
        }
        else
        {
            ungetc(retrived, load_s_vec);
            fscanf(load_s_vec, "%d %d\n", &num_none_zero, &vector_length);
            break;
        }
    }

    IND_VAL *temp_s_vec_element = (IND_VAL *)malloc((size_t)num_none_zero * sizeof(IND_VAL));
    if (temp_s_vec_element == NULL)
    {
        printf(
            "Failed to allocate memory for the matrix.\n"
            "There is not enough space to allocate %lu bytes.\n"
            "Please, try smaller matrix.\n",
            ((size_t)num_none_zero * sizeof(IND_VAL)));
        return false;
    }

    for (int32_t i = 0; i < num_none_zero; i++)
    {
        fscanf(load_s_vec, "%d %lg\n", &temp_s_vec_element[i].index, &temp_s_vec_element[i].val);
        temp_s_vec_element[i].index--;
    }

    fclose(load_s_vec);

    s_vec->len_vector = vector_length;
    s_vec->num_nnz = num_none_zero;
    s_vec->vector_sparsity = (double)num_none_zero / vector_length;
    s_vec->vec_elements = temp_s_vec_element;
    return true;
}