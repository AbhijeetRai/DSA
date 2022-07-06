#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int* get_array(int size) {

    int* array = (int*)malloc(sizeof(int) * size);
    assert(array != NULL);
    memset(array, 0, sizeof(int) * size);

    for(int i = 0; i < size; ++i)
        array[i] = rand() % 100 + 1;
    
    return array;
}


void show_array(int* array, int size, char* message) {

    if(message) 
        puts(message);
    
    for(int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}


void sort(int* array, int size) {

    int key = array[size - 1];
    int i = size - 2;

    for(; i >= 0 && array[i] > key; --i)
        array[i + 1] = array[i];

    array[i + 1] = key;
}


void insert_sort(int* array, int size) {

    for(int i = 2; i <= size; i++)
        sort(array, i);
}


int main(int argc, char* argv[]) {

    if(argc != 2) {
        fprintf(stderr, "Enter size of an array as command line argument\n");
        exit(EXIT_FAILURE);
    }

    int size = atoi(argv[1]);
    assert(size > 1);

    int* array = get_array(size);
    show_array(array, size, "Before sorting:");
    insert_sort(array, size);
    show_array(array, size, "After sorting:");

    return 0;
}