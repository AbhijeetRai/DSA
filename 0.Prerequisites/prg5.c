/**
 * A memory leak occurs, 
 * when dynamic memory no longer needed is 
 * not freed and when it becomes "UNREACHABLE". 
 */

#include<stdio.h>
#include<stdlib.h>

int main() {

    int* pointer1 = (int*)malloc(sizeof(int) * 5);      //an array of 5 integers created on heap referenced by pointer1
    pointer1 = NULL;                                    //pointer1 points to NULL now and array of 5 integers still exist but is lost now

    /**
     *  Dynamic memory should be freed before becoming unreachable 
     *  or should not become unreachable
    */

    return 0;
}