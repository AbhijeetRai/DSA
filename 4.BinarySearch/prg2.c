#include<stdio.h>

int key = 0;
int bin_search(int* arr, int i, int j) {

    if(j < i)
        return -1; 

    else {

        printf("%d %d\n", i, j);
        int mid = (i + j) / 2; 

        if (key == arr[mid])
            return mid; 

        else if(key < arr[mid])
            return bin_search(arr, i, mid - 1);

        else if(key > arr[mid])
            return bin_search(arr, mid + 1, j);

    }
}

void main() {

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    printf("The index of is %d\n", bin_search(arr, 0, 8));
}


/**
 * There was no stopping condition in previous code, if element was not found
 * Sometimes an element of array say 10 is i, j, mid, all of it. 
 *           
               10 
            i, j, mid 

    When we do
    bin_search(arr, i, mid - 1)  OR 
    bin_search(arr, mid + 1, j) if key is not found then 
    j < i, j becomes lesser than i and stack overflows and also key is never found. 

    So stopping condition should be if j < i = -1 (key is absent)
 */