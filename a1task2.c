#include <stdio.h>
#include <string.h>

const int ARRAY_SIZE=59;
#define MAX_STRING_SIZE 25
#define R 31


int hash(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s) % ARRAY_SIZE; 
        s++;   
    } 
    return hash;
}; //hash function (given in assignment) 


int hash2(char* s){
    int hash = 0;
    while(*s){
        hash = (R*hash + *s) % ARRAY_SIZE; 
        s++;   
    } 
    return hash;
}; //2nd hash function for task2


void read_name(FILE*csv, char* buffer, int max_len){
    char c;
    int j=0;
    do{
        c=fgetc(csv);
        if(c != EOF && c!= '\n'){
            buffer[j]=c;
            j++;
        }

    }while(c != EOF && c != '\n');

    buffer[j]=0;
    return;
};//takes file and assigns a line to pointer "buffer"


struct word_freq {
    char word[MAX_STRING_SIZE];
    int freq;
};//struct contains a word (the name) and its frequency


void print_table(struct word_freq table[]){

    for(int i=0;i<ARRAY_SIZE;i++){
            printf("%d ", i);
            printf("%s ", table[i].word);
            if(table[i].freq != 0){
                printf("%d", table[i].freq);
                
            } 
            printf("\n");
    }
}


void insert_entry(struct word_freq table[], char key[], int *cols){

        int index=hash2(key);
        //printf("%d %s\n", index, key);
        

        if(table[index].word[0]==0){
            strcpy(table[index].word, key);
            table[index].freq=1;
        
        }
        else{
            int array_check;
            do{
                int i = 0;
                array_check = 1;
                do{
                        if(strcmp(table[index].word, key)!=0){
                            array_check = 0;
                            if(index==ARRAY_SIZE-1) index=0;
                            else index++;
                            *cols = *cols + 1;
                        }
                        i++;
                }while(i < MAX_STRING_SIZE && array_check == 1);
           
            }while(table[index].word[0]!=0 && array_check == 0);

            if(array_check==1){
                table[index].freq++;
            }
            else{
                strcpy(table[index].word, key);
                table[index].freq=1;
            }
        }

}//takes in a name and inserts it into the correct position in the hash table
 //if name is already in hash table it will increase the freq by 1
 //counts the number of collisions that occur


int num_terms(struct word_freq table[]){
    int counter=0;
    for(int i=0;i<ARRAY_SIZE;i++){
        if(table[i].freq != 0) counter++;
    }
    return counter;
}//returns the number of names in the hash table


int key_found(struct word_freq table[], char key[], int *index){

    int found=0;

        if(strcmp(key,table[*index].word)==0) found=1;

        while(found==0){
            if(*index==ARRAY_SIZE-1) *index=0;
            else *index=*index+1;
            if(table[*index].word[0]==0) found=2;
            else if(strcmp(key,table[*index].word)==0) found=1;
            
        }

    return found;
}//takes in a key and its associated index
 //returns 1 if it is in the hash table
 //returns 2 if its not in hash table


int main(void){

    struct word_freq hash_table[ARRAY_SIZE];
    int collisions=0;

    for(int i=0;i<ARRAY_SIZE;i++){
        memset(hash_table[i].word,0,MAX_STRING_SIZE);
        hash_table[i].freq=0;
    }//initilizes hash table i.e. fills up with zeroes

    char surname[MAX_STRING_SIZE];
    char *ptr;
    ptr=surname;
    
    FILE *names = fopen("names.csv", "r");

    while(!feof(names)){

        read_name(names,ptr,MAX_STRING_SIZE); //sets "surname" to name from names.csv
        insert_entry(hash_table, surname, &collisions); //inserts surname into hash table using hash function

    }//loops until the end of the file

    //printf("\n\n");
    //print_table(hash_table);
    printf("\nCapacity\t: %d\nNum terms\t: %d\nCollisions\t: %d\nLoad\t\t: %g%%\n\n", ARRAY_SIZE, num_terms(hash_table), collisions, (double) (100*num_terms(hash_table))/ARRAY_SIZE);
    
    char input[MAX_STRING_SIZE];
    int init_input_val, input_val;
    
    printf("Enter name: ");
    scanf("%[^\n]%*c", input);
    while(strcmp(input,"quit")!=0){

        init_input_val = hash2(input); //saves initial hash value, will be needed if hash table becomes full
        input_val = init_input_val;

            if(key_found(hash_table,input, &input_val) == 1){ 
                printf("%s %d\n\n", hash_table[input_val].word, hash_table[input_val].freq); //if key_found func is 1, print word and its frequency
            }

            if(key_found(hash_table,input, &input_val) == 2){ 
                printf("%s not in table\n\n", input); //if key_found func is 2, print not found
            }

        printf("Enter name: ");
        scanf("%[^\n]%*c", input);
    }

    printf("\n");
    fclose(names);
    return 0;
}