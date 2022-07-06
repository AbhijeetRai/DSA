#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "queue.h"

int main(void)
{
    queue_t* p_queue = NULL; 
    data_t data; 

    p_queue = create_queue(); 
    assert(p_queue); 
    assert(is_queue_empty(p_queue) == TRUE); 
    assert(peek(p_queue, &data) == QUEUE_EMPTY);
    assert(remove(p_queue, &data) == QUEUE_EMPTY);  

    for(data = 0; data < 8; ++data)
        assert(insert(p_queue, (data + 1)*10) == SUCCESS);

    assert(is_queue_empty(p_queue) == FALSE); 

    data = -1; 
    assert(peek(p_queue, &data) == SUCCESS); 
    printf("First data = %d\n", data); 

    data = -1; 
    assert(remove(p_queue, &data) == SUCCESS); 
    printf("Removed data = %d\n", data); 

    while(is_queue_empty(p_queue) != TRUE)
    {
        assert(remove(p_queue, &data)); 
        printf("Removed data  = %d\n", data); 
    }

    assert(destroy_queue(&p_queue) == SUCCESS && p_queue == NULL); 

    exit(EXIT_SUCCESS); 
}
