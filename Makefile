all: matrix sorted_array
matrix: matrix_main.cc
	g++ -o matrix matrix_main.cc

sorted_array: sorted_array_main.cc
	g++ -o sorted_array sorted_array_main.cc