#include<iostream>

using namespace std;

int left(int i)
{ 
        int left = 2*i+1;
        return left;
}

int right(int i)
{ 
        int right = 2*i+2;
        return right;
}
void swap(int A[], int i, int j)
{
        int temp;
        temp=A[i];
        A[i] = A[j];
        A[j] = temp;
}

void Heapify(int A[], int n)
{
        int largest, r, l;
        for(int i=(n/2)-1;i>=0;i--)
        {

                largest = i;
                r=2*i+2;
                l=2*i+1;
                if(A[largest]<A[l])
                        largest = l;
                if(A[largest]<A[r])
                        largest = r;
                if(largest!=i)
                        std::cout<<"\nSwapping"<<A[largest]<<" & "<<A[i];
                        swap(A, largest, i);
                        Heapify(A, largest);
                        
        }
}

void Heapsort(int A[])
{

}

void build_heap(int A[])
{

}

void delete_max(int A[], int n)
{
        //int n = sizeof(A)/sizeof(int);

        swap(A, 0, n-1);
        Heapify(A, n-1);
}
/*
void heapify(HEAP *heap, int i);

void build_heap(HEAP *heap);

void heapsort(HEAP *heap);

void decrease_key(HEAP *heap, int i, DATA data);

void delete_min(HEAP *heap);

void insert(HEAP *heap, DATA data);
*/
