#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t* create_list() {

    list_t* list = NULL;
    list = get_node(-1);
    list -> previous = list;
    list -> next = list;

    return list;
}

status_t insert_start(list_t* list, data_t new_data) {

    generic_insert(list, get_node(new_data), list -> next);
    return SUCCESS;
}

status_t insert_end(list_t* list, data_t new_data) {

    generic_insert(list -> previous, get_node(new_data), list);
    return SUCCESS;
}

void show_list(list_t* list) {

    for(node_t* ptr = list -> next; ptr != list; ptr = ptr -> next)
        printf("%d ", ptr -> data);
    printf("\n");
}

status_t insert_before(list_t* list, data_t e_data, data_t new_data) {

    node_t* e_node = search_node(list, e_data);

    if(e_node == NULL)
        return NODE_NOT_FOUND;    

    generic_insert(e_node -> previous, get_node(new_data), e_node);
    return SUCCESS;
}

status_t insert_after(list_t* list, data_t e_data, data_t new_data) {

    node_t* e_node = search_node(list, e_data);

    if(e_node == NULL)
        return NODE_NOT_FOUND;

    generic_insert(e_node, get_node(new_data), e_node -> next);
    return SUCCESS;
}

status_t get_start(list_t* list, data_t* dataptr) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;

    *dataptr = list -> next -> data;
    return SUCCESS;
}

status_t get_end(list_t* list, data_t* dataptr) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;
    
    *dataptr = list -> previous -> data;
    return SUCCESS;
}

status_t pop_start(list_t* list, data_t* dataptr) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;

    *dataptr = list -> next -> data;
    generic_delete(list -> next);
    return SUCCESS;
}

status_t pop_end(list_t* list, data_t* dataptr) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;

    *dataptr = list -> previous -> data;
    generic_delete(list -> previous);
    return SUCCESS;
}

status_t remove_start(list_t* list) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;

    generic_delete(list -> next);
    return SUCCESS;
}

status_t remove_end(list_t* list) {

    if(is_empty(list) == 1)
        return LIST_EMPTY;

    generic_delete(list -> previous);
    return SUCCESS;
}

status_t delete_data(list_t* list, data_t e_data) {

    node_t* e_node = search_node(list, e_data);
    if(e_node == NULL)
        return NODE_NOT_FOUND;

    generic_delete(e_node);
    return SUCCESS; 
}

int is_empty(list_t* list) {

    if(list -> previous == list && list -> next == list)
        return 1; 
    else 
        return 0;
}

status_t find_data(list_t* list, data_t data) {

    node_t* e_node = search_node(list, data);
    return (e_node != NULL);
}

int get_length(list_t* list) {

    int length = 0;
    for(node_t* ptr = list -> next; ptr != list; ptr = ptr -> next, length++)
        ;
    
    return length;
}

status_t concat_mutable(list_t* list1, list_t* list2) {

    if(is_empty(list2) == 1)    
        return SUCCESS;

    list1 -> previous -> next = list2 -> next;
    list2 -> next -> previous = list1 -> previous;
    list1 -> previous = list2 -> previous;
    list2 -> previous -> next = list1;

    free(list2);
    list2 = NULL;

    return SUCCESS;
}

list_t* concat_immutable(list_t* list1, list_t* list2) {

    list_t* merged_list = NULL;
    merged_list = create_list();

    for(node_t* ptr = list1 -> next; ptr != list1; ptr = ptr -> next)
        insert_end(merged_list, ptr -> data);

    for(node_t* ptr = list2 -> next; ptr != list2; ptr = ptr -> next)
        insert_end(merged_list, ptr -> data);

    return merged_list;
}

status_t destroy_list(list_t** lsptr) {

    list_t* list = *lsptr;
    node_t* ptr = list -> next;
    node_t* ptr_next = NULL;

    while(ptr != list) {

        ptr_next = ptr -> next;
        free(ptr);
        ptr = ptr_next;
    }

    free(list);
    list = NULL;
    *lsptr = NULL;
    return SUCCESS;
}

list_t* merge(list_t* list1, list_t* list2) {

    list_t* merged_list = create_list();

    node_t* ptr1 = list1 -> next;
    node_t* ptr2 = list2 -> next;

    while(1) {
        if(ptr1 == list1) {
            for(; ptr2 != list2; ptr2 = ptr2 -> next)
                insert_end(merged_list, ptr2 -> data);
            break;
        } 

        if(ptr2 == list2) {
            for(; ptr1 != list1; ptr1 = ptr1 -> next)
                insert_end(merged_list, ptr1 -> data);
            break;
        }

        if(ptr1 -> data <= ptr2 -> data) {
            insert_end(merged_list, ptr1 -> data);
            ptr1 = ptr1 -> next;
        }

        else {
            insert_end(merged_list, ptr2 -> data);
            ptr2 = ptr2 -> next;
        }
    }

    return merged_list;
}   

list_t* reverse_immutable(list_t* list) {

    list_t* reversed_list = create_list();

    for(node_t* ptr = list -> previous; ptr != list; ptr = ptr -> previous)
        insert_end(reversed_list, ptr -> data);

    return reversed_list;
}

status_t reverse_mutable(list_t* list) {

    node_t* last = list -> previous;
    node_t* original_last = last;
    node_t* ptr_previous = NULL;

    for(node_t* ptr = last -> previous; ptr != list; ptr = ptr_previous) {

        ptr_previous = ptr -> previous;
        ptr -> previous = last; 
        last -> next = ptr;
        last = ptr;
    }

    original_last -> previous = list;
    list -> next = original_last;

    list -> previous = last;
    last -> next = list;

    return SUCCESS;
}

static node_t* get_node(data_t new_data) {

    node_t* node = NULL;
    node = (node_t*)xcalloc(1, sizeof(node_t));
    node -> data = new_data;
    node -> previous = NULL;
    node -> next = NULL;

    return node;
}

static void* xcalloc(unsigned int no_of_elements, unsigned int size) {

    void* node = NULL;
    node = calloc(no_of_elements, size);

    if(node == NULL) {
        fprintf(stderr, "fatal:calloc:out of virtual memory");
        exit(EXIT_FAILURE);
    }

    return node;
}

static void generic_insert(node_t* beg, node_t* mid, node_t* end) {

    mid -> next = end;
    mid -> previous = beg;
    beg -> next = mid;
    end -> previous = mid;
}

static node_t* search_node(list_t* list, data_t e_data) {

    node_t* ptr = list -> next;

    while(ptr != list) {

        if(ptr -> data == e_data)
            return ptr;

        ptr = ptr -> next;
    }

    return NULL;
}

static void generic_delete(node_t* node) {

    node -> previous -> next = node -> next;
    node -> next -> previous = node -> previous;

    free(node);
    node = NULL;
}