INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/

CC = gcc-11
CFLAGS = -Wall -Wextra -Wconversion -Wpedantic -Wno-unused-result -std=c17 -O2



matrix_allocation_manager.o: $(SRC_DIR)matrix_allocation_manager.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_allocation_manager.c -o $(OBJ_DIR)matrix_allocation_manager.o

matrix_coo.o: $(SRC_DIR)matrix_coo.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_coo.c -o $(OBJ_DIR)matrix_coo.o

matrix_csc.o: $(SRC_DIR)matrix_csc.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_csc.c -o $(OBJ_DIR)matrix_csc.o

matrix_csr.o: $(SRC_DIR)matrix_csr.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_csr.c -o $(OBJ_DIR)matrix_csr.o

matrix_format_convertor.o: $(SRC_DIR)matrix_format_convertor.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_format_convertor.c -o $(OBJ_DIR)matrix_format_convertor.o

matrix_loader.o: $(SRC_DIR)matrix_loader.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_loader.c -o $(OBJ_DIR)matrix_loader.o

matrix_utility.o: $(SRC_DIR)matrix_utility.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_utility.c -o $(OBJ_DIR)matrix_utility.o



main: matrix_allocation_manager.o matrix_coo.o matrix_csc.o matrix_csr.o matrix_format_convertor.o matrix_loader.o matrix_utility.o
	$(CC) main.c $(OBJ_DIR)matrix_allocation_manager.o $(OBJ_DIR)matrix_coo.o $(OBJ_DIR)matrix_csc.o $(OBJ_DIR)matrix_csr.o $(OBJ_DIR)matrix_format_convertor.o $(OBJ_DIR)matrix_loader.o $(OBJ_DIR)matrix_utility.o -o proj_r.out