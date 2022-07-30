#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

/* Symbolic Constants */ 
#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 

#define G_VEXISTS   2 
#define G_EEXISTS   3 
#define G_VINVALID  4 
#define G_EINVALID  5
#define G_CORRUPTED 6 

/* structure layout */ 
struct hnode
{
    int v; 
    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode
{
    int v; 
    struct hnode* ph_list; 

    struct vnode* prev; 
    struct vnode* next; 
}; 

struct graph
{
    struct vnode* pv_list; 
    unsigned long long int nr_vert; 
    unsigned long long int nr_edges; 
}; 

struct edge
{
    int v_start; 
    int v_end; 
}; 

/*  graph management -> interface functions */ 
struct graph* create_graph(void); 
int add_vertex(struct graph* g, int v); 
int add_edge(struct graph* g, int v_start, int v_end); 
int remove_vertex(struct graph* g, int v); 
int remove_edge(struct graph* g, int v_start, int v_end); 
void print_graph(struct graph* g, const char* msg); 
int destroy_graph(struct graph** pp_graph); 

/* graph management -> vertical list management -> interface functions */ 
struct vnode* v_create_list(void); 
int v_insert_end(struct vnode* pv_list, int v); 

/* graph management -> vertical list management -> interface functions */ 
void v_generic_insert(struct vnode* p_beg, struct vnode* p_mid, 
                        struct vnode* p_end); 
void v_generic_delete(struct vnode* p_delete_node); 
struct vnode* v_search_node(struct vnode* pv_list, int v); 
struct vnode* v_get_node(int v); 

/* graph management -> horizontal list management -> interface functions */ 
struct hnode* h_create_list(void); 
int h_insert_end(struct hnode* ph_list, int v); 

/* graph management -> vertical list management -> interface functions */ 
void h_generic_insert(struct hnode* p_beg, struct hnode* p_mid, 
                        struct hnode* p_end); 
void h_generic_delete(struct hnode* p_delete_node); 
struct hnode* h_search_node(struct hnode* ph_list, int v); 
struct hnode* h_get_node(int v); 

void* xcalloc(size_t nr_elements, size_t size_per_element); 

int main(void)
{
    struct graph* g = NULL; 
    int V[] = {1, 2, 3, 4, 5, 6}; 
    struct edge E[] = { {1, 2}, {1, 6}, 
                        {2, 6}, {2, 5}, {2, 3}, 
                        {3, 5}, {3, 4}, 
                        {4, 5}, 
                        {5, 6}
                    }; 
    int i; 
    int status; 

    g = create_graph(); 
    for(i = 0; i < sizeof(V)/sizeof(V[0]); ++i)
        assert(add_vertex(g, V[i]) == SUCCESS);
    for(i = 0; i < sizeof(E)/sizeof(E[0]); ++i)
        assert(add_edge(g, E[i].v_start, E[i].v_end) == SUCCESS); 
    print_graph(g, "Initial State:"); 
    
    status = remove_edge(g, 1, 6); 
    assert(status == SUCCESS); 
    status = remove_edge(g, 5, 3); 
    assert(status == SUCCESS); 

    print_graph(g, "graph after removing edges, (1, 6), (5, 3)"); 

    status = remove_vertex(g, 2); 
    assert(status == SUCCESS); 
    print_graph(g, "graph after removing vertex 2"); 

    status = add_vertex(g, 7); 
    assert(status == SUCCESS); 

    status = add_edge(g, 1, 7); 
    assert(status == SUCCESS); 

    status = add_edge(g, 1, 4); 
    assert(status == SUCCESS); 

    status = add_edge(g, 3, 7); 
    assert(status == SUCCESS); 

    status = add_edge(g, 5, 7); 
    assert(status == SUCCESS); 

    print_graph(g, "graph after adding vertex 7 and adding edges (1, 7), (1, 4), (3, 7), (5, 7):"); 

    status = destroy_graph(&g); 
    assert(status == SUCCESS && g == NULL); 

    return (EXIT_SUCCESS); 
}

/*  graph management -> interface functions */ 
struct graph* create_graph(void)
{
    struct graph* g = NULL; 

    g = (struct graph*)xcalloc(1, sizeof(struct graph)); 
    g->pv_list = v_create_list();  
    g->nr_vert = 0; 
    g->nr_edges = 0; 

    return (g); 
}

int add_vertex(struct graph* g, int v)
{
    struct vnode* pv_node = NULL; 
    int status; 

    pv_node = v_search_node(g->pv_list, v); 
    if(pv_node != NULL)
        return (G_VEXISTS); 

    status = v_insert_end(g->pv_list, v); 
    assert(status == SUCCESS); 
    g->nr_vert += 1; 

    return (SUCCESS); 
}

int add_edge(struct graph* g, int v_start, int v_end)
{
    struct vnode* pv_start = NULL; 
    struct vnode* pv_end = NULL; 
    struct hnode* ph_start_in_end = NULL; 
    struct hnode* ph_end_in_start = NULL; 
    int status; 

    pv_start = v_search_node(g->pv_list, v_start); 
    if(pv_start == NULL)
        return (G_VINVALID); 

    pv_end = v_search_node(g->pv_list, v_end); 
    if(pv_end == NULL)
        return (G_VINVALID); 

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);

    if(ph_end_in_start && ph_start_in_end)
        return (G_EEXISTS); 

    if((ph_end_in_start != NULL) ^ (ph_start_in_end != NULL))
        return (G_CORRUPTED);  

    status = h_insert_end(pv_start->ph_list, v_end); 
    assert(status == SUCCESS); 

    status = h_insert_end(pv_end->ph_list, v_start); 
    assert(status == SUCCESS); 

    g->nr_edges += 1; 

    return (SUCCESS); 
}

int remove_vertex(struct graph* g, int v)
{
    struct vnode* pv_delete_node = NULL, *pv_for_adj_v = NULL; 
    struct hnode* ph_run = NULL, *ph_run_next = NULL; 
    struct hnode* ph_for_adj_node = NULL; 

    pv_delete_node = v_search_node(g->pv_list, v); 
    if(pv_delete_node == NULL)
        return (G_VINVALID); 
    
    for(ph_run = pv_delete_node->ph_list->next; ph_run != pv_delete_node->ph_list; ph_run = ph_run_next)
    {
        ph_run_next = ph_run->next; 
        pv_for_adj_v = v_search_node(g->pv_list, ph_run->v); 
        if(pv_for_adj_v == NULL)
            return (G_CORRUPTED); 
        ph_for_adj_node = h_search_node(pv_for_adj_v->ph_list, v); 
        if(ph_for_adj_node == NULL)
            return (G_CORRUPTED); 
        h_generic_delete(ph_for_adj_node);         
        free(ph_run); 
        g->nr_edges -= 1; 
    }
    free(pv_delete_node->ph_list); 
    v_generic_delete(pv_delete_node); 
    g->nr_vert -=1; 

    return (SUCCESS); 
}

int remove_edge(struct graph* g, int v_start, int v_end)
{
    struct vnode* pv_start = NULL; 
    struct vnode* pv_end = NULL; 
    struct hnode* ph_start_in_end = NULL; 
    struct hnode* ph_end_in_start = NULL; 
    int status; 

    pv_start = v_search_node(g->pv_list, v_start); 
    if(pv_start == NULL)
        return (G_VINVALID); 

    pv_end = v_search_node(g->pv_list, v_end); 
    if(pv_end == NULL)
        return (G_VINVALID); 

    ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 
    ph_start_in_end = h_search_node(pv_end->ph_list, v_start);

    if((ph_end_in_start == NULL)  && (ph_start_in_end == NULL))
        return (G_EINVALID); 

    if((ph_end_in_start != NULL) ^ (ph_start_in_end != NULL))
        return (G_CORRUPTED);      

    h_generic_delete(ph_end_in_start); 
    h_generic_delete(ph_start_in_end); 
    g->nr_edges -= 1; 

    return (SUCCESS); 
}

void print_graph(struct graph* g, const char* msg)
{
    struct vnode* pv_run = NULL; 
    struct hnode* ph_run = NULL; 

    if(msg)
        puts(msg); 

    printf("|V|=%llu, |E|=%llu\n", g->nr_vert, g->nr_edges); 
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        printf("[%d]\t->\t", pv_run->v); 
        for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next)
            printf("[%d]<->", ph_run->v); 
        puts("[END]"); 
    }
}

int destroy_graph(struct graph** pp_graph)
{
    struct vnode* pv_run=NULL, *pv_run_next=NULL; 
    struct hnode* ph_run=NULL, *ph_run_next = NULL; 
    struct graph* g = NULL; 

    g = *pp_graph; 
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run_next)
    {
        pv_run_next = pv_run->next; 
        for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run_next)
        {
            ph_run_next = ph_run->next; 
            free(ph_run); 
        }
        free(pv_run->ph_list); 
        free(pv_run); 
    }
    free(g->pv_list); 
    free(g); 

    *pp_graph = NULL; 
    return (SUCCESS); 
}

/* graph management -> vertical list management -> interface functions */ 
struct vnode* v_create_list(void)
{
    struct vnode* pv_list = NULL; 

    pv_list = (struct vnode*)xcalloc(1, sizeof(struct vnode)); 
    pv_list->v = -1; 
    pv_list->ph_list = NULL; 
    pv_list->prev = pv_list; 
    pv_list->next = pv_list; 

    return (pv_list); 
}

int v_insert_end(struct vnode* pv_list, int v)
{
    v_generic_insert(pv_list->prev, v_get_node(v), pv_list);
    return (SUCCESS);  
}

/* graph management -> vertical list management -> interface functions */ 
void v_generic_insert(struct vnode* p_beg, struct vnode* p_mid, 
                        struct vnode* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void v_generic_delete(struct vnode* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

struct vnode* v_search_node(struct vnode* pv_list, int v)
{
    struct vnode* pv_run = NULL; 

    for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
        if(pv_run->v == v)
            return (pv_run); 

    return (NULL); 
}

struct vnode* v_get_node(int v)
{
    struct vnode* pv_node = NULL; 

    pv_node = (struct vnode*)xcalloc(1, sizeof(struct vnode)); 
    pv_node->v = v; 
    pv_node->ph_list = h_create_list(); 

    return (pv_node); 
}

/* graph management -> horizontal list management -> interface functions */ 
struct hnode* h_create_list(void)
{
    struct hnode* ph_list = NULL; 

    ph_list = h_get_node(-1); 
    ph_list->prev = ph_list; 
    ph_list->next = ph_list; 

    return (ph_list); 
}

int h_insert_end(struct hnode* ph_list, int v)
{
    h_generic_insert(ph_list->prev, h_get_node(v), ph_list); 
    return (SUCCESS); 
}

/* graph management -> vertical list management -> interface functions */ 
void h_generic_insert(struct hnode* p_beg, struct hnode* p_mid, 
                        struct hnode* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void h_generic_delete(struct hnode* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev; 
    free(p_delete_node); 
}

struct hnode* h_search_node(struct hnode* ph_list, int v)
{
    struct hnode* p_run = NULL; 

    for(p_run = ph_list->next; p_run != ph_list; p_run = p_run->next)
        if(p_run->v == v)
            return (p_run); 

    return (NULL); 
}

struct hnode* h_get_node(int v)
{
    struct hnode* ph_node = NULL; 

    ph_node = (struct hnode*)xcalloc(1, sizeof(struct hnode)); 
    ph_node->v = v; 

    return (ph_node); 
}

void* xcalloc(size_t nr_elements, size_t size_per_element)
{
    void* p = NULL; 

    p = calloc(nr_elements, size_per_element); 
    if(p == NULL)
    {
        fprintf(stderr, "xcalloc:out of virtual memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}