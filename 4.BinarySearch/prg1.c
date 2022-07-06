#include<stdio.h> 

/**
 * Works perfectly fine if, element is found 
 * But what if.... element is not found
 */

int key = 120;

int bin_search(int* arr, int i, int j) {

    int mid = (i + j) / 2; 
    printf("i = %d j = %d\n", i, j); 

    if(key == arr[mid])
        return mid; 

    else if(key < arr[mid])
        return bin_search(arr, i, mid - 1); 

    else if(key > arr[mid])
        return bin_search(arr, mid + 1, j);
}

int main() {

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    printf("The index is %d\n", bin_search(arr, 0, 9));
}