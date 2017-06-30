#include <stdio.h>
#include <stdlib.h>

typedef enum { BLACK, RED } Color;

typedef struct RBNode{
  int value;
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right;
  Color color;

}RB_Node;


typedef struct RBTree{
    RB_Node *root;
    RB_Node *external;
    
    
}RB_Tree;


RB_Node* createNode(RB_Tree *tree, int key);
RB_Tree* createTree();
void preorder(RB_Tree *tree,RB_Node *node);
void rotate(RB_Tree *tree , RB_Node *child,RB_Node *node,RB_Node *parent,RB_Node *granParent);
void rBFix(RB_Node *root,RB_Node *node,RB_Tree *tree);
void rotateRight(RB_Tree *tree,RB_Node *node);
void rotateLeft(RB_Tree *tree,RB_Node *node);
RB_Node* getUncle(RB_Node *node);
RB_Node* getGranParent(RB_Node *node);
RB_Node *_insert(RB_Tree *tree,RB_Node *root,RB_Node *node );
void insert(RB_Tree *tree, int value);



RB_Tree* createTree(){
   RB_Tree * newTree;   
     
   newTree = (RB_Tree*) malloc(sizeof(RB_Tree));
   newTree->external = (RB_Node*) malloc(sizeof(RB_Node));   
   newTree->external->color = BLACK;
   newTree->root = newTree->external;
   newTree->root->left = newTree->external;
   newTree->root->right = newTree->external;
   newTree->root->parent = newTree->external;
   
   return newTree;   
}


RB_Node* createNode(RB_Tree *tree,int key){
    RB_Node *newNode ;
    newNode =  (RB_Node*) malloc(sizeof(RB_Node));
    newNode->parent = tree->external;
    newNode->right = tree->external;
    newNode->left = tree->external;
    newNode->value = key;
    newNode->color = RED;
    return newNode;

}
RB_Node* createNode_(RB_Tree *tree){
    RB_Node *newNode;
    newNode = (RB_Node*) malloc(sizeof(RB_Node));
    newNode->parent = tree->external;
    newNode->right = tree->external;
    newNode->left = tree->external;
    newNode->color = RED;
    
    return newNode;

}

void insert(RB_Tree *tree, int value){
	RB_Node *node = createNode(tree,value);
    tree->root = _insert(tree,tree->root ,node);
    rBFix(tree->root,node,tree);
}


RB_Node* getGranParent(RB_Node *node){
	
	return node->parent->parent;
}

RB_Node* getUncle(RB_Node *node){
	if(node->parent == node->parent->parent->left)
		return node->parent->parent->right;
	else
		return node->parent->parent->left;
}

void rotateLeft(RB_Tree *tree,RB_Node *node){
	RB_Node *aux;
	aux = node->right;
	
	node->right = node->left;
	if(aux->left == tree->external){
		aux->parent =  node;
	}
	aux->parent = node->parent;
	
	if(node->parent == tree->external){
		tree->root = aux;
	}else{
		if(node == node->parent->left){
			node->parent->left = aux;
		}else{
			node->parent->right = aux;
		}
	}
	aux->left = node;
	node->parent = 	aux;
	
	
}


void rotateRight(RB_Tree *tree,RB_Node *node){
	RB_Node *aux;
	aux = node->left;
	node->left = node->right;
	if(aux->right == tree->external){
		aux->parent =  node;
	}
	aux->parent = node->parent;
	
	if(node->parent == tree->external){
		tree->root = aux;
	}else{
		if(node == node->parent->left){
			node->parent->left = aux;
		}else{
			node->parent->right = aux;
		}
	}
	aux->right = node;
	node->parent = 	aux;
	
	
}
void rBFix(RB_Node *root,RB_Node *node,RB_Tree *tree){
	RB_Node *parent = NULL;
	RB_Node *granParent = NULL;
	
	while( ( node != root ) && (node->color = RED ) && (node->parent->color != BLACK)){
		
		parent = node->parent;
		granParent = getGranParent(node);
		
		if(parent == granParent->left){
			RB_Node * uncle;
			uncle  = granParent->right;
			if( (uncle != tree->external) && uncle->color == RED ){
				granParent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = granParent;
			}else{
				if(node == parent->right){
					rotateLeft(tree,parent);
					node = parent;
					parent = node->parent;
					
				}
				rotateRight(tree, granParent);
				Color aux = parent->color;
                parent->color= granParent->color;
                granParent->color = aux;
                node = parent;
				
			}
		}else{
			RB_Node *uncle;
			uncle = granParent->left;
			
			if((uncle != tree->external) && (uncle->color == RED) ){
				granParent->color = RED;
				parent->color = BLACK;
				uncle->color = BLACK;
				node = granParent;
				
				
				
			}else{
				 if(node == parent->left){
					 rotateRight(tree,parent);
					 node = parent;
					 parent = node->parent;
					 
				 }
				 rotateLeft(tree,granParent);
				 Color aux = parent->color;
					parent->color= granParent->color;
					granParent->color = aux;
					node = parent;
			}
 
			
		}
		
	}
	tree->root->color = BLACK;
}

RB_Node  *_insert(RB_Tree *tree,RB_Node *root,RB_Node *node ){
	
	if (root == tree->external)
       return node;
 
    
    if (node->value < root->value)
    {
        root->left  = _insert(tree,root->left, node);
        root->left->parent = root;
    }
    else if (node->value > root->value)
    {
        root->right = _insert(tree,root->right, node);
        root->right->parent = root;
    }
 
    
    return root;
    
}


void preorder(RB_Tree *tree,RB_Node *node){
	
    if ( node != tree->external )
    { 	
		printf("%d %s\n", node->value,(node->color == 1 ? "RED" : "BLACK"));
        preorder(tree, node->left );
        preorder(tree, node->right );
    }
    
}

int main(){
    RB_Tree *tree1;
    
    tree1 = createTree();
    
    insert(tree1,11);
    insert(tree1,10);
    insert(tree1,9);
    insert(tree1,15);
    insert(tree1,8);
    insert(tree1,7);
    preorder(tree1,tree1->root);
    
    return 0;
}


