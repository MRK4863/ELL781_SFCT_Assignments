#include <stdio.h>
#include <stdlib.h>
#define MAX 20
void min_heapify(int *, int, int);
void buil_dminheap(int *, int);
int* extract_min (int *a, int);

struct pq_element
{
    int weight;
    int priority;
};

struct priority_queue_adt
{
    struct pq_element *pq_array;
    int n;
    int used;
};




void main()
{
    int i, t, n;
	int *a = (int*)malloc(MAX*sizeof(int));
    int *m = (int*)malloc(MAX*sizeof(int));
    printf("Enter no of elements in the array\n");
    scanf("%d", &n);
    printf("Enter the array\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    build_minheap(a, n);
    printf("The heap is\n");
    for (t = 0; t < n; t++) 
    {
        printf("%d\n", a[t]);
    }

    m = extract_min(a, n);

    printf("The new heap is\n");
    for (t = 0; t < n-1; t++) 
    {
        printf("%d\n", m[t]);
    }
}

void build_minheap(int *a, int n)
{
    int heapsize = n;
    int k;
    for (k = heapsize/2; k >= 0; k--) 
    {   //printf("value of k is %d", k);
        min_heapify(a, k, heapsize);
    }
}

void min_heapify(int *a, int i, int heapsize)
{
    int l, r, temp, largest;
    l = (2*i+1);
    r = ((2*i)+2);
    if (l >= heapsize)
        return;
    else {
        if (a[l] < a[i]) 
            largest = l;
        else
            largest = i;
        if (a[r] < a[largest])  
            largest = r;
        if (largest != i) 
        {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            min_heapify(a, largest, heapsize);
        }
    }
}

int* extract_min(int *a, int n)
{
    int newheapsize, min, i;
    newheapsize = n-1; 
    min = a[0];
    int *b = (int*)malloc((n-1)*sizeof(int));
    b[0] = a[n-1];
    for (i=1; i<n-1; i++)
    b[i] = a[i];
    min_heapify(b, 0, newheapsize);
    printf("The extracted min value is %d\n", min);

    return b;
}