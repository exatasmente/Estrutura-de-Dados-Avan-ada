#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
 
#define COLOR_RED     "\x1b[31m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

char depth[ 2056 ];
int di;

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
int height(RB_Tree *tree, RB_Node *node );
void Print(RB_Tree *tree, RB_Node* node );
void DFS( RB_Tree *tree ); 
void Push( char c ); 
void Pop( );

void rbDot(RB_Tree* tree,RB_Node *node, FILE* stream);
void rbToDot(RB_Tree *tree, RB_Node * node, FILE* stream);
void rbDotNil(int key, int nullcount, FILE* stream);

void insert(RB_Tree *tree, int value);
RB_Node  *_insert(RB_Tree *tree,RB_Node *root,RB_Node *node );
void rBFix(RB_Node *root,RB_Node *node,RB_Tree *tree);


RB_Node *min(RB_Tree *tree,RB_Node *node);
void rotateRight(RB_Tree *tree,RB_Node *node);
void rotateLeft(RB_Tree *tree,RB_Node *node);
void rbDelete(RB_Tree *tree, RB_Node *node);

RB_Node* getUncle(RB_Node *node);
RB_Node* getGrandParent(RB_Node *node);


RB_Node* createNode_(RB_Tree *tree);
RB_Node* createNode(RB_Tree *tree,int key);
RB_Tree* createTree();


void RBremove(RB_Tree *tree,RB_Node *node, int value) ;
RB_Node * sucessor(RB_Tree* tree,RB_Node* node);




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
       rotations are O(1)

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
       rotations are O(1)

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
	
	while( node->parent->color != BLACK) {
		parent = node->parent;
		grandParent = getGrandParent(node);
		
		if(parent == grandParent->left){

			RB_Node * uncle;
			uncle  = getUncle(node);
			if( (uncle != tree->external) && ( uncle->color == RED ) ){

				grandParent->color = RED; 
				parent->color = BLACK;
				uncle->color = BLACK;
				node = grandParent;
			}else{
				if(node == parent->right){

					rotateLeft(tree,parent);
					node = parent;
					parent = node->parent;
					
				}
				rotateRight(tree, grandParent);
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
				Color aux = parent->color;
                parent->color= grandParent->color;
                grandParent->color = aux;
                node = parent;
	    	}
		
	    }
	}
	tree->root->color = BLACK;
}

void rbDelete(RB_Tree *tree, RB_Node *node){
        Color red;
        RB_Node *root = tree->root;
        RB_Node *NIL = tree->external;
        RB_Node *subst, *temp, *w;

        if (node == NIL) {
                return;
        } else if (node->left == NIL) {
                temp = node->right;
                subst = node;
        } else if (node->right == NIL) {
                temp = node->left;
                subst = node;
        } else {
                subst = min(tree,node->right);
                temp = subst->right;
               
        }

        if (subst == root) {
                root = temp;
                temp->color = BLACK;
                return;
        }

        red = subst->color;

        if (subst == subst->parent->left) {
                subst->parent->left = temp;
        } else {
                subst->parent->right = temp;
        }

        if (subst == node) {
                temp->parent = subst->parent;
        } else {
                if (subst->parent == node) {
                        temp->parent = subst;
                } else {
                        temp->parent = subst->parent;
                }
                
                subst->left = node->left;
                subst->right = node->right;
                subst->parent = node->parent;
                subst->color =  node->color;
                
                if (node == root) {
                        root->value = subst->value;
                } else {
                        if (node == node->parent->left) {
                                node->parent->left = subst;
                        } else {
                                node->parent->right = subst;
                        }
                }

                if (subst->left != NIL) {
                        subst->left->parent = subst;
                }

                if (subst->right != NIL) {
                        subst->right->parent = subst;
                }
        }
        if (red) {
                return;
        }


        while (temp != root && temp->color == BLACK) {

                if (temp == temp->parent->left) {
                        w = temp->parent->right;

                        if (w->color == RED) {
                                w->color = BLACK;
                                temp->parent->color = RED;
                                rotateLeft(tree,temp->parent);
                                w = temp->parent->right;
                        }

                        if (w->left->color == BLACK && w->right->color == BLACK) {
                                w->color =RED;
                                temp = temp->parent;
                        } else {
                                if (w->right->color == BLACK) {
                                        w->left->color = BLACK;
                                        w->color = RED;
                                        rotateRight(tree, w);
                                        w = temp->parent->right;
                                }

                                w->color =  temp->parent->color;
                                temp->parent->color = BLACK;
                                w->right->color = BLACK;
                                rotateLeft(tree, temp->parent);
                                temp = root;
                        }

                } else {
                        w = temp->parent->left;

                        if (w->color == RED) {
                                w->color = BLACK;
                                temp->parent->color = RED;
                                rotateRight(tree, temp->parent);
                                w = temp->parent->left;
                        }

                        if (w->left->color == BLACK && w->right->color == BLACK) {
                                w->color = RED;
                                temp = temp->parent;
                        } else {
                                if (w->left->color == BLACK) {
                                        w->right->color = BLACK;
                                        w->color = RED;
                                        rotateLeft(tree, w);
                                        w = temp->parent->left;
                                }

                                w->color = temp->parent->color ;
                                temp->parent->color = BLACK;
                                w->left->color = BLACK;
                                rotateRight(tree, temp->parent);
                                temp = root;
                        }
                }
        }

        temp->color = BLACK;
      
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


    
RB_Node *min(RB_Tree *tree,RB_Node *node){
  RB_Node *current = node;
    
    while (current->left != tree->external) {
    current = current->left;
  }
  return current;
}

void RBremove(RB_Tree *tree,RB_Node *node, int value) {

    if (node != tree->external) {

        if (node->value == value) {
                rbDelete(tree,node);
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

int height(RB_Tree *tree,RB_Node *node){
	int hLeft = 0;
	int hRight = 0;

	if( node->left !=  tree->external  ){
            hLeft = height(tree,node->left);
        }
	if( node->right != tree->external ){
            hRight = height(tree, node->right );
        }

	return hRight > hLeft ? ++hRight : ++hLeft;
}


void Push( char c ){
    depth[ di++ ] = ' ';
    depth[ di++ ] = c;
    depth[ di++ ] = ' ';
    depth[ di++ ] = ' ';
    depth[ di ] = 0;
}

void Pop( ){   
    depth[ di -= 4 ] = 0;
}
 
void Print(RB_Tree *tree, RB_Node* node ){
    if(node == tree->external)
           printf(COLOR_BLUE"( )\n");
    else{
        if(node->color == RED)
            printf(COLOR_RED"( %d )\n", node->value );
        else
           printf(COLOR_BLUE"( %d )\n", node->value );
    }
    if ( node != tree->external ){ 
        printf(COLOR_RESET"%s `--", depth );
        Push( '|' );
        Print(tree, node->right );
        Pop( );
 
        printf(COLOR_RESET"%s `--", depth );
        Push( ' ' );
        Print(tree, node->left );
        Pop( );
    }
}

void DFS( RB_Tree *tree ) {
   	Print(tree,tree->root);
	
}


void rbDotNil(int key, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [label=\"NIL\", shape=record, width=.4,height=.25, fontsize=16];\n", nullcount);
    fprintf(stream, "    %d -> null%d ;\n", key, nullcount);
}

void rbToDot(RB_Tree *tree, RB_Node * node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left != tree->external)
    {
        if(node->left->color == RED)
            fprintf(stream, "    %d [fillcolor=red]\n%d -> %d;\n", node->left->value,node->value, node->left->value);
        else
            fprintf(stream, "    %d -> %d ;\n", node->value, node->left->value);
        rbToDot(tree,node->left, stream);
    }
    else
        rbDotNil(node->value, nullcount++, stream);

    if (node->right != tree->external)
    {
        if(node->right->color == RED)
            fprintf(stream, "    %d[fillcolor=red]\n%d -> %d [weight=%d];\n",node->right->value, node->value, node->right->value);
        else
            fprintf(stream, "    %d -> %d ;\n", node->value, node->right->value);
        rbToDot(tree,node->right, stream);
    }
    else
        rbDotNil(node->value, nullcount++, stream);
}

void rbDot(RB_Tree* tree,RB_Node *node, FILE* stream)
{
    fprintf(stream, "digraph RBTREE {\n");
    fprintf(stream, "  graph [ratio=.48];\nnode [style=filled, color=black, shape=circle, width=.6\nfontname=Helvetica,fontweight=bold, fontcolor=white,fontsize=24, fixedsize=true];\n");

    rbToDot(tree,node, stream);

    fprintf(stream, "}\n");
}

int main(){
    RB_Tree *tree1;    
    tree1 = createTree();
    int fim =1;
    int val;
    int op =0 ;
    int qt;
    char *str;
    char *syt;
    char *dot;
    FILE *arq;
    int tam;
    do{
        puts(COLOR_RESET"Rubro Negra\n1-> inserir Nó\n2->Remover Nó\n3->Mostrar Árvore\n4->Gerar Grafo\n5->Sair");
        scanf("%d",&op);
        system("clear");        
        switch(op){

            case 1:
                puts("Digite a quntidade de Nós à Ser Inserida");
                scanf("%d",&qt);
                puts("Digite os Valores das Chaves");

                for(int b = 0 ; b < qt ; b++){
                    scanf("%d",&val);
                    insert(tree1,val);
                }
                break;
            case 2:
                puts("Digite o Valor da Chave");
                scanf("%d",&val);
                RBremove(tree1,tree1->root,val);
                break;                
            case 3:
                DFS(tree1 );    
                break;       
            case 4:
                str = malloc(30);
                puts("nome do Arquivo");
                scanf("%s.dot",str);

                dot = malloc(7);
                snprintf(dot, 40, "%s%s", str,".png");
                printf("%s\n",dot);

                arq = fopen(str,"w");
                rbDot(tree1,tree1->root, arq);
                fclose(arq);
                tam = 100;
                syt = malloc(tam);

                snprintf(syt,tam,"%s%s%s%s","sudo dot -Tpng ",str," -o ",dot);
                system(syt);
                break;
            case 5:
                fim = 0;
                break;
       }
    }while(fim != 0);
    return 0;
}

