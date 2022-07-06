#include<stdio.h> 

void main() {

    int a = 10; 
    void *ptr = &a; 
    //Although void pointer can hold address of int or array of pointers, it is blind.
    //It cannot be dereferenced, because it does not know what kind of address it is holding.
    //It does not know whether it is holding address of int or array of pointers
    //So when it is dereferenced, it does not know how many bits to read at stored address. 

    //For example, when *ptr is dereferenced, 
    //*ptr does not know it holds address of an integer and must read 4 bytes after dereferencing 
    //Which is why compiler gives error for dereferecing void pointer  

    //Which is why ptr is explicitly casted to integer pointer 
    //When integer pointer is derefernced, it goes to stored address and reads 4 bytes as expected
    int* intpointer = ptr; 
    printf("%d\n", *intpointer);
}