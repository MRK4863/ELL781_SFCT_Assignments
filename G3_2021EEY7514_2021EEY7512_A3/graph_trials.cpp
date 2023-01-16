#include<iostream.h>
#include<malloc.h>

class graph_adt
{
    private:
        int v;
        int **adj_matrix;

    public:

        int get_number_of_vertices(char *fname)
            {
                char data_read[250];
                int t=0;
                FILE *fptr;
                fptr = fopen(fname, "r");

                fgets(data_read, 50, fptr);

                fclose(fptr);

                char s[50];
                int count = 0;

                for(int i=0; i<strlen(data_read); i++)
                {
                    if((data_read[i]==' ')||(data_read[i]=='\0'))
                    {
                        t++;
                    }
                }
                //printf("\n %d \n", v+1);
                v = t+1;
            }

        void create_graph()
        {
            adj_matrix = (int **) malloc((v+1) * sizeof(int *));
            for(int i = 0; i <= v; i++)
	            adj_matrix[i] = (int *) malloc((v+1) * sizeof(int));   

        }

        void add_edge(int v1, int v2, int w)
        {
            adj_matrix[v1][v2] = w;
        }

        void print_graph(struct graph_adt* g)
        {
            int m, n;
            for(m=1;m<=v;m++)
            {
                for(n=1;n<=v;n++)
                {
                    printf("%d ", adj_matrix[m][n]);
                }
                printf("\n");
            }
        }

        struct graph_adt* load_graph(char *fname)
        {
            char data_read[250];
            char *number;
            int n_vertices, r=1,c=1;
            n_vertices = get_number_of_vertices(fname);
            FILE *fptr;
            int temp, count, v_count=1;
            
            fptr = fopen(fname, "r");

            struct graph_adt* graph;
            graph = create_graph(n_vertices);
            for(r=1;r<=graph->v;r++)
            {
                for(c=1;c<=graph->v;c++)
                {
                    fscanf(fptr, "%d", &temp);
                    graph = add_edge(graph, r, c, temp);
                }
            }
            fclose(fptr);

            return graph;
}




}




struct graph_adt* load_graph(char *fname)
{
    char data_read[250];
    char *number;
    int n_vertices, r=1,c=1;
    n_vertices = get_number_of_vertices(fname);
    FILE *fptr;
    int temp, count, v_count=1;
    
    fptr = fopen(fname, "r");

    struct graph_adt* graph;
    graph = create_graph(n_vertices);
    for(r=1;r<=graph->v;r++)
    {
        for(c=1;c<=graph->v;c++)
        {
            fscanf(fptr, "%d", &temp);
            graph = add_edge(graph, r, c, temp);
        }
    }
    fclose(fptr);

    return graph;
}