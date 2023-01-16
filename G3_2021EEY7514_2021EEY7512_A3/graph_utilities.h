#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct graph_adt
{
    unsigned int n_vertex;
    unsigned int n_edge;
    int **adj_matrix;
};

unsigned int get_number_of_vertices(char *fname)
{
    char data_read[250];
    unsigned int v=0;
    FILE *fptr;
    fptr = fopen(fname, "r");

    fgets(data_read, 50, fptr);

    fclose(fptr);

    char s[50];
    unsigned int count = 0;

    for(unsigned int i=0; i<strlen(data_read); i++)
    {
        if((data_read[i]==' ')||(data_read[i]=='\0'))
        {
            v++;
        }
    }
    //printf("\n %d \n", v+1);
    return v+1;    
}


struct graph_adt* create_graph(int v)
{
    struct graph_adt* graph;
    graph = (struct graph_adt*) malloc(sizeof(struct graph_adt));
    graph->n_vertex = v;

    //CREATING 2D MATRIC OF SIZE (V+1) X (V+1)
    graph->adj_matrix = (int **) malloc((graph->n_vertex +1) * sizeof(int *));
    for(unsigned int i = 0; i <= graph->n_vertex; i++)
	    graph->adj_matrix[i] = (int *) malloc((graph->n_vertex +1) * sizeof(int));

    unsigned int r, c;
    for(r=0;r<=v;r++)
    {
        for(c=0;c<=v;c++)
        {
            if(r==c)
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
    for(m=1;m<=g->n_vertex;m++)
    {
        for(n=1;n<=g->n_vertex;n++)
        {
            printf("%d ", g->adj_matrix[m][n]);
        }
        printf("\n");
    }
}

struct graph_adt* load_graph(char *fname)
{
    char data_read[250];
    char *number;
    int n_vertices, n_edges=0, r=1,c=1;
    n_vertices = get_number_of_vertices(fname);
    FILE *fptr;
    int temp, count, v_count=1;
    
    fptr = fopen(fname, "r");

    struct graph_adt* graph;
    graph = create_graph(n_vertices);
    for(r=1;r<=graph->n_vertex;r++)
    {
        for(c=1;c<=graph->n_vertex;c++)
        {
            fscanf(fptr, "%d", &temp);
            graph = add_edge(graph, r, c, temp);
            if(temp>0)
                n_edges++;
        }
    }
    graph->n_edge = n_edges/2;
    fclose(fptr);
    


    return graph;
}

int get_weight_from_graph(struct graph_adt* g, unsigned int vertex_1, unsigned int vertex_2)
{
    return g->adj_matrix[vertex_1][vertex_2];
}