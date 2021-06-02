#include<stdio.h> 
#include<string.h> 

#define ARRAY_SIZE 10

void swap(int* a, int* b){
    int temp =*a;
    *a=*b;
    *b=temp;
}

void print_array(int arr[]){
    for(int i=0; i<ARRAY_SIZE;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void selection_sort(int arr[]){
 
    int min_i;
    for(int i=0; i<ARRAY_SIZE-1; i++){

        min_i=i;
        for(int j = i+1;j<ARRAY_SIZE; j++){
            if(arr[j]<arr[min_i]) min_i=j;
        } // finds the minimum value
        swap(&arr[min_i], &arr[i]); // swaps it to the start, moves to next number and repeats
    } 

}


//quicksort function, sorts array
void quick_sort(int arr[], int start, int end, int* swaps, int* comps){

    int i, j, pivot;

   *comps=*comps+1;
   if(start<end){ //checks if start is less than the end
       
        pivot=start;
        i=start;
        j=end;

        *comps=*comps+1;
        while(i<j){
            *comps=*comps+1;

            *comps=*comps+1;
           while(arr[i]<=arr[pivot]&&i<end){ //increases i until it finds a number less than the pivot
                i++;
                *comps=*comps+1;
           } 

           *comps=*comps+1;
           while(arr[j]>arr[pivot]){ //decreases j until it finds a number more than the pivot
            if(i<j) {
                j--;
                *comps=*comps+1;

           } 
            *comps=*comps+1;
            if(i<j) { 
                swap(&arr[i],&arr[j]);
                *swaps=*swaps+1;
            }
        }// loops until i becomes greater than j

        *comps=*comps+1;
        if(j!=pivot) {
            swap(&arr[pivot],&arr[j]);
            *swaps=*swaps+1;
        }

        quick_sort(arr,start,j-1, swaps, comps);
        quick_sort(arr,j+1,end, swaps, comps);

   }

}

int main (void) { 

    int swap_count=0,comp_count=0;
    int data[ARRAY_SIZE]={4,3,5,1,0,1,3,2,9,6};
    print_array(data);
    
    quick_sort(data,0,ARRAY_SIZE-1, &swap_count, &comp_count);
    print_array(data);
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comp_count);

    return 0;
} 
