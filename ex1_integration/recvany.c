#include "mpi.h"
#include<stdio.h>
int main(int argc,char **argv)
{
	int buf[1];
	int myid,sz,i;
  double st,ed;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&sz);
	if(myid==0)
	{
    st=MPI_Wtime();
		for(i=0;i<(sz-1)*5;++i)
		{
			MPI_Recv(buf,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			printf("recv %d from process %d with tag %d\n",buf[0],status.MPI_SOURCE,status.MPI_TAG );
		}
    ed=MPI_Wtime();
    printf("process time=%f\n",ed-st);
	}
	else
	{
		for(i=0;i<5;++i)
		{
			buf[0]=myid*5+i;
			MPI_Send(buf,1,MPI_INT,0,i,MPI_COMM_WORLD);
		}
	}


	MPI_Finalize();
	return 0;
}

