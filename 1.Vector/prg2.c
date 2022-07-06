//Program to accept your name dynamically: growing character vector
//Implemented with the help of structure

#include <stdio.h> 
#include <stdlib.h>

typedef struct vector{
    char *cptr; 
    int size; 
}vector;  

int main() {

    vector* ptr = NULL; 
    ptr = (vector*)malloc(sizeof(vector));
    ptr -> cptr = NULL; 
    ptr -> size = 0;

    int response = 0;
    char character = 0;

    while(1) {

        printf("Press 1 to enter a character. Press any key to exit\n"); 
        scanf("%d", &response);

        if(response != 1) 
            break; 

        printf("Enter the character\n");
        scanf(" %c", &character);

        ptr -> cptr = (char *)realloc(ptr->cptr, sizeof(char) * (ptr -> size + 1));
        *(ptr -> cptr + ptr -> size) = character; 
        ptr -> size++;
    }

    for(int i = 0; i < ptr -> size; i++)
        printf("%c ", *(ptr -> cptr + i));
    printf("\n");

    return 0;
}