#include<stdio.h>
// enqueues an entry into the Priority Queue
void enqueue(struct edge heap[], int size, struct edge value)
{
    heap[size] = value;
 
    int i = size;
    struct edge temp;
 
    while (i >= 1) {
        if (heap[i / 2].weight > heap[i].weight) {
            temp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = temp;
 
            i = i / 2;
        } else {
            break;
        }
    }
}
 
void heapify(struct edge heap[], int size, int index)
{
    int i = index;
    struct edge temp;
 
    while ((2 * i) < size) {
        if ((2 * i) + 1 >= size) {
            if (heap[i].weight > heap[2 * i].weight) {
                temp = heap[i];
                heap[i] = heap[2 * i];
                heap[2 * i] = temp;
 
                break;
            }
        }
 
        if (heap[i].weight > heap[2 * i].weight || heap[i].weight > heap[2 * i + 1].weight) {
            if (heap[2 * i].weight <= heap[(2 * i) + 1].weight) {
                temp = heap[2 * i];
                heap[2 * i] = heap[i];
                heap[i] = temp;
 
                i = 2 * i;
            } else if (heap[2 * i].weight > heap[(2 * i) + 1].weight) {
                temp = heap[(2 * i) + 1];
                heap[(2 * i) + 1] = heap[i];
                heap[i] = temp;
 
                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}
 
// Deletes and entry in the Priority Queue
void deleteNode(struct edge heap[], int size, int index)
{
    struct edge temp = heap[index];
 
    heap[index] = heap[size - 1];
    heap[size - 1] = temp;
 
    int i = index;
    --size;
 
    heapify(heap, size, i);
}
 
// Returns the element with
// Minimum Priority and deletes it
struct edge extractMin(struct edge heap[], int size)
{
    struct edge min = heap[0];

    deleteNode(heap, size, 0);

    return min;
}

int main()
{
    char fname[] = "sample_graph.txt";
    int mat[5][5], m, n;
    FILE *fp;
    fp = fopen(fname, "r+");
    for(n=0;n<5;n++)
    {
        for(m=0;m<5;m++)
        {
            fscanf(fp, "%d", &mat[m][n]);
            printf("%d\t", mat[m][n]);
        }
        printf("%d\n");
    }
}