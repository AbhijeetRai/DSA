#include<stdio.h>
int main() {

    int arr[3] = {10, 20, 30}; 

    printf("%d\n", arr[2]); 
    printf("%d\n", *(&arr[0] + 2));
    printf("%d\n", *(arr + 2));     //arr = &arr[0]

    printf("\n");

    int *ptr = arr;                 //pointer to an integer that is arr[0], ptr holds address of zeroth element
    printf("%d\n", *(ptr + 2));     //if *(arr + 2) = *(&arr[0] + 2) then *(ptr + 2) = *(arr + 2)
    printf("%d\n", ptr[2]);         //ptr[2] = *(ptr + 2) = *(arr + 2) = *(&arr[0] + 2)
}