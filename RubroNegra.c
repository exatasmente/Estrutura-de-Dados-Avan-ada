#include "RubroNegra.h"
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

int balanceFactor(RB_Tree *tree, RB_Node *node ) {
    int bf = 0;

    if( node->left != tree->external ){
        bf += height(tree, node->left );
    }
    if( node->right != tree->external ){
         bf -= height(tree, node->right );
    }
    return bf ;
}

RB_Node *max(RB_Tree *tree, RB_Node *node) {
    RB_Node *aux = node;
    while (aux->right != tree->external) { 
        aux = aux->right;
    }
    return aux;
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
             if(balanceFactor(tree,node->right) < balanceFactor(tree,node->left)){ 
                subst = max(tree,node->left);
                temp = subst->left;
             }else{
                 subst = min(tree,node->right);
                 temp = subst->right;
             }
               
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

                        tree->root = subst;
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
        if (red == RED){
                return;
        }


        while (temp != root && temp->color == BLACK) {

                if (temp == temp->parent->left) {
                        w = temp->parent->right;

                        if (w->color == RED) {
                                puts("CASE 1");
                                w->color = BLACK;
                                temp->parent->color = RED;

                                rotateLeft(tree,temp->parent);

                                w = temp->parent->right;
                        }

                        if (w->left->color == BLACK && w->right->color == BLACK) {
                                puts("CASE 2");
                                w->color =RED;
                                temp = temp->parent;
                        } else {
                                if (w->right->color == BLACK) {
                                        puts("CASE 3");
                                        w->left->color = BLACK;
                                        w->color = RED;
                                        rotateRight(tree, w);
                                        w = temp->parent->right;
                                }
                                puts("CASE 4");
                                w->color =  temp->parent->color;
                                temp->parent->color = BLACK;
                                w->right->color = BLACK;
                                rotateLeft(tree, temp->parent);
                                break;
                        }

                } else {
                        w = temp->parent->left;

                        if (w->color == RED) {
                                puts("CASE 1 R");
                                w->color = BLACK;
                                temp->parent->color = RED;
                                rotateRight(tree, temp->parent);
                                w = temp->parent->left;
                        }

                        if (w->left->color == BLACK && w->right->color == BLACK) {
                                puts("CASE 2 R");
                                w->color = RED;
                                temp = temp->parent;
                        } else {
                                if (w->left->color == BLACK) {
                                        puts("CASE 3 R");
                                        w->right->color = BLACK;
                                        w->color = RED;
                                        rotateLeft(tree, w);
                                        w = temp->parent->left;
                                }
                                puts("CASE 4 R");
                                w->color = temp->parent->color ;
                                temp->parent->color = BLACK;
                                w->left->color = BLACK;

                                rotateRight(tree, temp->parent);

                                break;
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
            if(node == tree->root && node->left == tree->external && node->right == tree->external){
                tree->root = tree->external;
            }else{
                rbDelete(tree,node);
            }
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
                puts("Digite o Valore da Chave");
                    scanf("%d",&val);
                    insert(tree1,val);

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


