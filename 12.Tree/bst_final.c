#define _CRT_RAND_S

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define TRUE    1 
#define FALSE   0 

#define SUCCESS             1 
#define TREE_EMPTY          2 
#define TREE_DATA_NOT_FOUND 3 
#define TREE_NO_SUCCESSOR   4 
#define TREE_NO_PREDECESSOR 5

struct bst_node
{
    int data; 
    struct bst_node* left; 
    struct bst_node* right; 
    struct bst_node* parent; 
}; 

struct bst
{
    struct bst_node* p_root_node; 
    unsigned long long int nr_elements; 
}; 

struct bst* create_bst(void); 
int bst_insert(struct bst* p_bst, int new_element); 

void preorder_r(struct bst* p_bst); 
void inorder_r(struct bst* p_bst); 
void postorder_r(struct bst* p_bst); 
int bst_max(struct bst* p_bst, int* p_max_data); 
int bst_min(struct bst* p_bst, int* p_min_data); 
int bst_inorder_successor(struct bst* p_bst, int ext_data, int* p_succ_data); 
int bst_inorder_predecessor(struct bst* p_bst, int ext_data, int* p_pred_data); 
int bst_search(struct bst* p_bst, int search_data); 
int remove_data(struct bst* p_nst, int r_data); 
int bst_remove_with_helper_routine(struct bst* p_bst, int r_data); 
int bst_is_empty(struct bst* p_bst); 
unsigned long long int get_nr_elements(struct bst* p_bst); 
void bst_destroy(struct bst** pp_bst); 

struct bst_node* get_max_node(struct bst_node* p_node); 
struct bst_node* get_min_node(struct bst_node* p_node); 
struct bst_node* inorder_successor(struct bst_node* p_node); 
struct bst_node* inorder_predecessor(struct bst_node* p_node); 
struct bst_node* search_node(struct bst* p_bst, int search_data); 
void preorder_node(struct bst_node* p_root_node); 
void inorder_node(struct bst_node* p_root_node); 
void postorder_node(struct bst_node* p_root_node); 
void destroy_node(struct bst_node* p_root_node); 
void transplant(struct bst* p_bst, struct bst_node* u, struct bst_node* v); 
struct bst_node* get_bst_node(int new_element); 

void extreme_testing(void); 

int main(void)
{
    struct bst* p_bst = NULL; 
    int status; 
    //int data[] = {10, 7, 16, 14, 15, 13}; 
    int data[] = {100, 150, 75, 200, 125, 85, 50, 65, 130}; 
    int data_np[] = {-100, 2004, 3453, -45635, 3456, 363535}; 
    int i; 
    int pred_data, succ_data; 
    int min_data, max_data; 

    p_bst = create_bst(); 

    status = bst_max(p_bst, &max_data); 
    if(status == TREE_EMPTY)
        printf("bst_max:Tree is empty\n"); 

    status = bst_min(p_bst, &min_data); 
    if(status == TREE_EMPTY)
        printf("bst_min:Tree is empty\n"); 

    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
    {
        status = bst_insert(p_bst, data[i]); 
        assert(status == SUCCESS); 
    }

    puts("Preorder traversal:"); 
    preorder_r(p_bst); 

    puts("Inorder traversal:"); 
    inorder_r(p_bst); 

    puts("Postorder traversal:"); 
    postorder_r(p_bst); 

    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
    {
        status = bst_search(p_bst, data[i]); 
        assert(status == TRUE); 
        printf("%d present in tree\n", data[i]); 
    }

    for(i = 0; i < sizeof(data_np)/sizeof(int); ++i)
    {
        status = bst_search(p_bst, data_np[i]); 
        assert(status == FALSE); 
        printf("%d not present in tree\n", data_np[i]); 
    }   

    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
    {
        status = bst_inorder_predecessor(p_bst, data[i], &pred_data); 
        if(status == TREE_NO_PREDECESSOR)
            printf("%d has no predecessor\n", data[i]); 
        else if(status == SUCCESS)
            printf("Predecessor of %d is %d\n", data[i], pred_data); 
    }

    for(i = 0; i < sizeof(data)/sizeof(int); ++i)
    {
        status = bst_inorder_successor(p_bst, data[i], &succ_data); 
        if(status == TREE_NO_SUCCESSOR)
            printf("%d has no successor\n", data[i]); 
        else if(status == SUCCESS)
            printf("Successor of %d is %d\n", data[i], succ_data); 
    }

    status = bst_max(p_bst, &max_data); 
    if(status == SUCCESS)
        printf("Max data = %d\n", max_data); 

    status = bst_min(p_bst, &min_data); 
    if(status == SUCCESS)
        printf("Min data = %d\n", min_data); 
    puts("Showing bst before starting removal:"); 
    inorder_r(p_bst);
    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        status = bst_remove_with_helper_routine(p_bst, data[i]); 
        assert(status == SUCCESS); 
        printf("Showing bst after removing:%d\n", data[i]); 
        inorder_r(p_bst); 
    }

    if(bst_is_empty(p_bst))
        puts("BST is empty after removing all data"); 

    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        status = bst_insert(p_bst, data[i]); 
        assert(status == SUCCESS); 
    }
    puts("Showing tree after re-population"); 
    inorder_r(p_bst); 

    bst_destroy(&p_bst); 
    // extreme_testing(); 

    puts("SUCCESS"); 
    return (0); 
}

void extreme_testing(void)
{
    unsigned long long int nr_elements = 1000000; 
    int status; 
    unsigned int num; 
    unsigned long long int i; 
    struct bst* p_bst = NULL; 

    p_bst = create_bst(); 
    for(i = 0; i < nr_elements; ++i)
    {   
        rand_s(&num); 
        status = bst_insert(p_bst, num); 
        assert(status == SUCCESS); 
    }

    printf("Printing %llu sorted numbers in tree\n", nr_elements); 
    inorder_r(p_bst); 
    
    bst_destroy(&p_bst); 
}

struct bst* create_bst(void)
{
    struct bst* p_bst = NULL; 

    p_bst = (struct bst*)malloc(sizeof(struct bst)); 
    if(p_bst == NULL)
    {
        fprintf(stderr, "malloc:fatal:out of virtual memory\n"); 
        exit(EXIT_FAILURE); 
    }

    p_bst->p_root_node = NULL; 
    p_bst->nr_elements = 0; 

    return (p_bst); 
}

int bst_insert(struct bst* p_bst, int new_element)
{
    struct bst_node* p_new_node = NULL; 
    struct bst_node* p_run = NULL; 

    p_new_node = get_bst_node(new_element); 
    p_run = p_bst->p_root_node; 

    if(p_run == NULL)
    {
        p_bst->p_root_node = p_new_node; 
        p_bst->nr_elements += 1; 
        return (SUCCESS); 
    }

    while(1)
    {
        if(new_element <= p_run->data)
        {
            if(p_run->left == NULL)
            {
                p_run->left = p_new_node; 
                p_new_node->parent = p_run; 
                
                break; 
            }
            else 
            {
                p_run = p_run->left; 
            }
        }
        else 
        {
            if(p_run->right == NULL)
            {
                p_run->right = p_new_node; 
                p_new_node->parent = p_run; 
                break; 
            }
            else 
            {
                p_run = p_run->right; 
            }
        }
    }
    p_bst->nr_elements += 1; 
    return (SUCCESS); 
}

void preorder_r(struct bst* p_bst)
{
    printf("[START]<->"); 
    preorder_node(p_bst->p_root_node); 
    puts("[END]"); 
}

void inorder_r(struct bst* p_bst)
{
    printf("[START]<->"); 
    inorder_node(p_bst->p_root_node); 
    puts("[END]"); 
}

void postorder_r(struct bst* p_bst)
{
    printf("[START]<->"); 
    postorder_node(p_bst->p_root_node); 
    puts("[END]"); 
}

int bst_max(struct bst* p_bst, int* p_max_data)
{
    struct bst_node* p_max_node = NULL; 

    if(p_bst->p_root_node == NULL)
        return (TREE_EMPTY); 
    
    p_max_node = get_max_node(p_bst->p_root_node); 
    *p_max_data = p_max_node->data; 

    return (SUCCESS); 
}

int bst_min(struct bst* p_bst, int* p_min_data)
{
    struct bst_node* p_min_node = NULL; 

    if(p_bst->p_root_node == NULL)
        return (TREE_EMPTY); 
    
    p_min_node = get_min_node(p_bst->p_root_node); 
    *p_min_data = p_min_node->data; 

    return (SUCCESS); 
}

int bst_inorder_successor(struct bst* p_bst, int ext_data, int* p_succ_data)
{
    struct bst_node* p_ext_node = NULL; 
    struct bst_node* p_succ_node = NULL; 

    p_ext_node = search_node(p_bst, ext_data); 
    if(p_ext_node == NULL)
        return (TREE_DATA_NOT_FOUND); 
    
    p_succ_node = inorder_successor(p_ext_node); 
    if(p_succ_node == NULL)
        return (TREE_NO_SUCCESSOR); 
    
    *p_succ_data = p_succ_node->data; 
    return (SUCCESS); 
}

int bst_inorder_predecessor(struct bst* p_bst, int ext_data, int* p_pred_data)
{
    struct bst_node* p_ext_node = NULL; 
    struct bst_node* p_pred_node = NULL; 

    p_ext_node = search_node(p_bst, ext_data); 
    if(p_ext_node == NULL)
        return (TREE_DATA_NOT_FOUND); 
    
    p_pred_node = inorder_predecessor(p_ext_node); 
    if(p_pred_node == NULL)
        return (TREE_NO_PREDECESSOR); 
    
    *p_pred_data = p_pred_node->data; 
    return (SUCCESS); 
}

int bst_search(struct bst* p_bst, int search_data)
{
    return (search_node(p_bst, search_data) != NULL); 
}

int remove_data(struct bst* p_bst, int r_data)
{
    struct bst_node* z = NULL;  /* pointer to node to be deleted */ 
    struct bst_node* w = NULL;  /* pointer to node to be deleted */ 

    z = search_node(p_bst, r_data); 
    if(z == NULL)
        return (TREE_DATA_NOT_FOUND); 
    
    if(z->left == NULL)
    {
        if(z->parent == NULL)
            p_bst->p_root_node = z->right; 
        else if(z == z->parent->left)
            z->parent->left = z->right; 
        else 
            z->parent->right = z->right; 
        if(z->right != NULL)
            z->right->parent = z->parent; 
    }
    else if(z->right == NULL)
    {
        if(z->parent == NULL)
            p_bst->p_root_node = z->left; 
        else if(z == z->parent->left) 
            z->parent->left = z->left; 
        else 
            z->parent->right = z->left; 
        if(z->left != NULL)
            z->left->parent = z->parent; 
    }
    else 
    {
        w = z->right; 
        while(w->left != NULL)
            w = w->left; 
        
        if(z->right != w)
        {
            w->parent->left = w->right; 
            if(w->right != NULL)
                w->right->parent = w->parent; 

            w->right = z->right; 
            w->right->parent = w; 
        }

        if(z->parent == NULL)
            p_bst->p_root_node = w; 
        else if(z == z->parent->left)
            z->parent->left = w; 
        else 
            z->parent->right = w; 
        w->parent = z->parent; 

        w->left = z->left; 
        w->left->parent = w; 
    }

    p_bst->nr_elements -= 1; 
    free(z); 
    z = NULL; 

    return (SUCCESS); 
}

int bst_remove_with_helper_routine(struct bst* p_bst, int r_data)
{
    struct bst_node* z = NULL;  /* pointer to node to be deleted */ 
    struct bst_node* w = NULL;  /* pointer to node to be deleted */ 

    z = search_node(p_bst, r_data); 
    if(z == NULL)
        return (TREE_DATA_NOT_FOUND); 
    
    if(z->left == NULL)
        transplant(p_bst, z, z->right); 
    else if(z->right == NULL)
        transplant(p_bst, z, z->left); 
    else 
    {
        w = inorder_successor(z); 

        if(z->right != w)
        {
            transplant(p_bst, w, w->right); 
            w->right = z->right; 
            w->right->parent = w; 
        }

        transplant(p_bst, z, w); 
        w->left = z->left; 
        w->left->parent = w; 
    }

    p_bst->nr_elements -= 1; 
    free(z); 
    z = NULL; 

    return (SUCCESS);     
}

void bst_destroy(struct bst** pp_bst)
{
    destroy_node((*pp_bst)->p_root_node); 
    free(*pp_bst);
    *pp_bst = NULL; 
}

/////////////////////////////////////////////////////////////////

void preorder_node(struct bst_node* p_root_node)
{
    if(p_root_node != NULL)
    {
        printf("[%d]<->", p_root_node->data); 
        preorder_node(p_root_node->left); 
        preorder_node(p_root_node->right); 
    }
}

void inorder_node(struct bst_node* p_root_node)
{
    static unsigned long long int i = 0; 
    if(p_root_node != NULL)
    {
        inorder_node(p_root_node->left); 
        printf("[%llu]:[%d]<->", ++i, p_root_node->data); 
        inorder_node(p_root_node->right); 
    }
}

void postorder_node(struct bst_node* p_root_node)
{
    if(p_root_node != NULL)
    {
        postorder_node(p_root_node->left); 
        postorder_node(p_root_node->right); 
        printf("[%d]<->", p_root_node->data); 
    }
}

void destroy_node(struct bst_node* p_root_node)
{
    if(p_root_node != NULL)
    {
        destroy_node(p_root_node->left); 
        destroy_node(p_root_node->right); 
        free(p_root_node); 
    }
}

struct bst_node* get_max_node(struct bst_node* p_node)
{
    struct bst_node* p_run = NULL; 

    p_run = p_node; 
    while(p_run->right != NULL)
        p_run = p_run->right; 

    return (p_run); 
}

struct bst_node* get_min_node(struct bst_node* p_node)
{
    struct bst_node* p_run = NULL; 

    p_run = p_node; 
    while(p_run->left != NULL)
        p_run = p_run->left; 

    return (p_run); 
}

struct bst_node* inorder_successor(struct bst_node* p_node)
{
    // दिलेल्या नोड चा इन ऑर्डर सकसेकर शोधून काढणे 
    struct bst_node* p_run = NULL; 
    
    struct bst_node* x = NULL, *y = NULL; 
    
    p_run = p_node; 
    if(p_run->right != NULL)
    {
        p_run = p_run->right; 
        while(p_run->left != NULL)
            p_run = p_run->left; 
        
        return (p_run); 
    }
    else 
    {
        x = p_run; 
        y = x->parent; 
        while(y != NULL && y->right == x)
        {
            x = y; 
            y = y->parent;
        }
        return (y); 
    }
}

struct bst_node* inorder_predecessor(struct bst_node* p_node)
{
     // दिलेल्या नोड चा इन ऑर्डर प्रेडेसेसर शोधून काढणे 
    struct bst_node* p_run = NULL; 
    struct bst_node* x = NULL, *y = NULL; 
    
    p_run = p_node; 
    if(p_run->left != NULL)
    {
        p_run = p_run->left; 
        while(p_run->right != NULL)
            p_run = p_run->right; 
        return (p_run); 
    }
    else 
    {
        x = p_run; 
        y = x->parent; 
        while(y != NULL && y->left == x)
        {
            x = y; 
            y = y->parent; 
        }
        return (y); 
    }
}

struct bst_node* search_node(struct bst* p_bst, int search_data)
{
    struct bst_node* p_run = NULL; 

    p_run = p_bst->p_root_node; 
    while(p_run != NULL)
    {
        if(search_data == p_run->data)
            break; 
        else if(search_data < p_run->data)
            p_run = p_run->left; 
        else 
            p_run = p_run->right; 
    }

    return (p_run); 
}

void transplant(struct bst* p_bst, struct bst_node* u, struct bst_node* v)
{
    if(u->parent == NULL)
        p_bst->p_root_node = v; 
    else if(u == u->parent->left)
        u->parent->left = v; 
    else 
        u->parent->right = v; 

    if(v != NULL)
        v->parent = u->parent; 
}

int bst_is_empty(struct bst* p_bst)
{
    return (p_bst->p_root_node == NULL); 
}

unsigned long long int get_nr_elements(struct bst* p_bst)
{
    return (p_bst->nr_elements); 
}

struct bst_node* get_bst_node(int new_element)
{
    struct bst_node* p_new_node = NULL; 

    p_new_node = (struct bst_node*)malloc(sizeof(struct bst_node)); 
    if(p_new_node == NULL)
    {
        fprintf(stderr, "malloc:fatal:out of virtual memory\n"); 
        exit(EXIT_FAILURE); 
    }

    p_new_node->data = new_element; 
    p_new_node->left = NULL; 
    p_new_node->right = NULL; 
    p_new_node->parent = NULL; 

    return (p_new_node); 
}