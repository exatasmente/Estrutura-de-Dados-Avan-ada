#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int value;
  struct node *left;
  struct node *right;

}Node;

Node *root = 0;

// A função busca retorna 1 caso a chave exista na arvore e 0 caso contrário
int search(Node *root, int val){
    if(root == NULL ){
        return 0;
    }
    if( val  <root-> value ){
        search(root->left, val );
    }else if( val > root-> value){
        search( root-> right, val );
    }else if( val == root-> value ){
        return 1;
    }
}

Node *insert(int key, Node *root){
    if( root == NULL ){
        root = (Node*) malloc( sizeof( Node ) );
        root->value = key;
        root->left = 0;    
        root->right = 0;  
        return root;
    }
    else if(key < root->value)
    {
      
       root->left = insert( key, root->left );
    }
    else if(key > root->value)
    {
        
        root->right = insert( key, root->right );
    }
}


// Calcula a Altura da Arvore
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
int min(Node *raiz) {
        int min = raiz->value;
        while (raiz->left != NULL) {
            min = raiz->left->value;
            raiz = raiz->left;
        }
        return min;
}


Node *removerChave(Node *raiz, int chave) {
        if (raiz == NULL) {
            return raiz;
        }

        if (chave < raiz->value) {
            raiz->left =  removerChave(raiz->left, chave);
        } else if (chave > raiz->value) {
            raiz->right = removerChave(raiz->right, chave);
        } else {
            if (raiz->left == NULL) {
                return raiz->right;
            } else if (raiz->right == NULL) {
                return raiz->left;
            }

            raiz->value = min(raiz->right);

            raiz->right = removerChave(raiz->right, chave);
        }

        return raiz;
}


void print_inorder(Node * tree){
    if (tree){
        print_inorder(tree->left);
        printf("%d\n",tree->value);
        print_inorder(tree->right);
    }
}
void print_preorder(Node * tree){
    if (tree){
        printf("%d\n",tree->value);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}
void print_posorder(Node * tree){
    if (tree){
        print_inorder(tree->left);
        print_inorder(tree->right);
        printf("%d\n",tree->value);
    }
}
  

int main(void){
      int tmp;
      root = NULL; 
      root = insert(60,root); 
      root = insert(20,root);
      root = insert(30,root);
      root = insert(10,root);
      root = insert(70,root);
      root = insert(100,root);
      root = insert(50,root);
      root = insert(40,root);


      root= removerChave(root,30);
      printf("IN ORDEM\n");
      print_inorder(root);
      printf("-----------------------------\n");
      printf("Busca Pelo Nó 20\n");
      tmp = search(root,20);
      printf( "%s\n", (tmp == 1) ? "True": "False" );
      printf("-----------------------------\n");
      printf("Busca Pelo Nó 200\n");
      tmp = search(root,200);
      printf( "%s\n", (tmp == 1) ? "True": "False" );
      printf("-----------------------------\n");
      printf("Altura da Árvore\n");
      printf("%d\n", height(root));
      
}
