#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS 8

typedef struct
{
   int a;
   int b;
   int sum;
   pthread_attr_t attr;
   pthread_t tid;
} Job;

Job jobs[THREADS];

void* worker(void *arg);

int main(int argc, char** argv)
{
   int n = atoi(argv[1]);
   
   // setup jobs
   for(int i=0; i<THREADS; ++i)
   {
      if(i==0)
      {
        jobs[i].a = 0;
        jobs[i].b = n/THREADS;
      }
      else if (i < THREADS-1)
      {
        jobs[i].a = jobs[i-1].b+1;
        jobs[i].b = ((i+1)*n)/THREADS-1;
      }
      else
      {
    	jobs[i].a = jobs[i-1].b+1;
        jobs[i].b = n;
      }
   }
   // start jobs
   for(int i=0; i<THREADS; ++i)
   {
     pthread_attr_init(&jobs[i].attr);
     pthread_create(&jobs[i].tid,&jobs[i].attr,worker,&jobs[i]);
   }
  
   //wait for workers to end
   for(int i=0; i<THREADS; ++i)
   {
     pthread_join(jobs[i].tid,NULL);
   }
   int total = 0;
   for(int i=0; i<THREADS; ++i)
   {
     total = total + jobs[i].sum;
   }

   printf("total = %d\n", total);

   return 0;
}

void* worker(void *arg)
{
  Job* job = (Job*)arg; 
  int a=job->a,b=job->b,sum=0;
  for(int i=job->a; i<=job->b; ++i)
  {
   sum += i;
  }
  job->sum = sum;
  return 0;
}
