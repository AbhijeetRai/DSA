#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 

void input_array(int* p, int N); 
void sort_array(int* p, int N); 
void output_array(int* p, int N); 
void release_array(int** pp); 

void insert_at_sorting_pos(int* p, int N); 

int main(int argc, char* argv[])
{
    int* p = NULL; 
    int N; 
    
    if(argc != 2)
    {
        printf("UsageError:%s nr_of_elements\n", argv[0]); 
        exit(EXIT_FAILURE); 
    }

    N = atoi(argv[1]); 
    if(N <= 0)
    {
        printf("Bad size for number of element field\n"); 
        exit(EXIT_FAILURE); 
    }

    p = (int*)malloc(N * sizeof(int)); 
    if(p == NULL)
    {
        puts("Memory allocation failed"); 
        exit(EXIT_FAILURE); 
    }
    memset(p, 0, N * sizeof(int)); 

    input_array(p, N); 
    sort_array(p, N); 
    output_array(p, N); 
    release_array(&p); 
   
    exit(0); 
}

void input_array(int* p, int N)
{
    int i; 
    for(i = 0; i < N; ++i)
        p[i] = rand(); 
}

void sort_array(int* p, int N)
{
    int i; 
    for(i = 2; i <= N; ++i)
        insert_at_sorting_pos(p, i); 
}

void output_array(int* p, int N)
{
    int i; 
    for(i = 0; i < N; ++i)
        printf("p[%d]:%d\n", i, p[i]); 
}

void release_array(int** pp)
{
    free(*pp);  // free(p in main)
    *pp = NULL; // (p in main) = NULL
}

void insert_at_sorting_pos(int* p, int N)
{
    int key, i; 
    key = p[N-1]; 
    for(i = N-2; i > -1 && p[i] > key; --i)
        p[i+1] = p[i]; 
    p[i+1] = key; 
}