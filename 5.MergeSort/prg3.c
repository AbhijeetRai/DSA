//same code but modification in array creation and merge(zip) function 
//Actual merge function written

#include<stdio.h> 
#include<stdlib.h>
#include<assert.h> 

int* create_array(int* size_ptr) {

    printf("Enter the size:");
    scanf("%d", size_ptr);

    int* arr = (int*)malloc(sizeof(int) * (*size_ptr));

    int mid = (*size_ptr) / 2; 

    for(int i = 0; i <= mid; i++)
        arr[i] = (i + 1) * 10;

    for(int i = mid + 1; i < (*size_ptr); i++)
        arr[i] = (i + 1) * 5;

    return arr;
}

void show_array(int* arr, int size, char* message) {

    puts(message);

    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int* arr, int size) {

    int mid = size / 2;

    int N1 = mid + 1; 
    int N2 = size - mid -1; 

    int* arr1 = (int*)malloc(sizeof(int) * N1); 
    int* arr2 = (int*)malloc(sizeof(int) * N2);

    for(int i = 0; i < N1; i++)
        arr1[i] = arr[i]; 

    for(int i = 0; i < N2; i++)
        arr2[i] = arr[mid + i + 1];

    int i = 0; 
    int j = 0; 
    int k = 0;

    while(1) {

        //start inserting (alternatively from both subarrays) according to increasing order
        if(arr1[i] <= arr2[j]) {
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
int main() {

    int size; 

    int* arr = create_array(&size);
    show_array(arr, size, "Before merge:");
    merge(arr, size);
    show_array(arr, size, "After merge:");
}