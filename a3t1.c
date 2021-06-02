#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//node struct
struct tree_item{
  char letter;
  struct tree_item * right, * left; 
};
typedef struct tree_item tree_node;

//insert function
void tree_insert(tree_node ** root, char data){
    tree_node *temp = NULL;


    if(!(*root)) { //checks if node is present
      temp = (tree_node *)malloc(sizeof(tree_node));//creates memory
      temp->left = temp->right = NULL; //sets child nodes to NULL
      temp->letter = data; //assigns data
      *root = temp;
      //printf("%c\n",data);
      
      return;
     }

    
    if(data < (*root)->letter){//if data is less, goes to the left node
        tree_insert(&(*root)->left, data);
        //printf("%c left\n",data);
    } 
    else if(data >= (*root)->letter){//if data is less, goes to the right node
        tree_insert(&(*root)->right, data);
        //printf("%c right\n",data);
        
    }

}

//search function
int tree_search(tree_node ** root, char data){

    if(!(*root)) { //checks if there is a node present
        return 0;
    }

    if(data < (*root)->letter) {
        tree_search(&((*root)->left), data); //if data is less, goes to node on the left
    }
    else if(data > (*root)->letter) {
        tree_search(&((*root)->right), data);//if data is less, goes to node on the right
    }
    else if(data == (*root)->letter) { //returns true if found
        return 1;
    }

}


//prints tree
void tree_print_sorted (tree_node* root ){

     if (root)
    {
        tree_print_sorted(root->left);//prints left node 
        printf("%c",root->letter);//prints parent node 
        tree_print_sorted(root->right);//prints right node
    }
}

void tree_delete (tree_node* root ){
    if (root) //if a node is present it gets deleted
    {
        tree_delete(root->left);
        tree_delete(root->right);
        free(root);
    }
}



int main(void) {
    srand(time(NULL)); //seeds random numbers

    tree_node *root;
   
    root=NULL;

    char input[]="FLOCCINAUCINIHILIPILIFICATTION";
   
    for(int i=0;i<sizeof(input)-1;i++){
        tree_insert(&root, input[i]); //inserts each charachter
    }

    
    //printf("\n");
    tree_print_sorted(root);
    printf("\n");

    char randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand () % 26];
    if(tree_search(&root, randomletter) == 1){
        printf("%c in tree\n", randomletter);
    }
    else{
        printf("%c not in tree\n",randomletter);
    }

    randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand () % 26];
    if(tree_search(&root, randomletter) == 1){
        printf("%c in tree\n", randomletter);
    }
    else{
        printf("%c not in tree\n",randomletter);
    }

    tree_delete(root);
    
    return 0;
}