#include "include/matrix_allocation_manager.h"
#include "include/matrix_loader.h"
#include "include/matrix_format_convertor.h"
#include "include/matrix_utility.h"
#include "include/matrix_coo.h"
#include "include/matrix_csc.h"
#include "include/matrix_csr.h"

int main(int argc, char *argv[])
{

    if (argc < 4 && argc > 4)
    {
        printf(
            "The program is designed to compute Sparse Matrix related computation.\n\n"
            "First Input\n"
            "\tSpMV\t\t Sparse Matrix * Dense Vector\n"
            "\tSpMV_T\t\t Transpose-Sparse Matrix * Dense Vector\n"

            "\tSpM_SpV\t\t Sparse Matrix * Sparse Vector\n"
            "\tSpM_SpV_t\t Transpose-Sparse Matrix * Sparse Vector\n"

            "\tSpM_SpM\t\t Sparse Matrix * Sparse Matrix\n"
            "\tSpM_SpM_t\t Transpose-Sparse Matrix * Sparse Matrix\n"

            "Second Input\n"
            "\tPath to .mtx format sparse matrix file.\n"

            "Third Input\n"
            "\tPath to the second file, which matches with the operation.\n\n");

        printf(
            "Example Input\n"
            "\tproj_r.out SpMV\t\t sample_mat.mtx sample_vec.dvec\n"
            "\tproj_r.out SpMV_T\t sample_mat.mtx sample_vec.dvec\n"
            "\tproj_r.out SpM_SpV\t sample_one.mtx sample_vec.svec\n"
            "\tproj_r.out SpM_SpV_T\t sample_one.mtx sample_vec.svec\n"
            "\tproj_r.out SpM_SpM\t Transpose-Sparse Matrix * Sparse Matrix\n"
            "\tproj_r.out SpM_SpM_T\t Transpose-Sparse Matrix * Sparse Matrix\n");
        return 0;
    }

    if ((strcmp(argv[1], "SpMV") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".dvec", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }
        S_MAT_CSR input_s_mat_csr = COO_TO_CSR(&input_s_mat);
        delete_COO(&input_s_mat);

        D_VECTOR input_d_vec;
        if (load_dense_vector(argv[3], &input_d_vec) == false)
        {
            delete_CSR(&input_s_mat_csr);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        D_VECTOR result = spmv_csr(&input_s_mat_csr, &input_d_vec);
        vector_element_printer_dense(&result);

        delete_DVEC(&input_d_vec);
        delete_DVEC(&result);
        delete_CSR(&input_s_mat_csr);
    }
    else if ((strcmp(argv[1], "SpMV_T") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".dvec", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }
        S_MAT_CSR input_s_mat_csr = COO_TO_CSR(&input_s_mat);
        delete_COO(&input_s_mat);

        D_VECTOR input_d_vec;
        if (load_dense_vector(argv[3], &input_d_vec) == false)
        {
            delete_CSR(&input_s_mat_csr);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        D_VECTOR result = spmv_t_csr(&input_s_mat_csr, &input_d_vec);
        vector_element_printer_dense(&result);

        delete_DVEC(&input_d_vec);
        delete_DVEC(&result);
        delete_CSR(&input_s_mat_csr);
    }
    else if ((strcmp(argv[1], "SpM_SpV") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".svec", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }
        S_MAT_CSR input_s_mat_csr = COO_TO_CSR(&input_s_mat);
        delete_COO(&input_s_mat);

        S_VECTOR input_s_vec;
        if (load_sparse_vector(argv[3], &input_s_vec) == false)
        {
            delete_CSR(&input_s_mat_csr);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        D_VECTOR result = spmspv_csr(&input_s_mat_csr, &input_s_vec);
        vector_element_printer_dense(&result);

        delete_SVEC(&input_s_vec);
        delete_DVEC(&result);
        delete_CSR(&input_s_mat_csr);
    }
    else if ((strcmp(argv[1], "SpM_SpV_T") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".svec", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }

        S_MAT_CSR input_s_mat_csr = COO_TO_CSR(&input_s_mat);
        delete_COO(&input_s_mat);

        S_VECTOR input_s_vec;
        if (load_sparse_vector(argv[3], &input_s_vec) == false)
        {
            delete_CSR(&input_s_mat_csr);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        D_VECTOR result = spmspv_t_csr(&input_s_mat_csr, &input_s_vec);
        vector_element_printer_dense(&result);

        delete_SVEC(&input_s_vec);
        delete_DVEC(&result);
        delete_CSR(&input_s_mat_csr);
    }
    else if ((strcmp(argv[1], "SpM_SpM") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".mtx", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat_1;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat_1) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }
        S_MAT_CSR input_s_mat_csr_1 = COO_TO_CSR(&input_s_mat_1);
        delete_COO(&input_s_mat_1);

        S_MAT_COO_TRIPLET input_s_mat_2;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[3], &input_s_mat_2) == false)
        {
            delete_CSR(&input_s_mat_csr_1);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        S_MAT_CSR input_s_mat_csr_2 = COO_TO_CSR(&input_s_mat_2);
        delete_COO(&input_s_mat_2);

        D_MATRIX result = spmspm_csr(&input_s_mat_csr_1, &input_s_mat_csr_2);
        matrix_element_printer_Dense(&result);

        delete_CSR(&input_s_mat_csr_1);
        delete_CSR(&input_s_mat_csr_2);
        delete_DENSE(&result);
    }
    else if ((strcmp(argv[1], "SpM_SpM_T") == 0) && check_file_format(argv[2], ".mtx", 1) && check_file_format(argv[3], ".mtx", 2))
    {
        S_MAT_COO_TRIPLET input_s_mat_1;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[2], &input_s_mat_1) == false)
        {
            printf("ERROR IN LOADIND FIRST INPUT.\n");
            return -1;
        }

        S_MAT_CSR input_s_mat_csr_1 = COO_TO_CSR(&input_s_mat_1);
        delete_COO(&input_s_mat_1);

        S_MAT_COO_TRIPLET input_s_mat_2;
        if (load_matrix_mtx_format_by_fscanf_TRIPLET(argv[3], &input_s_mat_2) == false)
        {
            delete_CSR(&input_s_mat_csr_1);
            printf("ERROR IN LOADIND SECOND INPUT.\n");
            return -1;
        }

        S_MAT_CSR input_s_mat_csr_2 = COO_TO_CSR(&input_s_mat_2);
        delete_COO(&input_s_mat_2);

        D_MATRIX result = spmspm_t_csr(&input_s_mat_csr_1, &input_s_mat_csr_2);
        matrix_element_printer_Dense(&result);

        delete_CSR(&input_s_mat_csr_1);
        delete_CSR(&input_s_mat_csr_2);
        delete_DENSE(&result);
    }
    else
    {
        printf(
            "ERROR IN INPUT PARAMETER - RECEIVED\n"
            "First\t %s\n"
            "Second\t %s\n"
            "Third\t %s\n",
            argv[1],
            argv[2],
            argv[3]);
    }

    return 0;
}