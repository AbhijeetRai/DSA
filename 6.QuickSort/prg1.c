#include <stdio.h> 

int partition(int* arr, int p, int r) {

    int i = p - 1;
    int pivot = arr[r];
    int j = p;

    for(; j < r; j++) {

        if(arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    i++;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    return i;
}

int main(int argc, char* argv[]) {
    
    int arr[] = {11, 7, 13, 8, 15, 7, 9};
    int q = partition(arr, 0, 6);

    printf("q index = %d\n", q);
    for(int i = 0; i <= 6; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;   
}