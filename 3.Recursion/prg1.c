//factorial code with mathematics 

/**
 * factorial(n) = n * factorial(n - 1)    .... if  n > 1 
 *              = 1                       .... if  n = 1
 */

#include<stdio.h> 

long long unsigned int factorial(long long unsigned int number) {

    if (number > 1) 
        return number * factorial(number - 1);
    else 
        return 1;
}

void main() {

    long long unsigned int number = 0;

    printf("Enter number to find factorial\n");
    scanf("%llu", &number);

    printf("%llu\n", factorial(number));
}