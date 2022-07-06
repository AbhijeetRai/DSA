/*
 * Insertion sort is written considering the case 
 * What if last element of array is not sorted 
 * Considering dry running this code
 */

#include<stdio.h> 

void main() {

    int arr[] = {10, 20, 30, 40, 50, 25};
    int key = arr[5];

    int i = 4;

    for(;i >= 0 && arr[i] > key; --i) 
        arr[i + 1] = arr[i];

    arr[i + 1] = key;
    printf("I IS %d\n", i);

    for(int i = 0; i < 6; i++) 
        printf("%d ", arr[i]); 

    printf("\n");
}