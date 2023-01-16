/* needs heap_utils.c */

typedef struct
	{
	int vertices;
	int **adj_matrix;
	} GRAPH;

GRAPH * read_graph_from_file(char *filename);
void print_graph(GRAPH *graph);
GRAPH * free_graph(GRAPH *graph);

GRAPH * read_graph_from_file(char *filename)
{
GRAPH * graph;
FILE *fp;
int i,j;

fp = fopen(filename,"rb");
if(fp == NULL) {printf("error reading %s\n",filename); return (GRAPH *) NULL;}

graph = (GRAPH *) malloc(sizeof(GRAPH));
fscanf(fp,"%d",&graph->vertices);

graph->adj_matrix = (int **) malloc(graph->vertices * sizeof(int *));
for(i = 0; i < graph->vertices; i++)
	graph->adj_matrix[i] = (int *) malloc(graph->vertices * sizeof(int));

for(i = 0; i < graph->vertices; i++)
for(j = 0; j < graph->vertices; j++)
fscanf(fp,"%d",&graph->adj_matrix[i][j]);

return graph;
}

void print_graph(GRAPH *graph)
{
int i,j;

printf("adjacency matrix for graph with %d vertices:\n",graph->vertices);
for(i = 0; i < graph->vertices; i++)
{
for(j = 0; j < graph->vertices - 1; j++)
printf("%d ",graph->adj_matrix[i][j]);
/* the last column */
printf("%d\n",graph->adj_matrix[i][j]);
}

return;
}

GRAPH * free_graph(GRAPH *graph)
{
int i;
for(i = 0; i < graph->vertices; i++)
free(graph->adj_matrix[i]);
free(graph->adj_matrix);

free(graph);
return (GRAPH *) NULL;
}
