#include"mpi.h"
#include<stdio.h>
int main(int argc,char **argv)
{
  int val=30;
  int myid,sz;
  MPI_Status status;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  MPI_Comm_size(MPI_COMM_WORLD,&sz);
  if(myid==0)
  {
    printf("get val=%d\n",val);
    MPI_Send(&val,1,MPI_INT,myid+1,0,MPI_COMM_WORLD);
  }
  else
  {
    MPI_Recv(&val,1,MPI_INT,myid-1,0,MPI_COMM_WORLD,&status);
    printf("process %d get %d from process %d\n",myid,val,myid-1);
    if(myid!=sz-1)
    {
      MPI_Send(&val,1,MPI_INT,myid+1,0,MPI_COMM_WORLD);
      printf("process %d send %d to process %d\n",myid,val,myid+1);
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
