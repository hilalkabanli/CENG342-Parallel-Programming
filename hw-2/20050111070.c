//HİLAL KABANLI 20050111070

#include <hellomake.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    int size_large = atoi(argv[1]);
    int size_small = atoi(argv[2]);
    int rank, numproc;
    double *large = NULL, *small = NULL, *vector = NULL, *result = NULL;
    double start_time, end_time; 
    long int myID = 20050111070;
    srand(myID);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);

    if (rank == 0) {     
      
        
        result = (double *) malloc(size_large* sizeof(double));
        large = (double *) malloc(size_large * size_large * sizeof(double));
        for (int i = 0; i < size_large; i++) {
            for (int j = 0; j < size_large; j++) {
                large[i * size_large+ j] = rand() / (double) RAND_MAX;
            }
        }
        small = (double *) malloc(size_small * size_small * sizeof(double));
        for (int i = 0; i < size_small; i++) {
            for (int j = 0; j < size_small; j++) {
                small[i * size_small + j] = rand() / (double) RAND_MAX;
            }
        }
        vector = (double *) malloc(size_large * sizeof(double));
        for (int i = 0; i < size_large; i++) {
            vector[i] = rand() / (double) RAND_MAX;
        }
    }

    start_time = MPI_Wtime();
    MPI_Bcast(vector, size_large, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int block_size = size_large / numproc;
    double *sub_large_matrix = (double *) malloc(block_size * size_large * sizeof(double));
    double *sub_result = (double *) malloc(block_size * sizeof(double));


    MPI_Scatter(large, block_size * size_large, MPI_DOUBLE,
                sub_large_matrix, block_size * size_large, MPI_DOUBLE,
                0, MPI_COMM_WORLD);

    
    for (int i = 0; i < block_size; i++) {
        sub_result[i] = 0.0;
        for (int j = 0; j < size_large; j++) {
            sub_result[i] += sub_large_matrix[i * size_large + j] * vector[j];
        }
    }

   
    MPI_Gather(sub_result, block_size, MPI_DOUBLE,
               result, block_size, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    if (rank == 0) {
       
        myPrintHelloMake(small, result, vector, size_small);

        // Print elapsed time
        printf("Elapsed time: %f seconds for parallel mxv with %d processes\n", end_time - start_time, numproc);

        // Free memory
        free(large);
        free(small);
        free(vector);
        free(result);
        free(sub_large_matrix);
        free(sub_result);
    }

    MPI_Finalize();
    return 0;
}
