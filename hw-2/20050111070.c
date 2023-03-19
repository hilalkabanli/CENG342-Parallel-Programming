#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  
  if(argc!=4){
	printf("usage: %s <rows> <cols> <outputfilename>/n", argv[0]);
	return 1;
}
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  char *output_file = argv[3];

  // setting the seed
  int num = 20050111070;
  unsigned short var = (unsigned short) num;  
  srand(var);

  // allocate memory for the matrix
  double **matrix = (double **) malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = (double *) malloc(cols * sizeof(double));
  }

  // filling the matrix with random double values between [1.0 - 100.0]
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = ((double) rand() / RAND_MAX) * 99.0 + 1.0;
    }
  }

  // creating and allocating a random vector for matrix-vector multiplication
  double *vector = (double *) malloc(cols * sizeof(double));
  for (int i = 0; i < cols; i++) {
    vector[i] = ((double) rand() / RAND_MAX) * 99.0 + 1.0;
  }

  // matrix-vector multiplication
  double *result = (double *) malloc(rows * sizeof(double));
  myPrintHelloMake(rows, cols, matrix, vector, result);

  // writing the solution to the output file
  FILE *output = fopen(output_file, "w");
  if (output == NULL) {
    printf("Error: failed to open file '%s'\n", output_file);
    return 1;
  }

  for (int i = 0; i < rows; i++) {
    fprintf(output, "%.2f\n", result[i]);
  }

  fclose(output);

  return(0);
}
