/* basic recursive quicksort algorithm*/

#include <stdio.h>

void swap(int[], int, int);
void qsort(int[], int, int);
int partition(int v[], int low, int high);
void print(int[], int);

int main(){
    int arr[] = {5,2,7,1,3,6};
    int length = (sizeof(arr) / sizeof(arr[0])-1);

    printf("Before sort -> \n");
    print(arr,length);
    qsort(arr,0,length);
    printf("After sort -> \n"); 
    print(arr,length);
}

void print(int v[], int length){
    for (int i = 0; i < length; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void qsort(int v[], int low, int high){
    if(low < high){
        int pivot = partition(v, low, high);
        qsort(v,low, pivot -1);
        qsort(v, pivot+1, high);
    }
}

void swap(int v[], int left, int right){
    int temp;
    temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

int partition(int v[], int low, int high){
    /* use last element as pivot*/
    int pivot = v[high];
    int i = low -1;
    int j = low;
    /* if the value at j is less than the pivot, increment i and swap (i and j)*/
    for(; j < high; j++){  
        if( v[j] < pivot){
            swap(v,++i, j);
        }
    }
    /* once we reach the pivot*/
    swap(v,++i, j);
    return i;
}
