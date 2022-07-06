#include<stdio.h> 
#include<stdlib.h>      //declaration of free, malloc and exit
#include<assert.h>      //declaration of assert
#include<string.h>      //declaration of memset

struct point {

    double x,y,z;
};

void built_in_data_type(void);
void array_of_built_in_data_type(void);
void array_of_pointers_to_built_in_data_type(void);

void user_defined_data_type();
void array_of_user_defined_data_type(void);
void array_of_pointers_to_user_defined_data_type(void);

int main(void) {

    //built_in_data_type();
    //array_of_built_in_data_type();
    //array_of_pointers_to_built_in_data_type();
    //user_defined_data_type();
    //array_of_user_defined_data_type();
    array_of_pointers_to_user_defined_data_type();
    exit(0);
}

void built_in_data_type(void) {

    int *ptr = NULL; 
    //on calling malloc, a memory is allocated to ptr 
    //from 4kb page size on heap
    ptr = (int*)malloc(sizeof(int));

    //after every malloc, it is not necessary that memory is mapped 
    //hence checking if memory is mapped against ptr
    //if memory is not allocated against ptr, program will terminate
    assert (ptr!= NULL);                
    memset(ptr, 0, sizeof(int));
    *ptr = 10; 
    printf("%d\n", *ptr); 
    free(ptr);      //deallocate memory from heap allocated to ptr
    ptr=NULL;       //make ptr forget the address of allocated memory
}

void array_of_built_in_data_type(void) {

    int length = 7;
    int *pointer = NULL; 

    pointer = (int*)malloc(sizeof(int) * length); 
    assert(pointer != NULL);
    memset(pointer, 0, sizeof(int) * length); 
    printf("put %d integers\n", length); 

    for(int i = 0; i < length; i++) 
        scanf("%d", pointer + i);

    for(int i = 0; i < length; i++) 
        printf("%d ", *(pointer + i));  //ptr[i] would also work

    free(pointer); 
    pointer = NULL;
}

void array_of_pointers_to_built_in_data_type(void) {

    int length = 3;
    int** pptr = NULL; 
    pptr = (int**)malloc(sizeof(int*) * length);
    assert(pptr != NULL);
    memset(pptr, 0, length * sizeof(int*)); 

    for(int i = 0; i < length; i++) {

        *(pptr + i) = (int*)malloc(sizeof(int));
        assert(*(pptr + i) != NULL); 
        memset(*(pptr+i), 0, sizeof(int));
        **(pptr + i) = (i + 1) * 10;                //*pptr[i] could work too
    }

    for(int i = 0; i < length; i++) { 

        printf("%d\n", **(pptr + i));
        free(*(pptr + i));
        *(pptr + i) = NULL;
    }

    free(pptr);
    pptr = NULL;
}

void user_defined_data_type(void) {

    struct point* ptr = NULL;
    ptr = (struct point*)malloc(sizeof(struct point));
    assert(ptr != NULL); 
    memset(ptr, 0, sizeof(struct point));

    ptr -> x = 1.1;
    ptr -> y = 2.2;
    ptr -> z = 3.3;

    printf("ptr -> x = %.2lf ptr -> y = %.2lf ptr -> z = %.2lf\n", 
    ptr -> x, ptr -> y, ptr ->z);

    free(ptr); 
    ptr = NULL;
}

void array_of_user_defined_data_type(void) {

    int length = 3;
    struct point* ptr = NULL; 
    ptr = malloc(sizeof(struct point) * length);
    assert(ptr != NULL); 
    memset(ptr, 0.0, sizeof(struct point) * length);

    for(int i = 0; i < length; i++) {

        (ptr + i) -> x = (i + 1) * 1.1;     //ptr[i].x could work too
        (ptr + i) -> y = (i + 1) * 2.2;
        (ptr + i) -> z = (i + 1) * 3.3;
    }

    for(int i = 0; i < length; i++) //(*(ptr+i)).x could work too
        printf("%.2f %.2f %.2f\n", (ptr + i) -> x, (ptr + i) -> y, (ptr + i) -> z);

    free(ptr);
    ptr = NULL;
}

void array_of_pointers_to_user_defined_data_type(void) {

    int length = 3;
    struct point** ptr = NULL; 
    ptr = (struct point**)malloc(sizeof(struct point*) * length);
    assert(ptr != NULL); 
    memset(ptr, 0, sizeof(struct point *) * length);

    for(int i = 0; i < length; i++) {

        *(ptr + i) = (struct point*)malloc(sizeof(struct point));       //ptr[i] would work too
        assert(*(ptr + i) != NULL);
        memset(*(ptr + i), 0, sizeof(struct point));

        //(**(ptr + i)).x = (i + 1) * 1.1; works as well
        (*(ptr + i)) -> x = (i + 1) * 1.1;                              //ptr[i] -> x would work too
        (*(ptr + i)) -> y = (i + 1) * 2.2;
        (*(ptr + i)) -> z = (i + 1) * 3.3;
    }

    for(int i = 0; i < length; i++) 
        printf("%.2f %.2f %.2f\n", (*(ptr + i)) -> x, 
        (*(ptr + i)) -> y, (*(ptr + i)) -> z);

    for(int i = 0; i < length; i++) {

        free(*(ptr + i));
        *(ptr + i) = NULL;
    }

    free(ptr); 
    ptr = NULL;
}