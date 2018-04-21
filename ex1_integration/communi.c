#include "mpi.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
int main(int argc,char **argv)
{
  int myid;
  MPI_Status status;
  char message[50];
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  if(myid==0)
  {
    strcpy(message,"Hello process 1");
    MPI_Send(message,strlen(message),MPI_CHAR,1,99,MPI_COMM_WORLD);
  }
  else if(myid==1)
  {
    MPI_Recv(message,40,MPI_CHAR,0,99,MPI_COMM_WORLD,&status);
    printf("process %d get %s\n",myid,message);
  }

  MPI_Finalize();
  return 0;
}
