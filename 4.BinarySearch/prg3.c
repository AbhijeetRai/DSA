//Bringing everything together, getting key from the users
#include<stdio.h>

int bin_search(int* arr, int key, int i, int j) {

    if(j < i) 
        return -1; 

    else {
        int mid = (i + j) / 2; 

        if (key == arr[mid])
            return mid;

        else if (key < arr[mid])
            return bin_search(arr, key, i, mid - 1);

        else if(key > arr[mid]) 
            return bin_search(arr, key, mid + 1, j);
    }
}

int main() {

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int key = 0; 

    printf("Enter the key please\n");
    scanf("%d", &key);

    printf("Index is %d\n", bin_search(arr, key, 0, 9));        //0 is first index, 9 is last

    return 0;
}

/**
 * bin_search(arr, key, i, j)  = -1                                         .... j < i 
 *                             
                                int mid = (i + j) / 2

                                = mid                                       .... key = arr[mid]  
                                = bin_search(arr, key, i , mid - 1)         .... key < arr[mid]
                                = bin_search(arr, key, mid + 1, j)          .... key > arr[mid]
 */