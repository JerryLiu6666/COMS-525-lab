#include <stdio.h>
#include <mpi.h>

int main() {
    int my_rank, comm_sz;
    int token;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    if (comm_sz < 2) {
        if (my_rank == 0) {
            printf("Need at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (my_rank == 0) {
        token = 1000;
        printf("Rank 0 initialized token %d\n", token);

        printf("Rank 0 sent token %d to Rank 1\n", token);
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&token, 1, MPI_INT, comm_sz - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 0 received token %d from Rank %d\n", token, comm_sz - 1);

        printf("Final token value at Rank 0 = %d\n", token);
    }
    else {
        MPI_Recv(&token, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %d received token %d from Rank %d\n", my_rank, token, my_rank - 1);

        token = token + 1;

        if (my_rank == comm_sz - 1) {
            printf("Rank %d sent token %d to Rank 0\n", my_rank, token);
            MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        else {
            printf("Rank %d sent token %d to Rank %d\n", my_rank, token, my_rank + 1);
            MPI_Send(&token, 1, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}