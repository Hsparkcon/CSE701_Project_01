# CSE 701 - Project 1 code instruction
## Brief
- This code is designed to compute the following operations related to sparse matrix and prints out the results on display.
  - SpMV : Sparse Matrix * Dense Vector
  - SpMV_T : Transpose-Sparse Matrix * Dense Vector
  - SpM_SpV : Sparse Matrix * Sparse Vector
  - SpM_SpV_T : Transpose-Sparse Matrix * Sparse Vector
  - SpM_SpM : Sparse Matrix * Sparse Matrix
  - SpM_SpM_T : Transpose-Sparse Matrix * Sparse Matrix


- This code can be used with following inputs
  - .mtx : Standard COO sparse matrix format. 

    ​			For more information [link](https://math.nist.gov/MatrixMarket/formats.html) 

    ​		    Also, to get .mtx file, please visit [SuiteSparse Matrix Collection](https://sparse.tamu.edu/)

  - .dvec : None standard dense vector format designed for the project. 

    ​			For more information check **About the non-standard input format** section.

  - .svec : None standard sparse vector format designed for the project. 

    ​			For more information check **About the non-standard input format** section.


- Limitation of the code

  - Example attached inside the package cannot show the performance advance given using **sparse matrix** as those are too small to make meaningful computation time.
  - To see the actual performance achievement, it is required to download a large-size sparse matrix from  [SuiteSparse Matrix Collection](https://sparse.tamu.edu/) and compare the difference.



## About sparse matrix
- **Sparse matrix** is used in many scientific computation applications. Especially, multiplication of a matrix with a vector. 
- As the computation gets complex and large, a method to compress the data size and minimize unnecessary memory accessing processes is required.
- One method to achieve data compression and minimization of unnecessary memory accessing is using a sparse matrix.
- Dense matrix contains every element including zero in the matrix which requires  **sizeof(double) * (column * row)** bytes in memory space, and zero value elements are generally not required for the multiplication process.
- Sparse matrix only containing non-zero elements with index information, and with a standard format **COO**, it uses **(sizeof(double) + sizeof(int32_t) + sizeof(int32_t)) * number of non-zero** bytes in memory space.
- Also, the iteration process can be reduced from **column * row** to **number of non-zero**.



## About goal of the project
- In **Project 01**, it is planned to implement the operations of **sparse matrix** computations listed above with COO, CSC and CSR format to achieve a clear understanding of the computation process.
- Also, it is planned to understand performance differences between the computation operations implemented in a specific format and hybrid format by comparing computation time.



## About directories
- The project contains following directories.
  - include : Contains header files for the project
  - src : Contains header files for the project
  - obj: Directory to separate object files from compilation process
  - func_test: Directory contains .c file for function test



## To compile the code
> In **workspace** or **CSE701_Project_01** directory, type
> 
>```bash
> make main
>```
>
> This will generate **proj_r.out** file at **workspace** or **CSE701_Project_01** directory.
> 



## To use proj_r.out
> In **workspace** or **CSE701_Project_01** directory, after generating **proj_r.out**, type
>
> ```bash
> ./proj_r.out operation input_one input_two
> ```
>
> **NOTE**
>  - following inputs can be used
> ```bash
> ./proj_r.out SpMV sample_mtx.mtx sample_dvec.dvec
> ./proj_r.out SpMV_T sample_mtx.mtx sample_dvec.dvec
> 
> ./proj_r.out SpM_SpV sample_mtx.mtx sample_svec.svec
> ./proj_r.out SpM_SpV_T sample_mtx.mtx sample_svec.svec
> 
> ./proj_r.out SpM_SpM sample_mtx.mtx sample_mtx.mtx
> ./proj_r.out SpM_SpM_T sample_mtx.mtx sample_mtx.mtx
> ```
>
> - example
> ```bash
> INPUT - ./proj_r.out SpMV sample_mtx.mtx sample_dvec.dvec
> INPUT - ./proj_r.out SpM_SpV sample_mtx.mtx sample_svec.svec
> Return - 87.00 6.00 54.00 16.00 36.00 54.00 70.00 70.00 173.00 0.00
> 
> INPUT - ./proj_r.out SpMV_T sample_mtx.mtx sample_dvec.dvec
> INPUT - ./proj_r.out SpM_SpV_T sample_mtx.mtx sample_svec.svec
> Return - 1.00 18.00 0.00 20.00 55.00 54.00 126.00 96.00 63.00 90.00
> ```
> 
>   
>   - About the operations
> 
>     - Currently, computation operation is done by using CSR - Compressed Sparse Row format for performance issues..
>   - Computation operations for COO - Coordinates format and CSC - Compressed Sparse Column format are implemented, but not used in the computation process.
>   - The operation of unused computation functions is confirmed by the separated functional testing process.



## To check operations in the project works correctly 
> In **func_test** directory, type
> 
>```bash
> make run_test
>```

> **NOTE**
>
> - The tests checks following operations
>   - Matrix converting operations
>   - COO computation operations
>   - CSC computation operations
>   - CSR computation operations
>   - Matrix loading operations
> 
> - The process must be done when there are modifications in the listed operations to check the updates do not make bugs.
> - The new operations need to be added to the process when a new operation is added to the listed operations.



## About the non-standard input format
> - Non-standard input format **.dvec** and **.svec** are designed for this project
>
> > - **.dvec**
> >   - It is designed for denoting **dense vector**.
> >
> >   - The first element in the file denotes **length of vector**.
> >
> >   - The remaining elements in the file denote **elements** in the vector.
> >
> >   - To load **length of vector** by **fscanf()**, **%d** needs to be used.
> >
> >   - To load **element** by **fscanf()**, **%lg** needs to be used.
> >
> >   - To generate **.dvec** file for operation, do the followings
> >
> >   - Generate **.txt**, write contents as follow and change the format into **.dvec**
> >
> >   >```.txt
> >   > 7
> >   > 0
> >   > 3
> >   > 1
> >   > 2
> >   > 5
> >   > 5
> >   > 8
> >   >```
> >   >
> > The above example represents dense vector with
> >   - Vector length : 7
> >   - Value : 0 3 1 2 5 5 8
> > 
> >
> > - **.svec**
> >   
> > - It is designed for denoting **sparse vector**.
> >   
> > - The first two elements in the file denotes **number of none zero** and **length of vector**.
> >   
> > - The remaining elements in the file denote **index** and **elements** in the vector.
> >   
> > - To load **number of none zero**, **length of vector** and **index** by **fscanf()**, **%d** needs to be used.
> >   
> > - To load **element** by **fscanf()**, **%lg** needs to be used.
> >   
> > - To generate **.svec** file for operation, do the followings
> >   
> > - Generate **.txt**, write contents as follow and change the format into **.dvec**
> >   
> >   >```.txt
> >   >8 10
> >   >1 1
> >   >2 3
> >   >4 4
> >   >5 6
> >   >6 9
> >   >7 10
> >   >8 5
> >   >9 7
> >   >```
> >   >
> > The above example represents sparse vector with
> >   - Vector length : 10
> >   - Number of none zero : 8
> >   - Index :  8 1 2 4 5 6  7 8 9
> >   - Value : 10 1 3 4 6 9 10 5 7