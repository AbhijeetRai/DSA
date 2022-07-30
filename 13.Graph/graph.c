#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define SUCCESS 	1
#define G_VEXISTS	2
#define G_EEXISTS	3
#define G_VINVALID 	4
#define G_EINVALID  5
#define G_CORRUPTED 6


struct hnode {

	struct hnode* previous; 
	int v; 
	struct hnode* next;
};

struct vnode {

	struct vnode* previous; 
	struct vnode* next;
	int v; 
	struct hnode* ph_list;
};	

struct graph {

	struct vnode* pv_list;
	long long unsigned int nr_vertices; 
	long long unsigned int nr_edges; 
};

struct edge {

	int v_start; 
	int v_end;
};


struct graph* create_graph();
void* xcalloc(long long unsigned int nr_elements, long long unsigned int size);
int add_vertex(struct graph* g, int vertex);
int add_edge(struct graph* g, int v_start, int v_end);
int remove_vertex(struct graph* g, int vertex);
int remove_edge(struct graph* g, int v_start, int v_end);
void print_graph(struct graph* g, char* message);
int destroy_graph(struct graph** g);

struct vnode* v_create_list();
struct vnode* v_search_node(struct vnode* vlist, int vertex);
int v_insert_end(struct vnode* pv_list, int vertex);
void v_generic_insert(struct vnode* beg, struct vnode* mid, struct vnode* end);
struct vnode* v_get_node(int vertex);
void v_generic_delete(struct vnode* v_delete_node);

struct hnode* h_create_list();
struct hnode* h_search_node(struct hnode* ph_list, int vertex);
int h_insert_end(struct hnode* ph_list, int vertex);
void h_generic_insert(struct hnode* beg, struct hnode* mid, struct hnode* end);
struct hnode* h_get_node(int vertex);
void h_generic_delete(struct hnode* h_delete_node);


int main() {

	struct graph* g = create_graph();
	int V[] = {1, 2, 3, 4, 5, 6};
	for(int i = 0; i < sizeof(V) / sizeof(V[0]); ++i)
		assert(add_vertex(g, V[i]) == SUCCESS);

	struct edge E[] = {	{1, 2}, {1, 6},
						{2, 3}, {2, 5}, {2, 6},
						{3, 4}, {3, 5},
						{4, 5}, 
						{5, 6}
					};

	for(int i = 0; i < sizeof(E)/sizeof(E[0]); ++i)
		assert(add_edge(g, E[i].v_start, E[i].v_end) == SUCCESS);

	destroy_graph(&g);
	assert(g == NULL);

	return 0;
}

struct graph* create_graph() {

	struct graph* g = (struct graph *)xcalloc(1, sizeof(struct graph));
	g -> pv_list = v_create_list();
	g -> nr_vertices = 0; 
	g -> nr_edges = 0;

	return g;
}

void* xcalloc(long long unsigned int nr_elements, long long unsigned int size) {

	void* ptr = calloc(nr_elements, size);
	if(ptr == NULL) {
		fprintf(stderr, "fatal:calloc:out of virtual memory\n");
		exit(EXIT_FAILURE);
	}
	return ptr;
}

struct vnode* v_create_list() {

	struct vnode* vnode = (struct vnode*)xcalloc(1, sizeof(struct vnode));
	vnode -> v = -1;
	vnode -> previous = vnode; 
	vnode -> next = vnode; 
	vnode -> ph_list = NULL;
	return vnode;
}

int add_vertex(struct graph* g, int v) {

	struct vnode* vnode = v_search_node(g -> pv_list, v);
	
	if(vnode != NULL)
		return G_VEXISTS;

	int status = v_insert_end(g -> pv_list, v);
	assert(status == SUCCESS);
	g -> nr_vertices += 1;
	return SUCCESS;
}

struct vnode* v_search_node(struct vnode* pv_list, int vertex) {

	struct vnode* pv_run = pv_list -> next;
	while(pv_run != pv_list) {

		if(pv_run -> v == vertex)
			return pv_run;

		pv_run = pv_run -> next;
	}

	return NULL;
}

struct vnode* v_get_node(int vertex) {

	struct vnode* vnode = (struct vnode*)xcalloc(1, sizeof(struct vnode));
	vnode -> previous = NULL;
	vnode -> next = NULL;
	vnode -> v = vertex;
	vnode -> ph_list = h_create_list();
	
	return vnode;
}

int v_insert_end(struct vnode* pv_list, int vertex) {

	v_generic_insert(pv_list -> previous, v_get_node(vertex), pv_list);
	return SUCCESS;
}

void v_generic_insert(struct vnode* beg, struct vnode* mid, struct vnode* end) {

	beg -> next = mid;
	mid -> previous = beg;
	mid -> next = end;
	end -> previous = mid;
}

struct hnode* h_create_list() {

	struct hnode* ph_list = h_get_node(-1);
	ph_list -> previous = ph_list; 
	ph_list -> next = ph_list; 
	return ph_list;
}

struct hnode* h_get_node(int vertex) {

	struct hnode* ph_node = (struct hnode*)xcalloc(1, sizeof(struct hnode));
	ph_node -> v = vertex;
	ph_node -> previous = NULL; 
	ph_node -> next = NULL;

	return ph_node;
}

int add_edge(struct graph* g, int v_start, int v_end) {

	int status;

	struct vnode* pv_start = v_search_node(g -> pv_list, v_start);
	if(pv_start == NULL)
		return G_VINVALID;

	struct vnode* pv_end = v_search_node(g -> pv_list, v_end);
	if(pv_end == NULL)
		return G_VINVALID;

	struct hnode* end_in_start = h_search_node(pv_start -> ph_list, v_end);
	struct hnode* start_in_end = h_search_node(pv_end -> ph_list, v_start);

	if(end_in_start && start_in_end)
		return G_EEXISTS;

	if(end_in_start != NULL ^ start_in_end != NULL)
		return G_CORRUPTED;

	status = h_insert_end(pv_start -> ph_list, v_end);
	assert(status == SUCCESS);

	status = h_insert_end(pv_end -> ph_list, v_start);
	assert(status == SUCCESS);

	g -> nr_edges += 1;
	return SUCCESS;
}

struct hnode* h_search_node(struct hnode* ph_list, int vertex) {

	for(struct hnode* ph_run = ph_list -> next; ph_run != ph_list; ph_run = ph_run -> next) {
		if(ph_run -> v == vertex)
			return ph_run;
	}
	return NULL;
}

int h_insert_end(struct hnode* ph_list, int vertex) {

	h_generic_insert(ph_list -> previous, h_get_node(vertex), ph_list);
	return SUCCESS;
}

void h_generic_insert(struct hnode* beg, struct hnode* mid, struct hnode* end) {

	beg -> next = mid;
	mid -> previous = beg;
	mid -> next = end;
	end -> previous = mid;
}

void print_graph(struct graph* g, char* message) {
	if(message)
		puts(message);

	printf("nr_vertices = %llu\n", g -> nr_vertices);
	printf("nr_edges = %llu\n", g -> nr_edges);

	for(struct vnode* pv_run = g -> pv_list -> next; pv_run != g -> pv_list; pv_run = pv_run -> next) {
		printf("%d -> ", pv_run -> v);
		for(struct hnode* ph_run = pv_run -> ph_list -> next; ph_run != pv_run -> ph_list; ph_run = ph_run -> next)
			printf("%d ", ph_run -> v);
		printf("\n");
	}
}

int remove_vertex(struct graph* g, int vertex) {

	struct hnode* ph_run_next;

	struct vnode* pv_delete_node = v_search_node(g -> pv_list, vertex);
	if(pv_delete_node == NULL)
		return G_VINVALID;

	for(struct hnode* ph_run = pv_delete_node -> ph_list -> next; ph_run != pv_delete_node -> ph_list; ph_run = ph_run_next) {
		ph_run_next = ph_run -> next;

		struct vnode* pv_adj_vertex = v_search_node(g -> pv_list, ph_run -> v);
		if(pv_adj_vertex == NULL)
			return G_CORRUPTED;

		struct hnode* ph_adj_vertex = h_search_node(pv_adj_vertex -> ph_list, vertex);
		if(ph_adj_vertex == NULL)
			return G_CORRUPTED;

		h_generic_delete(ph_adj_vertex);
		h_generic_delete(ph_run);
		g -> nr_edges -= 1;
	}
	free(pv_delete_node -> ph_list);
	v_generic_delete(pv_delete_node);
	g -> nr_vertices -= 1;
	return SUCCESS;
}

void v_generic_delete(struct vnode* v_delete_node) {
	
	v_delete_node -> previous -> next = v_delete_node -> next;
	v_delete_node -> next -> previous = v_delete_node -> previous;
	free(v_delete_node);	
}

void h_generic_delete(struct hnode* h_delete_node) {

	h_delete_node -> previous -> next = h_delete_node -> next;
	h_delete_node -> next -> previous = h_delete_node -> previous;
	free(h_delete_node);
}

int remove_edge(struct graph* g, int v_start, int v_end) {

	struct vnode* pv_start = v_search_node(g -> pv_list, v_start);
	struct vnode* pv_end = v_search_node(g -> pv_list, v_end);

	if(pv_start == NULL || pv_end == NULL)
		return G_VINVALID;

	struct hnode* end_in_start = h_search_node(pv_start -> ph_list, v_end);
	struct hnode* start_in_end = h_search_node(pv_end -> ph_list, v_start);

	if(end_in_start == NULL && start_in_end == NULL)
		return G_EINVALID;

	if(end_in_start == NULL ^ start_in_end == NULL)
		return G_CORRUPTED;

	h_generic_delete(end_in_start);
	h_generic_delete(start_in_end);

	g -> nr_edges -= 1;
	return SUCCESS;
}

int destroy_graph(struct graph** pptr) {

	struct graph* g = *pptr;

	struct vnode* pv_run = NULL;
	struct vnode* pv_run_next = NULL;

	struct hnode* ph_run = NULL;
	struct hnode* ph_run_next = NULL;

	for(pv_run = g -> pv_list -> next; pv_run != g -> pv_list; pv_run = pv_run_next) {

		pv_run_next = pv_run -> next;
		
		for(ph_run = pv_run -> ph_list -> next; ph_run != pv_run -> ph_list; ph_run = ph_run_next) {

			ph_run_next = ph_run -> next; 
			h_generic_delete(ph_run);
		}
		free(ph_run);
		v_generic_delete(pv_run);
	}
	free(pv_run);

	free(*pptr);
	*pptr = NULL;
	return SUCCESS;
}