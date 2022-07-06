#include<stdio.h> 
#include<stdlib.h>

//zipping
void zip(int* arr, int N) {

    int mid = N / 2;

    int N1 = mid + 1;
    int N2 = N - mid - 1;

    int* arr1 = (int *)malloc(sizeof(int) * N1);
    int* arr2 = (int *)malloc(sizeof(int) * N2);

    for(int i = 0; i < N1; i++) 
        arr1[i] = arr[i];

    for(int i = 0; i < N2; i++) 
        arr2[i] = arr[mid + i + 1];    

    int i = 0; 
    int j = 0; 
    int k = 0;

    while(1) {

        if(k % 2 ==0) {
            arr[k] = arr1[i]; 
            i++; 
            k++;

            if(i == N1) {
                while(j < N2) {
                    arr[k] = arr2[j];
                    j++;
                    k++;
                }
                break;
            }
        }

        else {
            arr[k] = arr2[j];
            j++;
            k++;

            if(j == N2) {
                while(i < N1) {
                    arr[k] = arr1[i]; 
                    i++; 
                    k++;
                }
                break;
            }
        }
    }
}

void main() {

    int arr[] = {900, 100, 300, 400, 700};
    zip(arr, 5);

    for(int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");
}