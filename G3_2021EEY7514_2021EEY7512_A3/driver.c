// #pragma once
#include "graph_utilities.h"

//#include "graphs_utilities.c"


struct pq_element 
{
    int weight;
    int u, v;   // edge from u ---> v
};

typedef struct pq_element pq_element;
pq_element min;

struct pq_adt
{
    int size;
    pq_element* pq;
};
typedef struct pq_adt pq_adt;

pq_adt* create_p_queue(int e)
{
    printf("\nCREATING NEW QUEUE");
    pq_adt* H;
    H = malloc(sizeof(pq_adt));
    H->size = 0;
    H->pq = (pq_element*) malloc(5*e*sizeof(pq_element));
    printf("\nCREATING NEW QUEUE");
    return H;
}

pq_adt* insert_into_p_queue(pq_adt* H, pq_element val)
{
    printf("\nINSERTING");
    H->pq[H->size] = val;
    
    printf("\nINSERTING");
    int i = H->size;
    pq_element temp;
 
    while (i >= 1) 
    {
        if (H->pq[i / 2].weight > H->pq[i].weight) 
        {
            temp = H->pq[i/2];
            H->pq[i/2] = H->pq[i];
            H->pq[i] = temp;
 
            i = i / 2;
        } 
        else 
        {
            break;
        }
    }
    H->size++;
    return H;
}

pq_adt* decrease_key(pq_adt* H, int i, int new_val)
{
    H->pq[i].weight = new_val;
    pq_element temp;
    while (i >= 1) 
    {
        if (H->pq[i / 2].weight > H->pq[i].weight) 
        {
            temp = H->pq[i/2];
            H->pq[i/2] = H->pq[i];
            H->pq[i] = temp;
 
            i = i / 2;
        } 
        else 
        {
            break;
        }
    }
    return H;

}


pq_adt* Heapify(pq_adt* H, int index)
{
    printf("\nHEAPIFY");
    int i = index;
    struct pq_element temp;
    int p, l, r;

    if((H->size)==1)
    {
        return H;
    }
    else
    {
        p = i;
        l = 2*i+1;
        r = 2*i+2;
        if(l<H->size && H->pq[p].weight > H->pq[l].weight)
            p = l;
        if(r<H->size && H->pq[p].weight > H->pq[r].weight)
            p = r;
        if(p!=i)
        {
            temp = H->pq[p];
            H->pq[p] = H->pq[i];
            H->pq[i] = temp;
            H = Heapify( H, p);
        }
    }
    return H;
}

pq_adt* deleteNode(pq_adt* H, int index)
{
    printf("\nDELETE NODE");
    struct pq_element temp = H->pq[index];

    H->pq[index] = H->pq[H->size - 1];
    H->pq[H->size - 1] = temp;
 
    int i = index;
    (H->size)-=1;

    //print_priority_queue(H);
    H = Heapify(H, 0);
    //print_priority_queue(H);
    return H;
}

pq_adt* extractMin(pq_adt* H)
{
    printf("\nEXTRACT MIN");
    min = H->pq[0];

    H = deleteNode(H, 0);
    return H;
}


void print_priority_queue(pq_adt* H)
{
    int i;
    printf("\nsize = %d\n", H->size);
    for(i=0;i<H->size;i++)
    {
        printf("%d\t", H->pq[i].weight);
    }
}

// struct graph_adt* prim(struct graph_adt* g, int startVertex)
// {
//     printf("\nPRIM'S ALGO");
//     int current = startVertex, newVertex, vertices = g->n_vertex, edges = g->n_edge;
//     struct graph_adt* MST;
//     MST = create_graph(g->n_vertex);
//     int visited[vertices + 1];
//     struct node * temp;
//     pq_element var;
//     pq_adt* priorityQueue;

//     printf("\nCREATING NEW QUEUE CALL......................");
//     priorityQueue = create_p_queue(g->n_edge) ;
 
//     int i, j;
 
//     for (i = 0; i <= vertices; ++i) 
//     {        // Initializing
//         visited[i] = 0;
//     }
 
//     i = 0;
 
//     while (i < vertices) 
//     {
//         if (visited[current] == 0) 
//         {   
//             printf("\nNOT VISITED......................");         
//             // If current node is not visited
//             visited[current] = 1;        // Mark it visited
//             //temp = g.adj_matrix[current];
 
//             for(j=1;j<=g->n_vertex;j++)
//             {
//                 if(g->adj_matrix[current][j]>0)
//                 {
//                     var.u = current;
//                     var.v = j;
//                     var.weight = g->adj_matrix[current][j];
//                     if (!visited[var.v]) 
//                     {
//                         // If the edge leads to an un-visited
//                         // vertex only then queueSize it
//                         printf("\nENQUEUE CALL......................");
//                         priorityQueue = insert_into_p_queue(priorityQueue, var);
//                     }
//                 }
//             }

//             // while (temp != NULL) 
//             // {
//             //     var.u = current;
//             //     var.v = temp->val;
//             //     var.weight = temp->weight;
 
//             //     if (!visited[var.v]) 
//             //     {
//             //         // If the edge leads to an un-visited
//             //         // vertex only then queueSize it
//             //         enqueue(priorityQueue, var);
//             //         ++queueSize;
//             //     }
 
//             //     temp = temp->next;
//             // }
//             printf("\nextract MIN CALL......................");
//             priorityQueue = extractMin(priorityQueue);     // The greedy choice
//             var = min;

//             newVertex = var.v;
//             current = var.u;
 
//             if (visited[newVertex] == 0) 
//             {
//                 // If it leads to an un-visited vertex, add it to MST
//                 MST = add_edge(MST, current, newVertex, var.weight);
//                 MST = add_edge(MST, newVertex, current, var.weight);

//                 // MST[current] = addEdge(MST[current], newVertex, var.weight);
//                 // MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
//                 current = newVertex;
//                 ++i;
//                 print_graph(MST);
//             }
//         }
//         else 
//         {
//             printf("\nALREADY VISITED PART......................");
//             printf("\nextract MIN CALL......................");
//             priorityQueue = extractMin(priorityQueue);     // The greedy choice
//             var = min;

//             newVertex = var.v;
//             current = var.u;

//             if (visited[newVertex] == 0) 
//             {
//                 // If it leads to an un-visited vertex, add it to MST
//                 MST = add_edge(MST, current, newVertex, var.weight);
//                 MST = add_edge(MST, newVertex, current, var.weight);

//                 // MST[current] = addEdge(MST[current], newVertex, var.weight);
//                 // MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
//                 print_graph(MST);
//             }

//             current = newVertex;
            
//         }
//     }
//     printf("\nCOMPLETED PRIM......................");
//     return MST;
// }

int main()
{
    char file_name[] = "sample_graph.txt";
    //printf("Enter the file name containing the graph: ");
    //scanf("%s",&file_name);

    struct graph_adt* g = load_graph(file_name);
    printf("\n%d\n", g->adj_matrix[6][3]);
    print_graph(g);
    struct graph_adt* MST;
    print_graph(g);
    //MST = prim(g, 1);
    //printf("\nRECIEVED MST");
    //print_graph(MST);

    // pq_adt* PQ;
    // PQ = create_p_queue(10);
    // pq_element val;
    // val.u = 10;
    // val.v = 10;
    // val.weight = 3;
    // print_priority_queue(PQ);
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 2;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 5;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 1;
    // PQ = insert_into_p_queue(PQ, val);
    // print_priority_queue(PQ);

    // val.weight = 7;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 9;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 4;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 6;
    // PQ = insert_into_p_queue(PQ, val);

    // val.weight = 8;
    // PQ = insert_into_p_queue(PQ, val);

    // PQ = extractMin(PQ);
    // print_priority_queue(PQ);
    // printf("%d %d %d", min.u, min.v, min.weight);

    // PQ = decrease_key(PQ, 6, 1);
    // print_priority_queue(PQ);
    
    // PQ = extractMin(PQ);
    // print_priority_queue(PQ);
    // printf("%d %d %d", min.u, min.v, min.weight);

    // PQ = extractMin(PQ);
    // print_priority_queue(PQ);
    // printf("%d %d %d", min.u, min.v, min.weight);

    // printf("%d", get_weight_from_graph(g, 6, 4));
}





















// pq_adt Heapify(pq_adt H, int index)
// {
//     printf("\nHEAPIFY");
//     int i = index;
//     struct pq_element temp;
 
//     while ((2 * i) < H.size) {
//         if ((2 * i) + 1 >= H.size) 
//         {
//             if (H.pq[i].weight > H.pq[2 * i].weight) {
//                 temp = H.pq[i];
//                 H.pq[i] = H.pq[2 * i];
//                 H.pq[2 * i] = temp;
 
//                 break;
//             }
//         }
 
//         if (H.pq[i].weight > H.pq[2 * i].weight || H.pq[i].weight > H.pq[2 * i + 1].weight) 
//         {
//             if (H.pq[2 * i].weight <= H.pq[(2 * i) + 1].weight) {
//                 temp = H.pq[2 * i];
//                 H.pq[2 * i] = H.pq[i];
//                 H.pq[i] = temp;
 
//                 i = 2 * i;
//             } else if (H.pq[2 * i].weight > H.pq[(2 * i) + 1].weight) {
//                 temp = H.pq[(2 * i) + 1];
//                 H.pq[(2 * i) + 1] = H.pq[i];
//                 H.pq[i] = temp;
 
//                 i = (2 * i) + 1;
//             }
//         } else {
//             break;
//         }
//     }
//     return H;
// }

// pq_adt deleteNode(pq_adt H, int index)
// {
//     printf("\nDELETE NODE");
//     struct pq_element temp = H.pq[index];

//     H.pq[index] = H.pq[H.size - 1];
//     H.pq[H.size - 1] = temp;
 
//     int i = index;
//     --(H.size);
 
//     H = Heapify(H, i);
//     return H;
// }

// pq_adt extractMin(pq_adt H)
// {
//     printf("\nEXTRACT MIN");
//     min = H.pq[0];

//     H = deleteNode(H, 0);
//     return H;
// }

// // void print_priority_queue(pq_adt x)
// // {
// //     printf("The size of PQ: %d", x.size);
// //     for(int i=0;i<x.size;i++)
// //     {
// //         printf("\nweight: %d, v1:%d, v2:%d", x.pq[i]->weight, x.pq[i]->u, x.pq[i]->u);
// //     }
// // }

// struct graph_adt* prim(struct graph_adt* g, int startVertex)
// {
//     printf("\nPRIM'S ALGO");
//     int current = startVertex, newVertex, vertices = g->n_vertex, edges = g->n_edge;
//     struct graph_adt* MST;
//     MST = create_graph(g->n_vertex);
//     int visited[vertices + 1];
//     struct node * temp;
//     pq_element var;
//     pq_adt priorityQueue;

//     printf("\nCREATING NEW QUEUE CALL......................");
//     priorityQueue = create_queue(g->n_edge) ;
 
//     int i, j;
 
//     for (i = 0; i <= vertices; ++i) 
//     {        // Initializing
//         visited[i] = 0;
//     }
 
//     i = 0;
 
//     while (i < vertices) 
//     {
//         if (visited[current] == 0) 
//         {   
//             printf("\nNOT VISITED......................");         
//             // If current node is not visited
//             visited[current] = 1;        // Mark it visited
//             //temp = g.adj_matrix[current];
 
//             for(j=1;j<=g->n_vertex;j++)
//             {
//                 if(g->adj_matrix[current][j]>0)
//                 {
//                     var.u = current;
//                     var.v = j;
//                     var.weight = g->adj_matrix[current][j];
//                     if (!visited[var.v]) 
//                     {
//                         // If the edge leads to an un-visited
//                         // vertex only then queueSize it
//                         printf("\nENQUEUE CALL......................");
//                         priorityQueue = enqueue(priorityQueue, var);
//                     }
//                 }
//             }

//             // while (temp != NULL) 
//             // {
//             //     var.u = current;
//             //     var.v = temp->val;
//             //     var.weight = temp->weight;
 
//             //     if (!visited[var.v]) 
//             //     {
//             //         // If the edge leads to an un-visited
//             //         // vertex only then queueSize it
//             //         enqueue(priorityQueue, var);
//             //         ++queueSize;
//             //     }
 
//             //     temp = temp->next;
//             // }
//             printf("\nextract MIN CALL......................");
//             priorityQueue = extractMin(priorityQueue);     // The greedy choice
//             var = min;

//             newVertex = var.v;
//             current = var.u;
 
//             if (visited[newVertex] == 0) 
//             {
//                 // If it leads to an un-visited vertex, add it to MST
//                 MST = add_edge(MST, current, newVertex, var.weight);
//                 MST = add_edge(MST, newVertex, current, var.weight);

//                 // MST[current] = addEdge(MST[current], newVertex, var.weight);
//                 // MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
//                 current = newVertex;
//                 ++i;
//                 print_graph(MST);
//             }
//         }
//         else 
//         {
//             printf("\nALREADY VISITED PART......................");
//             printf("\nextract MIN CALL......................");
//             priorityQueue = extractMin(priorityQueue);     // The greedy choice
//             var = min;

//             newVertex = var.v;
//             current = var.u;

//             if (visited[newVertex] == 0) 
//             {
//                 // If it leads to an un-visited vertex, add it to MST
//                 MST = add_edge(MST, current, newVertex, var.weight);
//                 MST = add_edge(MST, newVertex, current, var.weight);

//                 // MST[current] = addEdge(MST[current], newVertex, var.weight);
//                 // MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
//                 print_graph(MST);
//             }

//             current = newVertex;
            
//         }
//     }
//     printf("\nCOMPLETED PRIM......................");
//     return MST;
// }

// int main()
// {
//     char file_name[] = "sample_graph.txt";
//     //printf("Enter the file name containing the graph: ");
//     //scanf("%s",&file_name);

//     struct graph_adt* g = load_graph(file_name);
//     printf("\n%d\n", g->adj_matrix[6][3]);
//     struct graph_adt* MST;
//     print_graph(g);
//     MST = prim(g, 1);
//     printf("\nRECIEVED MST");
//     print_graph(MST);

//     // pq_adt* PQ;
//     // PQ = create_queue(10);
//     // pq_element val;
//     // val.u = 10;
//     // val.v = 10;
//     // val.weight = 2;
//     // enqueue(PQ, val);
//     // print_priority_queue(PQ);

//     //printf("%d", get_weight_from_graph(g, 6, 4));
// }