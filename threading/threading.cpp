/*
 * Parallel sort (using threads)
 * by Ryan Morris
 * Created on 04/03/13 
 */

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <vector>

using namespace std;

bool pop_data(vector<long> &data, char* filepath)
{
	long t = -1;
	ifstream inf(filepath);
	if(inf.good())
	{
		while(inf.good())
		{
			inf >> t;
			data.push_back(t);
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

void print_data(vector<long> &data)
{
	vector<long>::iterator iterate_this;
	if(!data.empty())
	{
		iterate_this = data.begin();
		cout << "Contents of data file\n";
		for(int i=0; i < data.size(); i++)
		{
			cout << *iterate_this << endl;
			iterate_this ++;
		}
		cout << "Done\n";
	}
	else cout << "Data is empty\n";
}

void vctr_swap(vector<long> &data, int i1, int i2)
{
	int temp = 0;
	temp = data[i1];
	data[i1] = data[i2];
	data[i2] = temp;
}

/*
void merge(long, long, long);

void merge_sort(long low, long high)
{
	long mid;
	if(low<high)
	{
		mid=(low+high)/2;
		merge_sort(low,mid);//parallelize me
		merge_sort(mid+1,high);
		merge(low,mid,high);
	}
}
*/


int main(int argc, char* argv[])
{
	vector<long> data;
	pthread_t tid;
	pthread_attr_t attr;
	if(argc == 2)
	{
		pop_data(data, argv[1]);
		cout << argv[1] << endl;
		print_data(data);
		return 0;
	}
	
	return 128;
}