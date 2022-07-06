#ifndef _QUEUE_H 
#define _QUEUE_H 

#include "list.h"

#define QUEUE_EMPTY LIST_EMPTY

typedef list_t queue_t; 

queue_t* create_queue(void); 
status_t insert(queue_t* p_queue, data_t new_data); 
status_t peek(queue_t* p_queue, data_t* p_peeked_data); 
status_t remove(queue_t* p_queue, data_t* p_removed_data); 
status_t is_queue_empty(queue_t* p_queue); 
status_t destroy_queue(queue_t** pp_queue); 

#endif /* _QUEUE_H */ 