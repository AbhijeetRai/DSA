#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS                 1
#define TREE_EMPTY              2
#define TREE_DATA_NOT_FOUND     3
#define TREE_NO_SUCCESSOR       4
#define TREE_NO_PREDECESSOR     5

struct bst {

    struct bst_node* root;
    long long unsigned int nr_elements;
};

struct bst_node {

    int data;
    struct bst_node* left;
    struct bst_node* right;
    struct bst_node* parent;
};


struct bst* create_bst();
int insert_bst(struct bst* tree, int data);
struct bst_node* get_node(int data);

void preorder(struct bst* tree);
void preorder_node(struct bst_node* node);
void inorder(struct bst* tree);
void inorder_node(struct bst_node* node);
void postorder(struct bst* tree);
void postorder_node(struct bst_node* node);

int get_minimum(struct bst* tree, int* dataptr);
struct bst_node* get_minimum_node(struct bst_node* node);
int get_maximum(struct bst* tree, int* dataptr);
struct bst_node* get_maximum_node(struct bst_node* node);

int search_tree(struct bst* tree, int data);
struct bst_node* search_node(struct bst_node* node, int data);

void destroy_tree(struct bst** treeptr);
void destroy_node(struct bst_node* node);

int get_successor(struct bst* tree, int e_data, int* dataptr);
struct bst_node* get_successor_node(struct bst_node* e_node);

int get_predecessor(struct bst* tree, int e_data, int* dataptr);
struct bst_node* get_predecessor_node(struct bst_node* e_node);

int delete_node(struct bst* tree, int data);
int delete_node_with_helper_rountine(struct bst* tree, int data);
void transplant(struct bst* tree, struct bst_node* u, struct bst_node* v);

int main(void) {

    struct bst* tree = create_bst();
    int dataarr[] = {100, 90, 80, 70, 85};

    for(int i = 0; i < sizeof(dataarr) / sizeof(int); ++i) {

        int status = insert_bst(tree, dataarr[i]);
        assert(status == SUCCESS);
    }

    inorder(tree);
    int status = delete_node(tree, 100);
    printf("delete_status = %d\n", status);
    inorder(tree);
    return 0;
}

struct bst* create_bst() {

    struct bst* tree = (struct bst*)malloc(sizeof(struct bst) * 1);

    if(tree == NULL) {
        fprintf(stderr, "fatal:malloc:out of virtual memory\n");
        exit(EXIT_FAILURE);
    }

    tree -> root = NULL;
    tree -> nr_elements = 0;

    return tree;
}

int insert_bst(struct bst* tree, int data) {

    struct bst_node* node = get_node(data);

    if(tree -> root == NULL) {
        tree -> root = node;
        tree -> nr_elements += 1;
        return SUCCESS;
    }

    struct bst_node* p_run = tree -> root;

    while(1) {
        if(data <= p_run -> data) {
            if(p_run -> left == NULL) {
                p_run -> left = node;
                node -> parent = p_run;
                tree -> nr_elements += 1;
                return SUCCESS;
            }
            else
                p_run = p_run -> left;
        }

        else {
            if(p_run -> right == NULL) {
                p_run -> right = node;
                node -> parent = p_run;
                tree -> nr_elements += 1;
                return SUCCESS;
            }
            else
                p_run = p_run -> right;
        }
    }
}

struct bst_node* get_node(int data) {

    struct bst_node* node = (struct bst_node*)malloc(sizeof(struct bst_node) * 1);
    if(node == NULL) {
        fprintf(stderr, "fatal:malloc:out of virtual memory\n");
        exit(EXIT_FAILURE);
    }

    node -> data = data;
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = NULL;

    return node;
}

void preorder(struct bst* tree) {
    preorder_node(tree -> root);
    printf("\n");
}

void preorder_node(struct bst_node* node) {

    if(node != NULL) {
        printf("%d ", node -> data);
        preorder_node(node -> left);
        preorder_node(node -> right);
    }
}

void inorder(struct bst* tree) {
    inorder_node(tree -> root);
    printf("\n");
}

void inorder_node(struct bst_node* node) {

    if(node != NULL) {
        inorder_node(node -> left);
        printf("%d ", node -> data);
        inorder_node(node -> right);
    }
}

void postorder(struct bst* tree) {
    postorder_node(tree -> root);
    printf("\n");
}

void postorder_node(struct bst_node* node) {
    if(node != NULL) {
        postorder_node(node -> left);
        postorder_node(node -> right);
        printf("%d ", node -> data);
    }
}

int get_minimum(struct bst* tree, int* dataptr) {

    if(tree -> root == NULL)
        return TREE_EMPTY;

    struct bst_node* node = get_minimum_node(tree -> root);
    *dataptr = node -> data;
    return SUCCESS;
}

struct bst_node* get_minimum_node(struct bst_node* node) {

    while(node -> left != NULL)
        node = node -> left;

    return node;
}

int get_maximum(struct bst* tree, int* dataptr) {

    if(tree -> root == NULL)
        return TREE_EMPTY;

    struct bst_node* node = get_maximum_node(tree -> root);
    *dataptr = node -> data;
    return SUCCESS;
}

struct bst_node* get_maximum_node(struct bst_node* node) {

    while(node -> right != NULL)
        node = node -> right;

    return node;
}

int search_tree(struct bst* tree, int data) {

    if(tree -> root == NULL)
        return TREE_EMPTY;

    struct bst_node* node = search_node(tree -> root, data);

    if(node == NULL)
        return TREE_DATA_NOT_FOUND;
    else
        return SUCCESS;
}

struct bst_node* search_node(struct bst_node* node, int data) {

    while(node != NULL) {
        if(data == node -> data)
            return node;
        else if(data > node -> data)
            node = node -> right;
        else
            node = node -> left;
    }
    return node;
}

void destroy_tree(struct bst** treeptr) {

    destroy_node((*treeptr) -> root);
    free(*treeptr);
    *treeptr = NULL;
}

void destroy_node(struct bst_node* node) {

    if(node != NULL) {
        destroy_node(node -> left);
        destroy_node(node -> right);
        free(node);
    }
}

int get_successor(struct bst* tree, int e_data, int* dataptr) {

    struct bst_node* node = search_node(tree -> root, e_data);
    if(node == NULL)
        return TREE_DATA_NOT_FOUND;

    struct bst_node* successor = get_successor_node(node);

    if (successor == NULL)
        return TREE_NO_SUCCESSOR;

    *dataptr = successor -> data;
    return SUCCESS;
}

//SUCCESSOR is minimum of RST
//if RST is null, you are (e_node)maximum of LST of node to be found
struct bst_node* get_successor_node(struct bst_node* e_node) {

    struct bst_node* x = NULL;
    struct bst_node *y = NULL;

    if(e_node -> right != NULL)
        return get_minimum_node(e_node -> right);
    else {
        x = e_node;
        y = x -> parent;
        while(y!= NULL && y -> left != x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }
}

int get_predecessor(struct bst* tree, int e_data, int* dataptr) {

    struct bst_node* e_node = search_node(tree -> root, e_data);
    if(e_node == NULL)
        return TREE_DATA_NOT_FOUND;

    struct bst_node* pred = get_predecessor_node(e_node);

    if(pred == NULL)
        return TREE_NO_PREDECESSOR;

    *dataptr = pred -> data;
    return SUCCESS;
}

//Maximum of LST is predecessor
//If LST is null, you are(e_node) minimum of RST of node to be found
struct bst_node* get_predecessor_node(struct bst_node* e_node) {

    struct bst_node* x = NULL;
    struct bst_node* y = NULL;

    if(e_node -> left != NULL)
        return get_maximum_node(e_node -> left);

    else {
        x = e_node;
        y = x -> parent;

        while(y != NULL && x != y -> right) {
            x = y;
            y = y -> parent;
        }
    }

    return y;
}

/**
 * DELETE ALGORITHM:
 *      1) LST is null, RST may or may not be NULL
 *      2) LST is not null, RST is null
 *      3) LST is not null, RST is null
                i)  Inorder successor of node to be deleted is the right child
                ii) Inorder successor of node to be deleted is not the right child
 */

int delete_node(struct bst* tree, int data) {

    struct bst_node* z = search_node(tree -> root, data);
    if(z == NULL)
        return TREE_DATA_NOT_FOUND;

    if(z -> left == NULL) {

        if(z -> parent == NULL)
            tree -> root = z -> right;

        else if(z == z -> parent -> right)
            z -> parent -> right = z -> right;

        else
            z -> parent -> left = z -> right;

        if(z -> right != NULL)
            z -> right -> parent = z -> parent;
    }

    else if(z -> right == NULL) {

        if(z -> parent == NULL)
            tree -> root = z -> left;

        else if(z == z -> parent -> right)
            z -> parent -> right = z -> left;
        else
            z -> parent -> left = z -> left;

        if(z -> left != NULL)
            z -> left -> parent = z -> parent;
    }

    else {

        struct bst_node* w = get_successor_node(z);

        if(w != z -> right) {
            w -> parent -> left = w -> right;
            if(w -> right != NULL)
                w -> right -> parent = w -> parent;

            w -> right = z -> right;
            z -> right -> parent = w;
        }
        w -> left = z -> left;
        z -> left -> parent = w;

        if(z -> parent == NULL)
            tree -> root = w;

        else if(z == z -> parent -> right)
            z -> parent -> right = w;

        else
            z -> parent -> left = w;
        w -> parent = z -> parent;
    }

    tree -> nr_elements -= 1;
    free(z);
    z = NULL;
    return SUCCESS;
}

int delete_node_with_helper_rountine(struct bst* tree, int data) {

    struct bst_node* z = search_node(tree -> root, data);
    if(z == NULL)
        return TREE_DATA_NOT_FOUND;

    if(z -> left == NULL)
        transplant(tree, z, z -> right);

    else if(z -> right == NULL)
        transplant(tree, z, z -> left);

    else {
        struct bst_node* w = get_successor_node(z);

        if(w != z -> right) {
            transplant(tree, w, w -> right);
            w -> right = z -> right;
            z -> right -> parent = w;
        }
        w -> left = z -> left;
        z -> left -> parent = w;
        transplant(tree, z, w);
    }

    tree -> nr_elements -= 1;
    free(z);
    z = NULL;
    return SUCCESS;
}

void transplant(struct bst* tree, struct bst_node* u, struct bst_node* v) {

    if(u -> parent == NULL)
        tree -> root = v;

    else if(u == u -> parent -> left)
        u -> parent -> left = v;

    else
        u -> parent -> right = v;

    if(v != NULL)
        v -> parent = u -> parent;
}
