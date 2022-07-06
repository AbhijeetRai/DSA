#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define SUCCESS 1

typedef struct vector_int {
    int* p_arr;
    unsigned long long int size;
} vector_int;

vector_int* create_vector(void);
int append_int(vector_int* p_vec, int element);
void destroy_vector(vector_int** pp_vec);
void show_vector(vector_int* p_vec, const char* msg) ;

int main() {

    vector_int * p_vec_rem0 = NULL;
    vector_int * p_vec_rem1 = NULL;
    vector_int * p_vec_rem2 = NULL;
    vector_int * p_vec = NULL;
    int i, n;
    int total_nums = 3000;

    p_vec_rem0 = create_vector();
    p_vec_rem1 = create_vector();
    p_vec_rem2 = create_vector();

    for(i = 0; i < total_nums; i++) {
        
        n = rand();
        switch (n % 3)
        {
            case 0:
                p_vec = p_vec_rem0;
                break;

            case 1:
                p_vec = p_vec_rem1;
                break;

            case 2:
                p_vec = p_vec_rem2;
                break;
        }

        append_int(p_vec, n);
        p_vec = NULL;
    }

    show_vector(p_vec_rem0, "Numbers Divisible by 3");
    show_vector(p_vec_rem1, "Numbers with remainder 1 after dividing by 3");
    show_vector(p_vec_rem2, "Numbers with remainder 1 after dividing by 3");

    printf("size of p_vec_rem0 : %llu\n", p_vec_rem0->size);
    printf("size of p_vec_rem1 : %llu\n", p_vec_rem1->size);
    printf("size of p_vec_rem2 : %llu\n", p_vec_rem2->size);

    destroy_vector(&p_vec_rem0);
    destroy_vector(&p_vec_rem1);
    destroy_vector(&p_vec_rem2);

    assert(p_vec_rem0 == NULL);
    assert(p_vec_rem1 == NULL);
    assert(p_vec_rem2 == NULL);

    return(0);
}

vector_int* create_vector(void) {
    vector_int* p_newVec = NULL;
    p_newVec = (vector_int*)malloc(sizeof(vector_int));
    assert(p_newVec != NULL);

    p_newVec->p_arr = NULL;
    p_newVec->size = 0;

    return(p_newVec);
}

int append_int(vector_int* p_vec, int element) {

    p_vec->p_arr = (int*)realloc(p_vec->p_arr, ((p_vec->size) + 1) * sizeof(int*));
    assert(p_vec->p_arr != NULL);
    p_vec->size += 1;
    p_vec->p_arr[p_vec->size - 1] = element;
    return(SUCCESS);
}

void show_vector(vector_int* p_vec, const char* msg) {

    unsigned long long int i;
    if(msg != NULL) {
        puts(msg);
    }
    for(i = 0; i < p_vec->size; i++) {
        printf("p_vec[%llu] : %d\n", i, p_vec->p_arr[i]);
    }
}

void destroy_vector(vector_int** pp_vec) {

    vector_int *p_vec = *pp_vec;

    free(p_vec->p_arr);
    p_vec->p_arr = NULL;
    p_vec->size = 0;

    free(p_vec);
    *pp_vec = NULL;
}
