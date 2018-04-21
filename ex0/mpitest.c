#include "mpi.h"
#include<stdio.h>
double f(double a)
{
	return 4.0/(1.0+a*a);
}
int main(int argc,int *argv[])
{
	int i,n,myid,namelen,numprocs;
	double PI=3.141592653589793238462643;
	double mypi,pi,h,sum,x;
	double startwtime,endwtime;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(processor_name,&namelen);
	printf("process %d on %s\n",myid,processor_name);
	if(myid==0)
	{
		n=10000;
		startwtime=MPI_Wtime();
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	h=1.0/(double)n;
	sum=0.0;
	for(i=myid;i<n;i+=numprocs)
	{
		x=h*((double)i+0.5);
		sum+=f(x);
	}
  mypi=h*sum;
  MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(myid==0)
  {
    endwtime=MPI_Wtime();
    printf("pi=%.16f\n",pi);
    printf("time=%f\n",endwtime-startwtime);
  }
  MPI_Finalize();
	return 0;
}
