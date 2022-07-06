typedef int data_t;
typedef int status_t;
typedef struct node list_t;
typedef struct node node_t;

#define SUCCESS             1
#define NODE_NOT_FOUND      2
#define LIST_EMPTY          3

struct node {

    data_t data;
    struct node* previous;
    struct node* next;
};

list_t* create_list();
static node_t* get_node(data_t new_data);
static void* xcalloc(unsigned int no_of_elements, unsigned int size);
status_t insert_start(list_t* list, data_t new_data);
static void generic_insert(node_t* beg, node_t* mid, node_t* end);
status_t insert_end(list_t* list, data_t new_data);
void show_list(list_t* list);
status_t insert_before(list_t* list, data_t e_data, data_t new_data);
static node_t* search_node(list_t* list, data_t e_data);
status_t insert_after(list_t* list, data_t e_data, data_t new_data);
status_t get_start(list_t* list, data_t* dataptr);
int is_empty(list_t* list);
status_t get_end(list_t* list, data_t* dataptr);
status_t pop_start(list_t* list, data_t* dataptr);
static void generic_delete(node_t* node);
status_t pop_end(list_t* list, data_t* dataptr);
status_t remove_start(list_t* list);
status_t remove_end(list_t* list);
status_t delete_data(list_t* list, data_t e_data);
status_t find_data(list_t* list, data_t data);
int get_length(list_t* list);
status_t concat_mutable(list_t* list1, list_t* list2);
list_t* concat_immutable(list_t* list1, list_t* list2);
status_t destroy_list(list_t** lsptr);
list_t* merge(list_t* list1, list_t* list2);
list_t* reverse_immutable(list_t* list);
status_t reverse_mutable(list_t* list);