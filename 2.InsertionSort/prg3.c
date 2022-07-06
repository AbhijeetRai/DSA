/**
 * Trying to sort same array using the same logic 
 * But the entire array is unsorted 
 * We can increase array length from 2 to n. 
 * To simulate scenario, what if only last element of array is not sorted
 */ 

#include<stdio.h> 

void insert_sort(int arr[], int size) {

    int key = arr[size - 1]; 
    int i = size - 2; 

    for(; i >= 0 && arr[i] > key; --i) 
        arr[i + 1] = arr[i]; 
    
    arr[i + 1] = key;  
}

void main() {

    int array[] = {10, 20, 2, -1, 3, 55, 31};
    
    for(int i = 2; i <= 7; i++) {
        insert_sort(array, i);
        printf("%d %d %d %d %d %d %d", array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
        printf("\n");
    }
}