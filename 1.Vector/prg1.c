//dynamic resizable array as known as vector
//array should keep growing dynamically 
//to do so we need a pointer pointing to array 
//and a variable to keep tap on size of array
#include<stdio.h> 
#include<stdlib.h>

int main() {

    int response = 0; 
    int number = 0;
    int *pointer = NULL;
    int size = 0;

    while(1) {

        printf("Press 1 to input a number or press any key to exit\n");
        scanf("%d", &response); 

        if(response != 1)
            break;

        printf("Enter the number\n");
        scanf("%d", &number);
        size++;

        pointer = (int *)realloc(pointer, sizeof(int) * size);
        *(pointer + size - 1) = number;
    }

    for(int i = 0; i < size; i++)
        printf("%d\n", *(pointer + i));

    return 0;
}