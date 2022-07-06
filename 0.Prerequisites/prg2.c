#include<stdio.h> 

void main() {

    int a = 10; 
    void *ptr = &a; 
    //ptr typecasted to intpointer
    printf("%d\n", *(int *)ptr);
}