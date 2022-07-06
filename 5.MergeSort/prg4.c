//merge routine for subarray 
#include<stdio.h>
#include<stdlib.h>


void merge(int* arr, int p, int q, int r) {

    int N1  = q - p + 1;
    int N2 = r - q;

    int* arr1 = (int*)malloc(sizeof(int) * N1);
    int* arr2 = (int*)malloc(sizeof(int) * N2);

    for(int i = 0; i < N1; i++)
        arr1[i] = arr[p + i]; 

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

        else{
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
}

int main() {

    int arr[] = {0, 0, 0,       10, 20, 30, 40, 5, 15, 25, 35     , 0, 0, 0};
    //Indices:   0  1  2         3   4   5   6  7   8  9   10       11 12 13
    
    //Calling merge over subarray [3, 10], that will create two sorted subarrays [3, 6] and [7, 10]
    merge(arr, 3, 6, 10);

    for(int i = 0; i < 14; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}