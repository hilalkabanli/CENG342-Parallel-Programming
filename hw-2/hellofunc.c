#include <stdio.h>
#include <hellomake.h>
#include <time.h>
#include <stdlib.h>
void myPrintHelloMake(int rows, int cols, double **matrix, double *vector, double *result) {
  for (int i = 0; i < rows; i++) {
    result[i] = 0.0;
    for (int j = 0; j < cols; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }

  return;
}
