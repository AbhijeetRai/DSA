#include<stdio.h>							//In this code, used for declaration of printf and scanf
#include<stdlib.h>							//In this code, used for declaration of malloc
#include<assert.h> 							//In this code, used for declaration of assert 
#include<string.h>							//In this code, used for declaration of memset

/**
 * input_array function takes address of the size variable of and from main function.
 * Then accepts size of array into the size variable, creates an array dynamically (on heap). 
 * Fills values in array in sorted manner and returns the base address of array to the main function.
 */
int* input_array(int* sizeptr) {
	
	printf("Enter size\n");
	scanf("%d", sizeptr);

	int* arr = NULL; 
	arr = (int*)malloc(sizeof(int) * (*sizeptr));
	assert(arr != NULL);						//making sure the memory is mapped against arr
	memset(arr, 0, sizeof(int) * (*sizeptr));			//initialising mapped memory against arr with 0

	for(int i = 0; i < (*sizeptr); i++)
		arr[i] = (i + 1) * 10;

	return arr;
}

/**
 * output_array function accepts base address of array, size of array and a message. 
 * It prints the message then array.
 */ 
void output_array(int* arr, int size, char* message) {
	
	puts(message);

	for(int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

/**
 * bin_search function actually accomplishes binary search. 
 * It accpets base address of array in which search has to be accomplished.
 * Key which has to be searched in the array.
 * Lowers bounds of array/subarray in form of int i. 
 * Upper bounds of array/subarray in form of int j
 */
int bin_search(int* arr, int key, int i, int j) {
	
	//keep looking only until lower bounds(i) lesser equal upper bounds(j) 
	if(i <= j) {
		
		int mid = (i + j) / 2;
		
		//If key is equal to element at mid index, return mid index
		if(key ==  arr[mid])
			return mid;
		
		//If key is lesser than element at mid index, start looking in array limited to mid - 1 index.
		else if(key < arr[mid])
			return bin_search(arr, key, i, mid - 1); 
		
		//If key is greater than the element at mid index, start looking in array starting from mid + 1 index.
		else if(key > arr[mid])
			return bin_search(arr, key, mid + 1, j);
	}
	
	//If upper bounds(j) < lower bounds(i), element not found: return -1
	else 
		return -1;
}

/**
 * accepts address of pointer that points to base address of the array 
 * and releases the array such that dynamically created memory does not become unreachable causing memory leak
 */
void release_array(int** pptr) {
	
	free(*pptr); 
	*pptr = NULL;
}

/**
 * Driver code: main function 
 * It accpets commands line arguments.
 * It keeps track of number of command line arguments with argc and stores them in argv 
 * Return exit code 0 to the operating system
 */
int main(int argc, char* argv[]) {
	
	int size = 0;
	
	//Send the address of size variable to input_array function. 
	//It will accept array size, create, initialise and return array
	int* arr = input_array(&size);
	//Display array
	output_array(arr, size, "The array is:"); 

	int key = 0; 
	//Ask the user to enter key
	printf("\nEnter key to be searched\n");
	//Accept key
	scanf("%d", &key);

	//Perform binary search, print the returned index 
	//if element is found or not found (in that case bin_search returns -1)
	printf("The index = %d\n", bin_search(arr, key, 0, size - 1));
	
	//release the dynamically created memory(array). We do this because 
	//We do not want dynamic memory(array) to become unreachable causing memory leak
	release_array(&arr);
	//make sure the dynamically mapped memory(the array) has been set to null
	assert(arr == NULL);
	
	//On successful termination, return exit code 0 to the operating system for 
	//cleaning up of this process(program) from the process table.
	return 0;
}
