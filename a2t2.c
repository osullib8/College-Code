#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<time.h> 

#define ARRAY_SIZE 10000

//fills array with -1
void clear_arr(int arr[]){
   for(int i=0;i<ARRAY_SIZE;i++){
        arr[i]=-1;
    }
}
//function to test if an array is sorted
char sorted_test(int arr[]){

    for(int i=0;i<ARRAY_SIZE-1;i++){
      if(arr[i]>arr[i+1]) return 'N';
    }
    return 'Y';
}

//fills with random numbers
void random_arr(int arr[]){
    for(int i=0;i<ARRAY_SIZE;i++){
        arr[i]=rand()%ARRAY_SIZE;
    }
}

//checks array for number
int check_arr(int arr[], int n) {
  for (int i = 0;i<ARRAY_SIZE;i++) {
    if(arr[i]==n) return 0;
  }
  return 1;
}

//fills with unique random numbers
void unique_random_arr(int arr[]) {
  int num;
  for (int i = 0;i<ARRAY_SIZE;i++) {
    do {
      num = rand() % ARRAY_SIZE;
    } while (check_arr(arr, num) == 0);
    
    arr[i] = num;
  }

}

//fills with ascending numbers
void ascending_arr(int arr[]){
    for(int i=0;i<ARRAY_SIZE;i++){
        arr[i]=i;
    }
}

//fills with descending numbers
void descending_arr(int arr[]) {
  int j = ARRAY_SIZE - 1;
  for (int i = 0;i<ARRAY_SIZE;i++) {
    arr[i] = j;
    j--;
  }
}

//fills with unifiorm numbers
void uniform_arr(int arr[]) {

  for (int i = 0;i<ARRAY_SIZE;i++) {
    arr[i] = 0;
  }
}

//swaps two elements
void swap(int* a, int* b){
    int temp =*a;
    *a=*b;
    *b=temp;
}

//prints array
void print_array(int arr[]){
    for(int i=0; i<ARRAY_SIZE;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

//selection sort function
void selection_sort(int arr[], int* swaps, int* comps){
 
    int min_i;
    for(int i=0; i<ARRAY_SIZE-1; i++){
        *comps=*comps+1;
        min_i=i;
        for(int j = i+1;j<ARRAY_SIZE; j++){
            *comps=*comps+1;
            if(arr[j]<arr[min_i]){
               min_i=j;
               *comps=*comps+1;
            }// finds the minimum value
        }
        if(arr[min_i] != arr[i]){
          swap(&arr[min_i], &arr[i]);// swaps it to the start, moves to next number and repeats
          *swaps=*swaps+1;
          *comps=*comps+1;
        }
    }

}

//quicksort function, sorts array
void quick_sort(int arr[], int start, int end, int* swaps, int* comps){

    int i, j, pivot;

   
   if(start<end){ //checks if start is less than the end
        *comps=*comps+1;
        
        pivot=start;
        i=start;
        j=end;

        
        while(i<j){
            *comps=*comps+1;

           while(arr[i]<=arr[pivot]&&i<end){
                i++;
                *comps=*comps+1;
           } //increases i until it finds a number less than the pivot
           
           while(arr[j]>arr[pivot]){
                j--;
                *comps=*comps+1;
           } // loops until i becomes greater than j
            
            if(i<j && arr[j] != arr[i]) {
                swap(&arr[i],&arr[j]);
                *swaps=*swaps+1;
                *comps=*comps+1;
            }
        }
       
        if(j != pivot && arr[j] != arr[pivot]) {
            swap(&arr[pivot],&arr[j]);
            *swaps=*swaps+1;
            *comps=*comps+1;
        }

    quick_sort(arr, start, j - 1, swaps, comps); //repeats from start - one less than j
    quick_sort(arr, j + 1, end, swaps, comps); //repeats from end - one more than j


   }

}


int main (void) { 

    int data[ARRAY_SIZE];
    srand(time(0));

    //print_array(data);
    unique_random_arr(data);
    //print_array(data);
    int swap_count = 0, comp_count = 0;
    
    quick_sort(data, 0, ARRAY_SIZE - 1, &swap_count, &comp_count);
    //print_array(data);
    printf("\n\nQUICK SORT:\n\n");
    printf("TEST\t: Unique Random Values\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    random_arr(data);
    //print_array(data);
    swap_count = 0;
    comp_count = 0;
    quick_sort(data,0,ARRAY_SIZE-1, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Random Values\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    ascending_arr(data);
    //print_array(data);
    swap_count=0;
    comp_count=0;
    quick_sort(data,0,ARRAY_SIZE-1, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Ascending sorted list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    descending_arr(data);    
    //print_array(d 
    swap_count = 0;     
    comp_count = 0;
    quick_sort(data, 0, ARRAY_SIZE - 1, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Descending sorted list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    uniform_arr(data);
    //print_array(data);
    swap_count = 0;
    comp_count = 0;
    quick_sort(data, 0, ARRAY_SIZE - 1, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Uniform list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);
    
    clear_arr(data);
    unique_random_arr(data);
   
    //print_array(data);
    swap_count = 0;
    comp_count = 0;
    selection_sort(data, &swap_count, &comp_count);
    //print_array(data);
    printf("\n\nSELECTION SORT:\n\n");
    printf("TEST\t: Unique Random Values\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    random_arr(data);
    //print_array(data);
    swap_count = 0;
    comp_count = 0;
    selection_sort(data, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Random Values\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    ascending_arr(data);
    //print_array(data);
    swap_count=0;
    comp_count=0;
    selection_sort(data, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Ascending sorted list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    descending_arr(data);    
    //print_array(d 
    swap_count = 0;     
    comp_count = 0;
    selection_sort(data, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Descending sorted list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    uniform_arr(data);
    //print_array(data);
    swap_count = 0;
    comp_count = 0;
    selection_sort(data, &swap_count, &comp_count);
    //print_array(data);
    printf("TEST\t: Uniform list\n");
    printf("SORTED\t: %c\n", sorted_test(data));
    printf("SWAPS\t: %d\n", swap_count);
    printf("COMPS\t: %d\n\n", comp_count);

    return 0;
}