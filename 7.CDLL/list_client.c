#include <stdio.h>
#include <assert.h>
#include "list.h"

int main() {

    list_t* list1 = create_list();
    list_t* list2 = create_list();

    insert_end(list1, 10);
    insert_end(list1, 20);
    insert_end(list1, 30);
    
    insert_end(list2, 5);
    insert_end(list2, 15);
    insert_end(list2, 35);

    list_t* merged_list = merge(list1, list2);
    show_list(merged_list);

    reverse_mutable(merged_list);
    show_list(merged_list);

    return 0;
}