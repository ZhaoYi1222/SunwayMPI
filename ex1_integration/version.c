#include"mpi.h"
#include<string.h>
#include<stdio.h>
int main(int argc,char **argv)
{
  int version,subversion;
  MPI_Init(&argc,&argv);
  MPI_Get_version(&version,&subversion);
  printf("version:%d.%d\n",version,subversion);

  MPI_Finalize();
  return 0;
}
