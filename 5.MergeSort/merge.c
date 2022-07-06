#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* get_array(int size) {
    
    int* arr = (int*)malloc(sizeof(int) * size);
    assert(arr != NULL);

    for(int i = 0; i < size; i++)
        arr[i] = rand() % 100 + 1;

    return arr;
}

void show_arr(char* message, int* arr, int size) {

    if(message)
        puts(message);

    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int* arr, int p, int q, int r) {

    int N1 = q - p + 1;
    int N2 = r - q; 

    int* arr1 = (int*)malloc(sizeof(int) * N1);
    int* arr2 = (int*)malloc(sizeof(int) * N2);

    assert(arr1 != NULL);
    for(int i = 0; i < N1; i++)
        arr1[i] = arr[p + i];

    assert(arr2 != NULL);
    for(int i = 0; i < N2; i++)
        arr2[i] = arr[q + 1 + i];

    int i = 0;
    int j = 0;
    int k = 0;

    while(1) {

        if(arr1[i] <= arr2[j]) {
            arr[p + k] = arr1[i];
            i++;
            k++;

            if(i == N1) {
                while(j < N2) {
                    arr[p + k] = arr2[j];
                    j++;
                    k++;
                }
                break;
            }
        }

        else {
            arr[p + k] = arr2[j];
            j++;
            k++;

            if(j == N2) {
                while(i < N1) {
                    arr[p + k] = arr1[i];
                    i++;
                    k++;
                }
                break;
            }
        }
    }

    free(arr1);
    arr1 = NULL;
    assert(arr1 == NULL);

    free(arr2);
    arr2 = NULL;
    assert(arr2 == NULL);
}

void merge_sort(int* arr, int p, int r) {

    if(p < r) {
        int q = (p + r) / 2; 
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

void destroy_array(int** array_pointer) {

    free(*array_pointer);
    *array_pointer = NULL;
}

int main(int argc, char* argv[]) {

    if(argc != 2) {
        fprintf(stderr, "Enter a command line argument: size of the array\n");
        exit(EXIT_FAILURE);
    }

    int size = atoi(argv[1]);
    int* arr = get_array(size);
    show_arr("Before sorting:", arr, size);
    merge_sort(arr, 0, size - 1);
    show_arr("After sorting:", arr, size);
    
    destroy_array(&arr);
    assert(arr == NULL);

    return 0;
}