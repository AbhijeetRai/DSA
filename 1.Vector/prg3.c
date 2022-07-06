#include<stdio.h> 
#include<stdlib.h> 
#include<assert.h>

typedef struct int_vector {

    int* iptr; 
    int size; 
}int_vector;

int_vector* create_vector() {

    int_vector* ptr = NULL; 
    ptr = (int_vector*)malloc(sizeof(int_vector));

    assert(ptr != NULL);
    ptr -> iptr = NULL; 
    ptr -> size = 0;

    return ptr;
}

void append_vector(int_vector* ptr) {

    int number = 0; 
    printf("Enter the number to be appended\n");
    scanf("%d", &number); 

    ptr -> iptr = (int*)realloc(ptr -> iptr, sizeof(int) * (ptr -> size + 1));
    *(ptr -> iptr + ptr -> size) = number; 
    ptr -> size++;
}

void show_vector(int_vector* ptr) {

    for(int i = 0; i < ptr -> size; i++) 
        printf("%d ", *(ptr -> iptr + i));

    printf("\n");
}

void destroy_vector(int_vector** pptr) {

    free((*pptr) -> iptr); 
    (*pptr) -> iptr = NULL; 
    ((*pptr) -> size) = 0;

    free(*pptr);
    *pptr = NULL; 
}

void main() {
    
    int_vector* pointer = create_vector();
    
    append_vector(pointer);
    append_vector(pointer);
    
    show_vector(pointer);
    destroy_vector(&pointer);

    assert(pointer == NULL);
}