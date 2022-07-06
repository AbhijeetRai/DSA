#include<stdio.h> 

/**
 * Trying to reverse an array using recursion
 * reverse(arr, 0, 5) = reverse(arr, i + 1, N)        ...      i < N - i
 *          IS SAME AS 
 * reverse(arr, i, N) = reverse(arr, i + 1, N)        ...      i < N - i
 */

void reverse(int* ptr, int i, int N) {              //"N IS THE LAST INDEX"

    if(i < N - i) {

        int temp = ptr[i]; 
        ptr[i] = ptr[N - i];                        
        ptr[N - i] = temp;
        reverse(ptr, i + 1, N);
    }
}

void main() {

    int arr[] = {10, 20, 30, 40, 50, 60};
    reverse(arr, 0, 5);

    for(int i = 0; i <= 5; i++)             
        printf("%d ", arr[i]);
    printf("\n");
}