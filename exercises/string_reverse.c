#include <stdio.h>

void reverse(char[], int, int);
void swap(char[], int, int);

int main(){
    char str[] = {"string"};
    int length = (sizeof(str) / sizeof(str[0])-1);

    printf("Initial -> %s\n", str);
    reverse(str,0, length-1);
    printf("Reversed -> %s\n", str);
}

void reverse(char str[], int low, int high){
    if(low < high){
        swap(str,low,high);
        reverse(str,++low,--high);
    }
}

void swap(char str[], int a, int b){
    int temp;
    temp = str[a];
    str[a] = str[b];
    str[b] = temp;
}