#include<stdio.h> 

int find_max(int* arr, int i, int j) {

    if(i < j) {

        int mid = (i + j) / 2;
        int lmax = find_max(arr, i, mid); 
        int rmax = find_max(arr, mid + 1, j);
        return lmax > rmax ? lmax : rmax;
    }

    else if(i == j) 
        return arr[i];  
}

void main() {

    int arr[] = {61, 2, 32, 45, 71, 80, 2, -9, 107, 112};
    int max = find_max(arr, 0, 9); 
    printf("max is %d\n", max);
}
/**
 * find_max(arr, i, j) =        return arr[i]                    ...... i == j
                                
                                mid = (i + j) /2                 ...... i < j
                                lamx = (Arr, i, mid) 
                                rmax = (arr, mid + 1, i) 
 */