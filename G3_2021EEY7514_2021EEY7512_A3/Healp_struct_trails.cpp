#include<iostream>
using namespace std;

struct data
{
        int key;
};

struct heap
{
        int heap_size;
        data *array;
};

void print_heap(heap H1)
{
        int i;
        std:cout<<"\nHeap: ";
        for(int i=0;i<H1.heap_size;i++)
        {
                //std::cout<<"Index: "<<i;
                std::cout<<H1.array[i].key<<"\t";
        }
}

void heapify(heap H, int i)
{
        int _min, l, r;
        //Heapify at index i

        //left child
        l=2*i+1;

        //right child
        r=2*i+2;

        _min = i;
        
        if(l>=H.heap_size || r>=H.heap_size) 
        {
                return;
        }
        else
        {
                _min = i;
                if(H.array[l].key<H.array[_min].key)
                        _min = l;
                if(H.array[r].key<H.array[_min].key)
                        _min = r;

                if(_min!=i)
                {
                        int temp;
                        temp = H.array[i].key;
                        H.array[i].key = H.array[_min].key;
                        H.array[_min].key = temp;
                        heapify(H, _min);
                }
                print_heap(H);  
        }
        
}

heap build_heap(heap H)
{
        std::cout<<"\nBuilding heap ";
        int i;
        for(i=(H.heap_size-1);i>=0;i--)
                heapify(H, i);
        return H;
}

heap insert_key(heap H, int d)
{
        data temp;
        //int a[H.heap_size]
        H.heap_size++;
        H.array[H.heap_size-1].key = d;
        //heapify(H, H.heap_size/2-1);
        H = build_heap(H);
        print_heap(H);
        return H;
}
heap delete_min(heap H)
{
        int temp;
        std::cout<<"\ndeleting :"<<H.array[0].key;
        temp = H.array[0].key;
        H.array[0].key = H.array[H.heap_size-1].key;
        H.array[H.heap_size-1].key = temp;

        H.heap_size--;
        //std::cout<<"\nheapsize after deletion: "<<H.heap_size;
        heapify(H,0);
        //std::cout<<"\nheapsize after deletion: "<<H.heap_size;
        print_heap(H);
        //std::cout<<"\nheapsize after deletion: "<<H.heap_size;

        return H;
}

heap heap_sort(heap H)
{
        int size = H.heap_size;
        for(int i=0;i<size;i++)
        {
                H = delete_min(H);
        }
        H.heap_size = size;

        return H;
}

heap decrease_key(heap H, int k, int new_val)
{
        int i;
        for(i=0;i<H.heap_size;i++)
        {
                if(H.array[i].key == k)
                {
                        H.array[i].key = new_val;
                        break;
                }
        }
        build_heap(H);
        return H;
}

heap H;

int main()
{
        int a[] = {1,13,7,3,10,8,14,15,9,16};
        std::cout<<"successful"<<sizeof(a[0])<<endl;

        H.heap_size = sizeof(a)/sizeof(a[0]);
        std::cout<<"Heap size:"<<H.heap_size<<endl;

        H.array = new data[H.heap_size];
        std::cout<<"Heap memory used:"<<sizeof(H.array)<<endl;

        for(int i=0;i<H.heap_size;i++)
        {
                H.array[i].key = a[i];
        }

        print_heap(H);

        //heapify(H, 5);
        //
        H = build_heap(H);
        //H = delete_min(H);
        H = insert_key(H, 2);
        H = decrease_key(H, 15, 4);        //std::cout<<"\nheapsize after deletion: "<<H.heap_size;
        //H = heap_sort(H);
        print_heap(H);
}