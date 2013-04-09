/*
 * Parallel merge sort using threads (not working but hey it uses threads and compiles and runs)
 * by Ryan Morris
 * Created on 04/03/13 
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>

const unsigned long MAXS = 80;
const unsigned long THREADS = 1;
const unsigned int BLOCK = (MAXS/THREADS);

using namespace std;

struct sort_block
{
	unsigned long size;
	long data[BLOCK];
	long tmp[BLOCK];
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

void split_data(long* data) //split data into equal size blocks for each thread
{
	long* block_data = NULL;
	/*
	for(unsigned long i=0; i<THREADS; i++)
	{
		jobs[i].size = BLOCK;
		block_data = jobs[i].data;
		for(unsigned long j=0; j<BLOCK; j++)
		{
			block_data[j] = data[(i*BLOCK)+j];
		}
		//print_data(block_data, BLOCK);
	}*/
	block_data = jobs[0].data;
	for(unsigned long j=0; j<BLOCK; j++)
	{
		block_data[j] = data[j];
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

void m_sort(long* data, long* tmp, unsigned long left, unsigned long right)
{
	unsigned long mid;
	if(right > left)
	{
		mid = (right+left)/2;
		m_sort(data, tmp, left, mid);
		m_sort(data, tmp, mid+1, right);
		merge(data, tmp, left, mid+1, right);
	}
}

void* worker(void *arg)
{
	sort_block* job = (sort_block*)arg; 
	long* data = job->data;
	long* tmp = job->tmp;
	unsigned long size = job->size;
	//print_data(data, BLOCK);
	m_sort(data, tmp, 0, size); //merge sort the block given to the worker
	//print_data(data, BLOCK);
	return 0;
}

void consolidate(long* data) //combine the sorted list from our worker threads back into the main list
{
	long* block_data = NULL;
	
	/*for(unsigned long i=0; i<THREADS; i++)
	{
		block_data = jobs[i].data;
		for(unsigned long j=0; j<BLOCK; j++)
		{
			data[(i*BLOCK)+j] = block_data[j];
		}
	}*/
	block_data = jobs[0].data;
	for(unsigned long j=0; j<BLOCK; j++)
	{
		data[j] = block_data[j];
	}
}

void merge_sort(long* data, long* tmp, unsigned long arr_size)
{
	split_data(data); //split the data
	cout << "Split" << endl;
	// start jobs
	/*
	for(unsigned int i=0; i<THREADS; ++i)
	{
		pthread_attr_init(&jobs[i].attr);
		pthread_create(&jobs[i].tid,&jobs[i].attr,worker,&jobs[i]);
	}
	cout << "Threads Created" << endl;
	//wait for workers to end
	for(unsigned int j=0; j<THREADS; ++j)
	{
		pthread_join(jobs[j].tid,NULL);
	}
	*/
	pthread_attr_init(&jobs[0].attr);
	pthread_create(&jobs[0].tid,&jobs[0].attr,worker,&jobs[0]);
	pthread_join(jobs[0].tid,NULL);
	cout << "Threads done" << endl;
	consolidate(data);
	cout << "consolodated" << endl;
	m_sort(data, tmp, 0, arr_size-1); //merge sort the sorted chunks
}

int main(int argc, char* argv[])
{
	long data[MAXS];
	long tmp[MAXS];
	if(argc == 2)
	{
		if(pop_data(data, argv[1]))
		{
			cout << argv[1] << endl;
			merge_sort(data, tmp, MAXS);
			print_data(data, MAXS);
			return 0;
		}
	}	
	return 128;
}