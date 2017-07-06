#include <stdio.h>
#include <stdlib.h>
/*
 *  The Red Black Tree will need Respect 5 Conditions:
 *  1) a Node cude be RED or BLACK
 *  2) the root is BLACK
 *  3) All external node are BLACK
 *  4) If a node is RED your parent is BLACK
 *  5) Every path tho a external node need be the same numbers of BLACK nodes
 * 
 *  The RB Tree structure have:
 *  the key
 *  a left and right and parent node
 *  the tree->external node is the external node of tree
 *  the external node is BLACK
 */

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


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

void preorder(RB_Tree *tree,RB_Node *node);


void insert(RB_Tree *tree, int value);
RB_Node  *_insert(RB_Tree *tree,RB_Node *root,RB_Node *node );

void rBFix(RB_Node *root,RB_Node *node,RB_Tree *tree);
void rBDelFix(RB_Node *node,RB_Tree *tree);

void rotateRight(RB_Tree *tree,RB_Node *node);
void rotateLeft(RB_Tree *tree,RB_Node *node);

RB_Node* getUncle(RB_Node *node);
RB_Node* getGrandParent(RB_Node *node);


RB_Node* createNode_(RB_Tree *tree);
RB_Node* createNode(RB_Tree *tree,int key);
RB_Tree* createTree();

void removeNode(RB_Tree *tree, RB_Node * node);
void RBremove(RB_Tree *tree,RB_Node *node, int value) ;

RB_Node * min(RB_Tree* tree,RB_Node* node);


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

//Commun Functions from Insert and Remove 

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
       in this case abrove the parent o node 0 will be change to 
       node 1R and te left pointer of 1R will be the node 0B
                            
                          ...
                           /
                         1R
                        /
                       0B
                       
       affter this the parent of 1R will be the Parent of 0B
       and the node 2R keep on your position
       
       !the is no colors change in the rotations!
       rotations are O(1)

*/
void rotateLeft(RB_Tree *tree,RB_Node *node){


	RB_Node *aux;
	aux = node->right;
	node->right = aux->left;
	if(node->right != tree->external){
		node->right->parent =  node;
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
       in this case abrove the parent o node 2B will be change to 
       node 1R and te RIGHT pointer of 1R will be the node 2B
                            
                          ...
                           /
                         1R
                           \                       
                           2B
                                
       affter this the parent of 1R will be the Parent of 2B
       and the node 0R keep on your position
       
       !the is no colors change in the rotations!
       rotations are O(1)

*/
void rotateRight(RB_Tree *tree,RB_Node *node){
	printf("%d RR\n ",node->value);
	RB_Node *aux;
	aux = node->left;
	node->left = aux->right;
	if(node->left != tree->external){
		node->left->parent =  node;
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
	/*
	*		This function is used for Fix Violations after insertion
	*		Case : insert 6
	*		Node -> 6
	*			-----------Tree------------
	*						N10 <- Root
	*						/ \ 	 
	*					  R8   12R
	*					 / \   / \
	*					7N  9N 11N 13N
	*				   /  \/ \ / \ / \
    *	 New Node->  6R
	*
    */
	RB_Node *parent = tree->external;
	RB_Node *grandParent = tree->external;
	
	while(  (node != root  && node->color == RED  && node->parent->color != BLACK) ){

		parent = node->parent;

      /*
       *   Get Parent of Node
       *   Case : insert 6
       *   Node -> 6
       *        -----------Tree------------
       *                   N10 <- Root
       *                   / \  
       *                 R8   12R
       *                 / \   / \
       *    Parent ->  7N  9N 11N 13N
       *               /  \/ \ / \ / \
       *  New Node->  6R
	   *
       */
		grandParent = getGrandParent(node);
      /*
       *  Get GrandParent of Node
       *   Case : insert 6
       *   Node -> 6
       *        -----------Tree------------
       *                   N10 <- Root
       *                  / \  
       *    grandParent-> R8   12R
       *                 / \   / \
       *    Parent->   7N  9N 11N 13N
       *               /  \/ \ / \ / \
       *  New Node->  6R  NN N N N N  N
       *
       */
		if(parent == grandParent->left){

     	/*
		 *	Case insertion Form Left 
		 *	Case : insert 6
		 *	Node -> 6
		 *	Uncle -> 9N*
		 *		-----------Tree------------
		 *					N10 <- Root
		 *					/  \  
		 *	grandParent-> R8   12R
         *               / \   /  \
		 *	Parent->   7N  9N* 11N 13N
         *             /  \/ \ / \ / \
		 *	New Node->6R  NN N N N N  N
         */		
			RB_Node * uncle;
			uncle  = getUncle(node); // Uncle -> 9N
			if( (uncle != tree->external) && ( uncle->color == RED ) ){

			    /*
			        Case Uncle Color = RED
			        The GrandParent will need change the color to RED 
			        parent and uncle will change color to BLACK
			        
			    */
				grandParent->color = RED; 
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandParent;
			}else{

			    /*
			        In Other Case 
			        a Left Rotation will be make
			        case the insertion is from right
			        or Right Rotation case insertion is from Left
			    */
				if(node == parent->right){

					rotateLeft(tree,parent);
					node = parent;
					parent = node->parent;
					
				}

				rotateRight(tree, grandParent);
				/*
				    in this case we need change the color of
				    parent with the grandParent color
				
				*/
				Color aux = parent->color;
                parent->color= grandParent->color;
                grandParent->color = aux;
                node = parent;
				
		  }
		}else{

			RB_Node * uncle;
			uncle  = getUncle(node);
			if( (uncle != tree->external) && ( uncle->color == RED ) ){


				grandParent->color = RED; 
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandParent;
			}else{


				if(node == parent->left){

					rotateRight(tree,parent);
					node = parent;
					parent = node->parent;
					
				}

				rotateLeft(tree, grandParent);
				/*
				    in this case we need change the color of
				    parent with the grandParent color
				
				*/
				Color aux = parent->color;
                parent->color= grandParent->color;
                grandParent->color = aux;
                node = parent;

	    	}
		
	    }
	}
	tree->root->color = BLACK;
}


void rBDelFix(RB_Node *node,RB_Tree *tree){
    RB_Node *aux;
    while(node != tree->root && node->color  == BLACK){
        if(node == node->parent->left){
            aux = node->parent->right;
            if(aux->color == RED){
                aux->color = BLACK;
                node->parent->color = RED;
                rotateLeft(tree,node->parent);
                aux = node->parent->right;
            }
            if(aux->left->color == BLACK && aux->right->color == BLACK){
                aux->color = RED;
                node = node->parent;
            }else{
                if(aux->right->color ==  BLACK){
                    aux->left->color = BLACK;
                    aux->color = RED;
                    rotateRight(tree,aux);
                    aux =  node->parent->right;
                
                }
                aux->color = node->parent->color;
                node->parent->color = BLACK;
                aux->right->color = BLACK;
                rotateLeft(tree,node->parent);
                node = tree->root;
            }
        }else{
            aux = node->parent->left;
            if(aux->color == RED){
                aux->color = BLACK;
                node->parent->color = RED;
                rotateRight(tree,node->parent);
                aux = node->parent->left;
            }
            if(aux->left->color == BLACK && aux->left->color == BLACK){
                aux->color = RED;
                node = node->parent;
            }else{
                if(aux->left->color ==  BLACK){
                    aux->right->color = BLACK;
                    aux->color = RED;
                    rotateRight(tree,aux);
                    aux =  node->parent->left;
                
                }
                aux->color = node->parent->color;
                node->parent->color = BLACK;
                aux->left->color = BLACK;
                rotateRight(tree,node->parent);
                node = tree->root;             
            }
    
    
       }
    
    }   
}


//End of Commun functions 


//Functions for Insert Node


RB_Node* getGrandParent(RB_Node *node){
/*
*    This function is used for get the Grand Parent of a node
*                10 <- GrandParent
*               /  \  
*              8    12 
*             / \   / \
*     Node-> 7   9 11  13
*/
	return node->parent->parent;
}

RB_Node* getUncle(RB_Node *node){
/*
*  This function is used for get the uncle of a node
*				  10
*			     /  \  
*				 8   12 <- Uncle
*				/ \  / \
*		Node-> 7   9 11 13
*			  /\ /\ /\ /\
*	External-> ---------------
*/
	if(node->parent == node->parent->parent->left)
		return node->parent->parent->right;
	else
		return node->parent->parent->left;
}

RB_Node  *_insert(RB_Tree *tree,RB_Node *root,RB_Node *node ){
	/*
     *   This function is used for get the Valid Position for Insert a Node
     *  Case : insert 6
     *   Node -> 6
     *        -----------Tree------------
     *                   10 <- Root
     *                   /  \  
     *                  8    12 
     *                 / \   / \
     *                7   9 11  13
     *               / \ /\ /\  /\
     *  Valid Pos-> | |-----------         
     */
	if (root == tree->external) return node; //Stop Condition 
 
    if (node->value  < root->value){
        root->left = _insert(tree,root->left, node); //Recursive Call case new node is greater 
        root->left->parent = root; //Change Parent
    }
    else if (node->value > root->value){
        root->right = _insert(tree,root->right, node);  //Recursive Call case new node is lower 
        root->right->parent = root;  //Change Parent
    }
 
    return root; //Return node Form Recursive Call
    
}

void insert(RB_Tree *tree, int value){

	RB_Node *node = createNode(tree,value);
    tree->root = _insert(tree,tree->root ,node);
    rBFix(tree->root,node,tree);//Affter Insert will need Fix the Violations
}



//End of Functions for insert
void preorder(RB_Tree *tree,RB_Node *node){
	
    if ( node != tree->external )
    { 	
 		printf("%d %s\n", node->value,(node->color == 1 ? "RED" : "BLACK"));
        preorder(tree, node->left );
        preorder(tree, node->right );
    }
    
}



RB_Node * min(RB_Tree* tree,RB_Node* node) { 
  RB_Node* aux;

  if ( node->right != tree->external) { 
        aux = node;
        while(aux->left != tree->external) {
          aux = aux->left;
        }
    return aux;
    
  }else{
    aux= node->parent;
    while(node == aux->right) {
      node = aux;
      aux  = aux->parent;
    }
    if (aux == tree->root) 
        return tree->external;
    return aux;
  }
}

void RBremove(RB_Tree *tree,RB_Node *node, int value) {

    if (node != tree->external) {

        if (node->value == value) {
            removeNode(tree,node);
        }
        else {

            if (value < node->value) {
                RBremove(tree,node->left, value);
            }
            else {
                RBremove(tree,node->right, value);
            }

        }
 
    }
    else {
        printf("Node : %d Not Found\n", value);
    
    }

}

void removeNode(RB_Tree *tree, RB_Node * node){
  RB_Node *aux;
  RB_Node *aux_aux;
  RB_Node *root= tree->root;

  if(node->left != tree->external || node->right != tree->external)
     aux =  min(tree,node);
  else
     aux = node;
     
  if(aux->left == tree->external)
    aux_aux = aux->right;
  else
    aux_aux  = aux->left;
    aux_aux->parent = aux->parent;

  if(aux->parent == tree->external)
      root = aux_aux;
  else{
        if(aux == aux->parent->left)
            aux->parent->left = aux_aux;
        else
            aux->parent->right = aux_aux;
 }
 if(aux != node){

     node->value = aux->value;
 }
 if(aux->color == BLACK)
        rBDelFix(aux_aux,tree); 
    

}

void traverseDFS(RB_Tree *tree, RB_Node *node, int depth ) {
	int i = 0;


	if( node->right != tree->external ) traverseDFS(tree, node->right, depth + 3 );
	for( i = 0; i < depth; i++ ) putchar( ' ' );
    if(node->color == RED)
    	printf(ANSI_COLOR_RED"%d\n",node->value);
    else 
        printf(ANSI_COLOR_BLUE"%d\n",node->value);
        
   	if( node->left != tree->external ) traverseDFS(tree, node->left, depth + 3 );

}


void DFS( RB_Tree *tree ) {
	traverseDFS(tree, tree->root, 1 );
}


int main(){
    RB_Tree *tree1;
    
    tree1 = createTree();
    
    
 
    insert(tree1,0);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
 
    insert(tree1,1);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
       
    insert(tree1,2);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
    
    insert(tree1,5);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
    
    insert(tree1,14);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    

    insert(tree1,15);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
        
    insert(tree1,20);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
   
    insert(tree1,27);
    DFS(tree1 );    
    puts(ANSI_COLOR_RESET"--------------------------");    
    
    insert(tree1,30);
    DFS(tree1 );
    puts(ANSI_COLOR_RESET"--------------------------");           
    
    insert(tree1,31);
    DFS(tree1 );
    puts(ANSI_COLOR_RESET"--------------------------");    
   
    insert(tree1,32);
    DFS(tree1 );
    puts(ANSI_COLOR_RESET"--------------------------");
            
    RBremove(tree1,tree1->root,1);
    
    DFS(tree1 );
    puts(ANSI_COLOR_RESET"--------------------------");        

    return 0;
}
