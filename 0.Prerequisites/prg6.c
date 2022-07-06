#include<stdio.h> 
#include<stdlib.h>

void fun() {

    char* ptr = (char*)malloc(sizeof(char) * 8);    //array of 8 characters created on heap, referenced by ptr; 
    //free(ptr);                                    //But when stack frame of fun pops up, 
                                                        //ptr will be lost and array of 8 characters become unreachable causing memory leak
}

void main() {
    fun();
}