#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	const int limite = 10;
	MPI_Init(NULL, NULL);

	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int cont = 0;
	int partner = (my_rank + 1) % 2;
	while (cont < limite)
	{
		if (my_rank == cont % 2)
		{
			printf("Proceso %d contador en %d\n", my_rank, cont, partner);
			cont++;
			MPI_Send(&cont, 1, MPI_INT, partner, 0, MPI_COMM_WORLD);
			cont++;
		}
		else
		{
			MPI_Recv(&cont, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Proceso %d contador en %d\n", my_rank, cont);
		}
	}
	MPI_Finalize();
}