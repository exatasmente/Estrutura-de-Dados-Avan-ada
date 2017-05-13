#include <stdio.h>

typedef struct Node
{
  int value;
  struct node *left;
  struct node *right;

}Node;

Node *root = 0;


int search(Node ** tree, int val){
    if( ! ( *tree ) ){
        return 0;
    }
    if( val < ( *tree )-> value ){
        search( &( ( *tree )-> left ), val );
    }else if( val > ( *tree ) -> value){
        search( &( ( *tree ) -> right ), val );
    }else if( val == ( *tree )-> value ){
        return 1;
    }
}

insert(int key, Node **leaf)
{
    if( *leaf == 0 )
    {
        *leaf = (Node*) malloc( sizeof( Node ) );
        (*leaf)->value = key;
        (*leaf)->left = 0;    
        (*leaf)->right = 0;  
    }
    else if(key < (*leaf)->value)
    {
        insert( key, &(*leaf)->left );
    }
    else if(key > (*leaf)->value)
    {
        insert( key, &(*leaf)->right );
    }
}


void print_inorder(Node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%d\n",tree->value);
        print_inorder(tree->right);
    }
}
void print_preorder(Node * tree)
{
    if (tree)
    {
        printf("%d\n",tree->value);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}
int height (Node *node){
   if(node){
       
       if (height(node->left) > height(node->right)){
           return  height(node->left)+1;
       }else{
           return  height(node->right)+1;
       }
   }else{
      return 0;   
   }
}     
int main(void){
      int tmp;
      root = NULL; 
      insert(60,&root); 
      insert(20,&root);
      insert(30,&root);
      insert(10,&root);
      insert(70,&root);
      insert(100,&root);
      insert(50,&root);
      insert(40,&root);

      printf("IN ORDEM\n");
      print_inorder(root);
      printf("-----------------------------\n");
      printf("Busca Pelo Nó 20\n");
      tmp = search(&root,20);
      printf( "%s\n", (tmp == 1) ? "True": "False" );
      printf("-----------------------------\n");
      printf("Busca Pelo Nó 200\n");
      tmp = search(&root,200);
      printf( "%s\n", (tmp == 1) ? "True": "False" );
      printf("-----------------------------\n");
      printf("Altura da Árvore\n");
      printf("%d\n", height(root));
      
}

