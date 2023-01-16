#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct graph_adt
{
unsigned int n_vertex;
unsigned int n_edge;
int** adj_matrix;
};

unsigned int get_number_of_vertices(char* fname)
{
char data_read[250];
unsigned int v = 0;
FILE* fptr;
fptr = fopen(fname, "r");

fgets(data_read, 50, fptr);

fclose(fptr);

char s[50];
unsigned int count = 0;

for (unsigned int i = 0; i < strlen(data_read); i++)
{
if ((data_read[i] == ' ') || (data_read[i] == '\0'))
{
v++;
}
}
//printf("\n %d \n", v+1);
return v + 1;
}


struct graph_adt* create_graph(int v)
{
struct graph_adt* graph;
graph = (struct graph_adt*) malloc(sizeof(struct graph_adt));
graph->n_vertex = v;

//CREATING 2D MATRIC OF SIZE (V+1) X (V+1)
graph->adj_matrix = (int**)malloc((graph->n_vertex + 1) * sizeof(int*));
for (unsigned int i = 0; i <= graph->n_vertex; i++)
graph->adj_matrix[i] = (int*)malloc((graph->n_vertex + 1) * sizeof(int));

unsigned int r, c;
for (r = 0; r <= v; r++)
{
for (c = 0; c <= v; c++)
{
if (r == c)
graph->adj_matrix[r][c] = 0;
else
graph->adj_matrix[r][c] = -1;
}
}

return graph;
}

struct graph_adt* add_edge(struct graph_adt* g, unsigned int vertex_1, unsigned int vertex_2, int w)
{
g->adj_matrix[vertex_1][vertex_2] = w;
//g->adj_matrix[vertex_2][vertex_1] = w;
return g;
}

void print_graph(struct graph_adt* g)
{
int m, n;
printf("number of vertices = %d\n", g->n_vertex);
printf("number of edges    = %d\n", g->n_edge);
for (m = 1; m <= g->n_vertex; m++)
{
for (n = 1; n <= g->n_vertex; n++)
{
printf("%d ", g->adj_matrix[m][n]);
}
printf("\n");
}
}

struct graph_adt* load_graph(char* fname)
{
char data_read[250];
char* number;
int n_vertices, n_edges = 0, r = 1, c = 1;
n_vertices = get_number_of_vertices(fname);
FILE* fptr;
int temp, count, v_count = 1;

fptr = fopen(fname, "r");

struct graph_adt* graph;
graph = create_graph(n_vertices);
for (r = 1; r <= graph->n_vertex; r++)
{
for (c = 1; c <= graph->n_vertex; c++)
{
fscanf(fptr, "%d", &temp);
graph = add_edge(graph, r, c, temp);
if (temp > 0)
n_edges++;
}
}
graph->n_edge = n_edges / 2;
fclose(fptr);



return graph;
}

int get_weight_from_graph(struct graph_adt* g, unsigned int vertex_1, unsigned int vertex_2)
{
return g->adj_matrix[vertex_1][vertex_2];
}

//#include "graphs_utilities.c"


struct pq_element
{
int weight;
int u, v;   // edge from u ---> v
};
typedef struct pq_element pq_element;

struct pq_adt
{
int size;
pq_element* pq;
};
typedef struct pq_adt pq_adt;

pq_adt* create_queue(int e)
{
printf("\nCREATING NEW QUEUE");
pq_adt* H;
H = malloc(sizeof(pq_adt));
H->size = 0;
H->pq = (pq_element*)malloc(5 * e * sizeof(pq_element));
return H;
}

void enqueue(pq_adt* H, struct pq_element value)
{
printf("\nENQUEUE");
H->pq[H->size] = value;

int i = H->size;
struct pq_element temp;

while (i >= 1) {
if (H->pq[i / 2].weight > H->pq[i].weight)
{
temp = H->pq[i / 2];
H->pq[i / 2] = H->pq[i];
H->pq[i] = temp;

i = i / 2;
}
else
{
break;
}
}
}



void Heapify(pq_adt* H, int index)
{
printf("\nHEAPIFY");
int i = index;
struct pq_element temp;

while ((2 * i) < H->size) {
if ((2 * i) + 1 >= H->size)
{
if (H->pq[i].weight > H->pq[2 * i].weight) {
temp = H->pq[i];
H->pq[i] = H->pq[2 * i];
H->pq[2 * i] = temp;

break;
}
}

if (H->pq[i].weight > H->pq[2 * i].weight || H->pq[i].weight > H->pq[2 * i + 1].weight) {
if (H->pq[2 * i].weight <= H->pq[(2 * i) + 1].weight) {
temp = H->pq[2 * i];
H->pq[2 * i] = H->pq[i];
H->pq[i] = temp;

i = 2 * i;
}
else if (H->pq[2 * i].weight > H->pq[(2 * i) + 1].weight) {
temp = H->pq[(2 * i) + 1];
H->pq[(2 * i) + 1] = H->pq[i];
H->pq[i] = temp;

i = (2 * i) + 1;
}
}
else {
break;
}
}
}

void deleteNode(pq_adt* H, int index)
{
printf("\nDELETE NODE");
struct pq_element temp = H->pq[index];

H->pq[index] = H->pq[H->size - 1];
H->pq[H->size - 1] = temp;

int i = index;
--(H->size);

Heapify(H, i);
}

pq_element extractMin(pq_adt* H)
{
printf("\nEXTRACT MIN");
pq_element min = H->pq[0];

deleteNode(H, 0);
return min;
}

void print_priority_queue(pq_adt* x)
{
printf("\nThe size of PQ: %d\n", x->size);
    for (int i = 0; i < x->size; i++)
    {
        printf("\nweight: %d, v1:%d, v2:%d", x->pq[i]->weight, x->pq[i]->u, x->pq[i]->v);
    }
}

struct graph_adt* prim(struct graph_adt* g, int startVertex)
{
printf("\nPRIM'S ALGO");
int current = startVertex, newVertex, vertices = g->n_vertex, edges = g->n_edge;
struct graph_adt* MST;
MST = create_graph(g->n_vertex);
int visited[vertices + 1];
struct node* temp;
pq_element var;
pq_adt* priorityQueue;

printf("\nCREATING NEW QUEUE CALL......................");
priorityQueue = create_queue(g->n_edge);

int i, j;

for (i = 0; i <= vertices; ++i)
{        // Initializing
visited[i] = 0;
}

i = 0;

while (i < vertices)
{
if (visited[current] == 0)
{
printf("\nNOT VISITED......................");
// If current node is not visited
visited[current] = 1;        // Mark it visited
//temp = g.adj_matrix[current];

for (j = 1; j <= g->n_vertex; j++)
{
if (g->adj_matrix[current][j] > 0)
{
var.u = current;
var.v = j;
var.weight = g->adj_matrix[current][j];
if (!visited[var.v])
{
// If the edge leads to an un-visited
// vertex only then queueSize it
printf("\nENQUEUE CALL......................");
enqueue(priorityQueue, var);
}
}
}

// while (temp != NULL)
// {
//     var.u = current;
//     var.v = temp->val;
//     var.weight = temp->weight;

//     if (!visited[var.v])
//     {
//         // If the edge leads to an un-visited
//         // vertex only then queueSize it
//         enqueue(priorityQueue, var);
//         ++queueSize;
//     }

//     temp = temp->next;
// }
printf("\nextract MIN CALL......................");
var = extractMin(priorityQueue);     // The greedy choice

newVertex = var.v;
current = var.u;

if (visited[newVertex] == 0)
{
// If it leads to an un-visited vertex, add it to MST
MST = add_edge(MST, current, newVertex, var.weight);
MST = add_edge(MST, newVertex, current, var.weight);

// MST[current] = addEdge(MST[current], newVertex, var.weight);
// MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
current = newVertex;
++i;
}
}
else
{
printf("\nALREADY VISITED PART......................");
printf("\nextract MIN CALL......................");
var = extractMin(priorityQueue);

newVertex = var.v;
current = var.u;

if (visited[newVertex] == 0)
{
// If it leads to an un-visited vertex, add it to MST
MST = add_edge(MST, current, newVertex, var.weight);
MST = add_edge(MST, newVertex, current, var.weight);

// MST[current] = addEdge(MST[current], newVertex, var.weight);
// MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
}

current = newVertex;

}
}
printf("\nCOMPLETED PRIM......................");
return MST;
}

int main()
{
char file_name[] = "sample_graph.txt";
//printf("Enter the file name containing the graph: ");
//scanf("%s",&file_name);

// struct graph_adt* g = load_graph(file_name);
// printf("\n%d\n", g->adj_matrix[6][3]);
// struct graph_adt* MST;
// print_graph(g);
// MST = prim(g, 1);
// printf("\nRECIEVED MST");
// print_graph(MST);

pq_adt* PQ;
PQ = create_queue(10);
pq_element val;
val.u = 10;
val.v = 10;
val.weight = 2;
enqueue(PQ, val);
print_priority_queue(PQ);
}
