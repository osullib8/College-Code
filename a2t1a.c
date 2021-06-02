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

//selection sort function, sorts array
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
void quick_sort(int arr[], int start, int end){

    int i, j, pivot;

   
   if(start<end){ //checks if start is less than the end
        pivot=start;
        i=start;
        j=end;

        while(i<j){ 
           while(arr[i]<=arr[pivot]&&i<end) i++; //increases i until it finds a number less than the pivot
           while(arr[j]>arr[pivot]) j--; //decreases j until it finds a number more than the pivot
            if(i<j) {
                swap(&arr[i],&arr[j]);
               
            }
      } // loops until i becomes greater than j
        
        if(j!=pivot) {
            swap(&arr[pivot],&arr[j]);
           
        }
 
        quick_sort(arr,start,j-1); //repeats from start - one less than j
        quick_sort(arr,j+1,end); //repeats from end - one more than j

   }

}

int main (void) { 

    
    int data[ARRAY_SIZE]={4,3,5,1,0,1,3,2,9,6};
    print_array(data);
    
    quick_sort(data,0,ARRAY_SIZE-1);
    print_array(data);



    return 0;
} 
