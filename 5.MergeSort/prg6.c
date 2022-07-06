//merge sort statically 
#include<stdio.h> 
#include<stdlib.h>

void merge(int* arr, int p, int q, int r) {

    int N1 = q - p + 1; 
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

void merge_sort(int* arr, int p, int r) {

    if(p < r) {
        int q = (p + r) / 2;
        merge_sort(arr, p, q);
        merge_sort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

void main() {

    int arr[] = {11, 7, 2, 13, 19, -2, 10};
    merge_sort(arr, 0, 6);

    for(int i = 0; i <= 6; i++)
        printf("%d ", arr[i]);
    printf("\n");
}