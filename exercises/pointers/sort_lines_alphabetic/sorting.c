#include <string.h>
#include "sort_lines_alphabetic.h"

void swap(char *v[], int i, int j);
int partition(char *v[], int low, int high);

void qsort(char *v[], int low, int high){
    if(low < high){
        int pivot = partition(v, low, high);
        qsort(v,low, pivot -1);
        qsort(v, pivot+1, high);
    }
}

void swap(char *v[], int left, int right){
    char *temp;
    temp = v[left];
    v[left] = v[right];
    v[right] = temp;
}

int partition(char *v[], int low, int high){
    /* use last element as pivot*/
    char *pivot = v[high];
    int i = low -1;
    int j = low;
    /* if the value at j is less than the pivot, increment i and swap (i and j)*/
    for(; j < high; j++){  
        if (strcmp(v[j], pivot) < 0) {
            swap(v,++i, j);
        }
    }
    /* once we reach the pivot*/
    swap(v,++i, j);
    return i;
}