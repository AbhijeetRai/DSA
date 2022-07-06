#include<stdio.h> 

/**
 * Last element of array is still not sorted, trying to sort the last element. 
 * Trying to sort last element with a little dynamic approach
 */

void insert_sort(int arr[], int size) {

    int key = arr[size - 1];
    int i = size - 2;

    for(; i >= 0 && arr[i] > key; --i) 
        arr[i + 1] = arr[i]; 

    arr[i + 1] = key; 

    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n"); 
}

void main() {

    int array[] = {10, 20, 30, -2}; 
    insert_sort(array, 4);
}