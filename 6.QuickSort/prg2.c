#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* get_array(int size) {

    int* array = (int*)malloc(sizeof(int) * size);
    assert(array != NULL);

    for(int i = 0; i < size; i++)
        array[i] = rand() % 100 + 1;

    return array;
}

void show_array(char* message, int* array, int size) {

    if(message)
        puts(message);

    for(int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int partition(int* array, int p, int r) {

    int pivot = array[r];
    int j = p;
    int i = p - 1;
    int temp;

    for(; j < r; j++) {
        if(array[j] <= pivot) {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    i++;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;

    return i;
}

void quick_sort(int* array, int p, int r) {

    if(p < r) {
        int q = partition(array, p, r);
        quick_sort(array, p, q - 1);
        quick_sort(array, q + 1, r);
    }
}

void destroy_array(int** ptr) {

    free(*ptr);
    *ptr = NULL;
}

int main(int argc, char* argv[]) {

    if(argc != 2) {
        fprintf(stderr, "Usage Error: Enter size of an array as command line argument\n");
        exit(EXIT_FAILURE);
    }
    
    int size = atoi(argv[1]);
    int* array = get_array(size);
    
    show_array("Before sorting:", array, size);
    quick_sort(array, 0, size - 1);
    show_array("After sorting:", array, size);

    destroy_array(&array);
    assert(array == NULL);

    return 0;
}