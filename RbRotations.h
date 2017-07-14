#include "RbStructures.h"

void rotateRight(RB_Tree *tree,RB_Node *node);
void rotateLeft(RB_Tree *tree,RB_Node *node);



/*
    Rotate Left
    
      ...                     ...
        \                       \
        0B                      1R
           \                   /  \
           1R       =>      0B    2R
             \                      \
              2R                    ...
                \
                ...
       the rotation just change the pointer reference of a node
       in this case above the parent o node 0 will be change to 
       node 1R and te left pointer of 1R will be the node 0B
                            
                          ...
                           /
                         1R
                        /
                       0B
                       
       affter this the parent of 1R will be the Parent of 0B
       and the node 2R keep on your position
       
       !the is no colors change in the rotations!
       rotations are Oh(1)

*/






void rotateLeft(RB_Tree *tree,RB_Node *node){
	RB_Node *aux;
	aux = node->right;
	node->right = aux->left;
	if(aux->left != tree->external){
		aux->left->parent =  node;
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

/*
    Rotate Right
    
          ...         ...
          /            /
        2B            1R
        /            /  \
       1R       =>  0R   2B
      /             /
    0R            ...
    /
  ...
       the rotation just change the pointer reference of a node
       in this case above the parent o node 2B will be change to 
       node 1R and te RIGHT pointer of 1R will be the node 2B
                            
                          ...
                           /
                         1R
                           \                       
                           2B
                                
       affter this the parent of 1R will be the Parent of 2B
       and the node 0R keep on your position
       
       !the is no colors change in the rotations!
       rotations are Oh(1)

*/
void rotateRight(RB_Tree *tree,RB_Node *node){

	RB_Node *aux;
	aux = node->left;
	node->left = aux->right;
	if(aux->right != tree->external){
		aux->right->parent =  node;
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

