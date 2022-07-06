/**
 * Looping approach towards binary search
 */

#include<stdio.h> 

void main() {

    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int i = 0, j = 9;
    int key = 65;
    int flag = 0;
    
    while(i <= j) {

        int mid = (i + j) / 2;

        if (key == arr[mid]) {

            printf("Index is %d\n", mid);
            flag = 1;
            break;
        }

        else if(key < arr[mid])
            j = mid - 1;

        else if(key > arr[mid])
            i = mid + 1;
    }

    if(flag == 0) 
        printf("Index is -1\n");
}