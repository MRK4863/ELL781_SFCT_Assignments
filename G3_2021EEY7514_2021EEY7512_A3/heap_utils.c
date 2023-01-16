/* -------------------------------------------------------- */
/* --- routines for a min-heap, implemented as an array --- */
/* -------------------------------------------------------- */
#define INF 100000

typedef struct _DATA
	{
	int key;
	int extra;
	} DATA;

typedef struct _HEAP
	{
	int size;
	DATA *array;
	} HEAP;

void heapify(HEAP *heap, int i);
/* pointer to heap, the index at which to heapify */

void build_heap(HEAP *heap);
/* pointer to heap */

void heapsort(HEAP *heap);
/* pointer to heap */

void decrease_key(HEAP *heap, int i, DATA data);
/* pointer to heap index, new value */

DATA delete_min(HEAP *heap);

void insert(HEAP *heap, DATA data);

void heapify(HEAP *heap, int i)
{
int smallest, left, right, k; 
DATA temp;

/* print the array on which heapify is called */
printf("heapify at index %d(%d) in [",i,heap->array[i].key);
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]",heap->array[k].key); /* last one without a space */

smallest = i; /* initialisation */
left = 2*i+1; right=2*i+2;

if (left >= heap->size)
{ /* --- base case --- */
printf(" leaf node\n");
return;
} /* --- base case --- */
else
{ /* --- non-base case --- */
printf("\n"); /* newline, non-leaf node */

/* --- 1. find smallest out of numbers at i, left(i), right(i) --- */
if((left < heap->size) && (heap->array[left].key < heap->array[i].key))
smallest = left; else smallest = i;
if((right < heap->size) && (heap->array[right].key < heap->array[smallest].key))
smallest = right;

/*
printf("Of the numbers at indices %d(%d),%d(%d),%d(%d), smallest = %d(%d)\n",
	i,heap->array[i].key,left,heap->array[left].key,right,
	heap->array[right].key,smallest,heap->array[smallest].key);
*/

/* --- 2. interchange the numbers at indices i, smallest --- */
/* --- 3. recursively call heapify on the smallest index --- */
if (smallest != i)
{ 
temp.key = heap->array[smallest].key; 
temp.extra = heap->array[smallest].extra; 
heap->array[smallest].key = heap->array[i].key; 
heap->array[smallest].extra = heap->array[i].extra; 
heap->array[i].key = temp.key; 
heap->array[i].extra = temp.extra; 

heapify(heap, smallest);
}

} /* --- non-base case --- */

return;
}

void build_heap(HEAP *heap)
{
int i;

/* print the array on which build_heap is called */
printf("build_heap input [");
for(i=0; i <= heap->size-2; i++) printf("%d ",heap->array[i].key);
printf("%d]\n",heap->array[i].key); /* last one without a space */

for(i=heap->size/2-1; i >= 0; i--) 
	heapify(heap, i);

/* print the result of build_heap */
printf("build_heap ouput [");
for(i=0; i <= heap->size-2; i++) printf("%d ",heap->array[i].key);
printf("%d]\n",heap->array[i].key); /* last one without a space */

return;
}

void heapsort(HEAP *heap)
{
int i, original_heap_size = heap->size;
DATA temp;

/* print the array on which build_heap is called */
printf("heapsort input [");
for(i=0; i <= heap->size-2; i++) printf("%d ",heap->array[i].key);
printf("%d]\n",heap->array[i].key); /* last one without a space */

build_heap(heap);

for(i=heap->size-1; i >=1; i--)
	{
	/* --- 1. exchange [0] with [i] --- */
	temp.key = heap->array[0].key;
	temp.extra = heap->array[0].extra;
	heap->array[0].key = heap->array[i].key;
	heap->array[0].extra = heap->array[i].extra;
	heap->array[i].key = temp.key;
	heap->array[i].extra = temp.extra;

	/* --- 2. reduce the heap heap->size --- */
	heap->size--;

	/* --- 3. heapify on the reduced heap --- */
	heapify(heap, 0);
	}

/* print the array on which build_heap is called */
printf("heapsort output [");
for(i=0; i <= original_heap_size-2; i++) printf("%d ",heap->array[i].key);
printf("%d]\n",heap->array[i].key); /* last one without a space */

/* restore the size of the original heap */
heap->size = original_heap_size;

return;
}

void decrease_key(HEAP *heap, int i, DATA data)
{
int k;
DATA temp;

/* print the array on which decrease_key is called */
printf("decrease_key called for #%d (%d to %d) in [",
			i,heap->array[i].key,data.key);
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

/* --- update the heap with the new key in the desired position --- */
heap->array[i].key = data.key;
/* leave heap->array[i].extra unchanged! */

/* go up till needed */
while((i > 0) && 
	(heap->array[ (int) floor((i - 1)/2) ].key > heap->array[i].key))
{ /* go up */
/* 1. --- exchange A[i] and A[parent(i)] --- */
temp.key = heap->array[i].key;
temp.extra = heap->array[i].extra;
heap->array[i].key = heap->array[ (int) floor((i - 1)/2)].key;
heap->array[i].extra = heap->array[ (int) floor((i - 1)/2)].extra;
heap->array[(int) floor((i - 1)/2)].key = temp.key;
heap->array[(int) floor((i - 1)/2)].extra = temp.extra;

/* print the array after the swap */
printf("After the swap: [");
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

/* 2. --- i = parent(i) --- */
i = (int) floor((i - 1)/2);
} /* go up */

printf("decrease_key done\n");
return;
}

DATA delete_min(HEAP *heap)
{
int k;
DATA min;

/* print the array before delete_min() */
printf("Calling delete_min on [");
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

min.key = heap->array[0].key;
min.extra = heap->array[0].extra;

/* put the last element at the top of the heap */
heap->array[0].key = heap->array[heap->size - 1].key;
heap->array[0].extra = heap->array[heap->size - 1].extra;

/* decrement the heap size by 1 */
heap->size--;

/* call heapify() */
heapify(heap,0);

/* print the array after delete_min() */
printf("After delete_min: [");
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

return min;
}

void insert(HEAP *heap, DATA data)
{
int k;

/* print the array before insert() */
printf("Inserting %d in heap of size %d: [",data.key,heap->size);
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

/* increment heap size by 1 */
heap->size++;

heap->array[heap->size - 1].key = INF;

decrease_key(heap,heap->size - 1,data);

/* print the array after insert() */
printf("After insert: [");
for(k=0; k <= heap->size-2; k++) printf("%d ",heap->array[k].key);
printf("%d]\n",heap->array[k].key); /* last one without a space */

return;
}
