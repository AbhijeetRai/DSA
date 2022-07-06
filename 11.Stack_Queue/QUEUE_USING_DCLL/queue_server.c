#include "queue.h"

queue_t* create_queue(void)
{
    return create_list(); 
}

status_t insert(queue_t* p_queue, data_t new_data)
{
    return insert_end(p_queue, new_data); 
}

status_t peek(queue_t* p_queue, data_t* p_peeked_data)
{
    return get_start(p_queue, p_peeked_data); 
}

status_t remove(queue_t* p_queue, data_t* p_removed_data)
{
    return pop_start(p_queue, p_removed_data); 
}

status_t is_queue_empty(queue_t* p_queue)
{
    return is_list_empty(p_queue); 
}

status_t destroy_queue(queue_t** pp_queue)
{
    return destroy_list(pp_queue); 
}