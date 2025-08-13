#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
class test1
{
	enum {num_of_elements = 1000000};
	enum {rand_max = 1000000};
	enum {left_child_index = 1};
	enum {start_index = 0};
	int* data;
	void generate_data(int value);
	void dump();
	void swap(int* a, int* b);
	void build_heap(int n, int i);
public:	
	test1();
	void sort1();
	void sort2();
	~test1();
};
void test1::generate_data(int value)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < num_of_elements; i++)
		*(data + i) = rand() % (value + 1);
}
void test1::dump()
{
        int i;
        for (i = 0; i < num_of_elements; i++)
                printf("[%d]%s", *(data + i), i == num_of_elements - 1 ? "\n" : " ");
}
void test1::swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void test1::build_heap(int n, int i)
{
    int greatest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
  
    if (left_child < n && data[left_child] > data[greatest])
      greatest = left_child;
  
    if (right_child < n && data[right_child] > data[greatest])
      greatest = right_child;
  
    if (greatest != i)
    {
      swap(data + i, data + greatest);
      build_heap(n, greatest);
    }	
}
test1::test1()
{
	errno = 0;
	data = (int*)malloc(num_of_elements * sizeof(int));
	if (!data)
	{
		perror("ERROR: test1::test1()-> data = (int*)malloc(num_of_elements * sizeof(int)), failed to allocate memory\n");
		exit(1);
	}
}
void test1::sort1()
{
	int i;
	generate_data(rand_max);
	for (int i = num_of_elements / 2 - 1; i >= 0; i--)
      		build_heap(num_of_elements, i);
  
	for (int i = num_of_elements - 1; i >= 0; i--) 
	{
      		swap(data, data + i);
  		build_heap(i, 0);
    	}	
	dump();
	printf("\n");
}
void test1::sort2()
{
	int i, key, j;
	generate_data(rand_max * 2);
    	for (int i = 1; i < num_of_elements; ++i) 
	{
        	key = data[i];
        	j = i - 1;
        	while (j >= 0 && data[j] > key) 
		{
            		data[j + 1] = data[j];
            		j = j - 1;
        	}
        	data[j + 1] = key;
    	}	
	dump();	
}
test1::~test1()
{
	free(data);
}
int main()
{
	test1 t;
#if 1	
	t.sort1();
#else
	t.sort2();
#endif	
	exit(0);
}
