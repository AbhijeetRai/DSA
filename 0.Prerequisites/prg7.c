//ways to avoid memory leak

#include<stdio.h>
#include<stdlib.h>

char* gptr; 

void fun1() {

    char* ptr1 = (char*)malloc(sizeof(char) * 8);
    gptr = ptr1;        //copy pointer into global variable
}

char* fun2() {

    char* ptr2 = (char*)malloc(sizeof(char)* 8);
    return ptr2;        //return the address of dynamic memory
}

char* fun3(char** cptr) {

    char* ptr3 = (char*)malloc(sizeof(char) * 8);
    *cptr = ptr3;       //put in character pointer of main wherever local ptr3 is looking
}

void main() {

    char* ptr3; 
    fun3(&ptr3); //sending address of character pointer
}
