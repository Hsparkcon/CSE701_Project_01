INC_DIR = ../include/
SRC_DIR = ../src/
OBJ_DIR = ../obj/

CC = gcc-11
CFLAGS = -Wall -Wno-unused-result -std=c17 -O2



matrix_allocation_manager.o: $(SRC_DIR)matrix_allocation_manager.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_allocation_manager.c -o $(OBJ_DIR)matrix_allocation_manager.o

matrix_coo.o: $(SRC_DIR)matrix_coo.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_coo.c -o $(OBJ_DIR)matrix_coo.o

matrix_csc.o: $(SRC_DIR)matrix_csc.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_csc.c -o $(OBJ_DIR)matrix_csc.o

matrix_csr.o: $(SRC_DIR)matrix_csr.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_csr.c -o $(OBJ_DIR)matrix_csr.o

matrix_loader.o: $(SRC_DIR)matrix_loader.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_loader.c -o $(OBJ_DIR)matrix_loader.o

matrix_format_convertor.o: $(SRC_DIR)matrix_format_convertor.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_format_convertor.c -o $(OBJ_DIR)matrix_format_convertor.o

matrix_utility.o: $(SRC_DIR)matrix_utility.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)matrix_utility.c -o $(OBJ_DIR)matrix_utility.o



testing_convertor: matrix_format_convertor.o matrix_utility.o matrix_allocation_manager.o
	$(CC) test_convertor.c $(OBJ_DIR)matrix_format_convertor.o $(OBJ_DIR)matrix_utility.o $(OBJ_DIR)matrix_allocation_manager.o -o testing_convertor

testing_coo: matrix_allocation_manager.o matrix_coo.o matrix_format_convertor.o matrix_utility.o
	$(CC) test_coo.c $(OBJ_DIR)matrix_allocation_manager.o $(OBJ_DIR)matrix_coo.o $(OBJ_DIR)matrix_format_convertor.o $(OBJ_DIR)matrix_utility.o -o testing_coo

testing_csc: matrix_allocation_manager.o matrix_csc.o matrix_format_convertor.o matrix_utility.o
	$(CC) test_csc.c $(OBJ_DIR)matrix_allocation_manager.o $(OBJ_DIR)matrix_csc.o $(OBJ_DIR)matrix_format_convertor.o $(OBJ_DIR)matrix_utility.o -o testing_csc

testing_csr: matrix_allocation_manager.o matrix_csr.o matrix_format_convertor.o matrix_utility.o
	$(CC) test_csr.c $(OBJ_DIR)matrix_allocation_manager.o $(OBJ_DIR)matrix_csr.o $(OBJ_DIR)matrix_format_convertor.o $(OBJ_DIR)matrix_utility.o -o testing_csr

testing_loader: matrix_allocation_manager.o matrix_loader.o matrix_utility.o 
	$(CC) test_loader.c $(OBJ_DIR)matrix_allocation_manager.o $(OBJ_DIR)matrix_loader.o $(OBJ_DIR)matrix_utility.o -o testing_loader



run_test: testing_convertor testing_coo testing_csc testing_csr testing_loader
	./testing_convertor
	rm testing_convertor
	./testing_coo
	rm testing_coo
	./testing_csc
	rm testing_csc
	./testing_csr
	rm testing_csr
	./testing_loader
	rm testing_loader