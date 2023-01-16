#include <iostream>
#include "5_Heap_utilities.cpp"

using namespace std;

int main()
{
        int arr[] = {15, 5, 20, 1, 17, 10, 30, 0};
        int i;
        //swap(arr, 0, 5);

        int l = 7;// sizeof(arr)/sizeof(int);

        Heapify(arr, l);
        std::cout<<"\nHeapify ";
        for( i=0;i<l;i++)
                std::cout<<arr[i]<<" ";

        /*

        delete_min(arr, l);
        std::cout<<"Deleting min element: ";
        for(i=0;i<(l-1);i++)
                std::cout<<arr[i]<<" ";
*/
        return 0;
}