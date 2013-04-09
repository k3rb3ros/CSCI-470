/*
 * Parallel sort using threads (more specially of a list of 1000000 64 bit integers)
 * by Ryan Morris
 * Created on 04/03/13 
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdlib.h>
#include <string>

const unsigned long MAXS = 1000000;
const unsigned long THREADS = 8;
const unsigned int BLOCK = (MAXS/THREADS);

using namespace std;

struct sort_block
{
	unsigned long size;
	long data[BLOCK];
	pthread_attr_t attr;
	pthread_t tid;
};

/*Global*/
sort_block jobs[THREADS];

bool pop_data(long* data, char* filepath)
{
	unsigned long i = 0;
	ifstream inf(filepath);
	if(inf.good())
	{
		while(!inf.eof())
		{
			inf >> data[i++]; //sketch code
		}
		cout << "File Succesfully Read\n";
		inf.close();
		return true;
	}
	else
	{
		cerr << "Unable to read file\n";
		inf.close();
		return false;
	}
}

void print_data(long* data, unsigned long size)
{
	if(!(data[0] == 0))
	{
		cout << "[ ";
		for(unsigned long i=0; i < size; i++)
		{
			cout << data[i];
			if(i < (size -1)) cout << ", ";
		}
		cout << " ] "<< endl;
	}
	else cout << "Data is empty\n";
}

void fprint_data(long* data, unsigned long size, char* filepath)
{
	ofstream outf(filepath);
	for(unsigned long i=0; i<size; i++)
	{
		outf << data[i] << endl;
	}
	outf.close();
}

void split_data(long* data) //split data into equal size blocks for each thread
{
	long* block_data = NULL;
	
	for(unsigned long i=0; i<THREADS; i++)
	{
		jobs[i].size = BLOCK;
		block_data = jobs[i].data;
		for(unsigned long j=0; j<BLOCK; j++)
		{
			block_data[j] = data[(i*BLOCK)+j];
		}
	}
}

void merge(long* data, long* tmp, unsigned long left, unsigned long mid, unsigned long right)
{
	unsigned long left_end = mid-1;
	unsigned long num_elements = (right-left)+1;
	unsigned long tmp_pos = left;
	
	while((left <= left_end) && (mid<= right))
	{
		if(data[left] <= data[mid]) tmp[tmp_pos++] = data[mid++];
		else tmp[tmp_pos++] = data[mid++];
	}
	while(left <= left_end)	tmp[tmp_pos++] = data[left++];
	while(mid <= right) tmp[tmp_pos++] = data[mid++];
	for(unsigned long i=0; i<num_elements; ++i)
	{
		data[right] = tmp[right];
		right --;
	}
}

int compareLong(const void* a, const void* b)
{
	if( *(long*)a <  *(long*)b ) return -1;
	if( *(long*)a == *(long*)b ) return 0;
	if( *(long*)a >  *(long*)b ) return 1;
}

void pq_sort(long* data, unsigned long size)
{
	qsort(data, size, sizeof(long), compareLong);
}

void* worker(void *arg)
{
	sort_block* job = (sort_block*)arg; 
	long* data = job->data;
	unsigned long size = job->size;
	pq_sort(data, size);
	return 0;
}

void consolidate(long* data) //combine the sorted list from our worker threads back into the main list
{
	long* block_data = NULL;
	
	for(unsigned long i=0; i<THREADS; i++)
	{
		block_data = jobs[i].data;
		for(unsigned long j=0; j<BLOCK; j++)
		{
			data[(i*BLOCK)+j] = block_data[j];
		}
	}
}

void parQ_sort(long* data, unsigned long arr_size)
{ 
	split_data(data); //split the data into multiple chunks
	// start jobs
	for(unsigned int i=0; i<THREADS; ++i)
	{
		pthread_attr_init(&jobs[i].attr);
		pthread_create(&jobs[i].tid,&jobs[i].attr,worker,&jobs[i]);
	}
	//wait for workers to end
	for(unsigned int j=0; j<THREADS; ++j)
	{
		pthread_join(jobs[j].tid,NULL);
	}
	consolidate(data); //consoldate the sorted chunks into a single file
	pq_sort(data, arr_size); //run a final pass of qsort
}

int main(int argc, char* argv[])
{
	long data[MAXS];
	if(argc == 2)
	{
		if(pop_data(data, argv[1]))
		{
			cout << argv[1] << endl;
			parQ_sort(data, MAXS);
			fprint_data(data, MAXS, "sorted.dat");
			return 0;
		}
	}	
	return 128;
}