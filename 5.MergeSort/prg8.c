#include<stdio.h> 
#include<stdlib.h>
#include<assert.h>
#include<string.h>


int* get_array(int* sizePtr) {

	printf("Enter the array size\n");
	scanf("%d", sizePtr);

	int* ptr = (int*)malloc(sizeof(int) * (*sizePtr));
	assert(ptr != NULL);
	memset(ptr, 0, sizeof(int) * (*sizePtr));

	for(int i = 0; i < (*sizePtr); i++)
		ptr[i] = rand();

	return ptr;
}


void show_array(int* ptr, int size, char* message) {

	if(message) 
		printf("%s\n", message);

	for(int i = 0; i < size; i++)
		printf("%d ", ptr[i]); 
	printf("\n");
}


void merge(int* ptr, int p, int q, int r) {

	int N1 = q - p + 1;
	int N2 = r - q;

	int* ptr1 = (int*)malloc(sizeof(int) * N1);
	int* ptr2 = (int*)malloc(sizeof(int) * N2);

	assert(ptr1 != NULL);
	assert(ptr2 != NULL);

	for(int i = 0; i < N1; i++)
		ptr1[i] = ptr[p + i];

	for(int i = 0; i < N2; i++)
		ptr2[i] = ptr[q + 1 + i];

	int i = 0;
	int j = 0; 
	int k = 0;  

	while(1) {

		if(ptr1[i] <= ptr2[j]) {
			ptr[p + k] = ptr1[i];
			i++;
			k++;

			if(i == N1) {
				while(j < N2) {
					ptr[p + k] = ptr2[j];
					j++;
					k++;
				}
				break;
			}
		}

		else {
			ptr[p + k] = ptr2[j];
			j++;
			k++;

			if(j == N2) {
				while(i < N1) {
					ptr[p + k] = ptr1[i];
					i++;
					k++;
				}
				break;
			} 
		}
	}

	free(ptr1); 
	ptr1 = NULL; 

	free(ptr2);
	ptr2 = NULL;
}


void merge_sort(int* ptr, int p, int r) {

	if(p < r) {

		int q = (p + r) / 2; 
		merge_sort(ptr, p, q);
		merge_sort(ptr, q + 1, r); 
		merge(ptr, p, q, r);
	}
}

void release_array(int** pptr) {

	free(*pptr);
	*pptr = NULL;
}

int main() {

	int size;

	int* ptr = get_array(&size);
	show_array(ptr, size, "Before merge sort");
	merge_sort(ptr, 0, size - 1);
	show_array(ptr, size, "After merge sort");
	release_array(&ptr);

	assert(ptr == NULL);
	return 0;
}