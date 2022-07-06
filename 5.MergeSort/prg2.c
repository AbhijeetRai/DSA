//same zipping code but little dynamically 

#include<stdio.h>
#include<stdlib.h>
#include<assert.h> 

int* create_array(int* sizeptr) {
	
	printf("Enter size\n");
	scanf("%d", sizeptr); 
	
	int* arr = (int*)malloc(sizeof(int) * (*sizeptr));
	assert(arr != NULL);

	for(int i = 0; i < (*sizeptr); i++)
		arr[i] = (i + 1) * 10;
	
	return arr;
}

void show_array(int* arr, int size, char* message) {
	
	puts(message); 
	
	for(int i = 0; i< size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void zip(int* arr, int size) {
	
	int mid = size / 2;

	int N1 = mid + 1; 
	int N2 = size - mid - 1; 
	
	int* arr1 = (int*)malloc(sizeof(int) * N1); 
	int* arr2 = (int*)malloc(sizeof(int) * N2);

	for(int i = 0; i < N1; i++)	
		arr1[i] = arr[i]; 

	for(int i = 0; i < N2; i++)
		arr2[i] = arr[mid + i + 1];

	int i = 0; 
	int j = 0; 
	int k = 0; 

	while(1) {
		
		if(k % 2 == 0) {
			arr[k] = arr1[i];
			i++;
			k++;
			
			if(i == N1) {
				while(j < N2) {
					arr[k] = arr2[j];
					j++;
					k++;
				}
				break;
			}
		}

		else {
			arr[k] = arr2[j];
			j++;
			k++; 
			
			if(j == N2) {
				while(i < N1) {
					arr[k] = arr1[i]; 
					i++;
					k++;
				}
				break;
			}
		}
	}
	free(arr1); 
	arr1 = NULL; 

	free(arr2); 
	arr2 = NULL;
}

void release_array(int** ptr) {
	
	free(*ptr);
	*ptr = NULL;
}

int main() {
	
	int size = 0; 
	int* arr = create_array(&size);
	
	show_array(arr, size, "Before zip");
	zip(arr, size); 
	show_array(arr, size, "After zip");	
		
	release_array(&arr);	

	return 0;
}
