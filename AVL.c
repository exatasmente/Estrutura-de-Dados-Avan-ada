#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int value;
  struct node *left;
  struct node *right;

}Node;

typedef struct tree {
	Node *root;
}Tree;

Tree *tree = NULL;

void DFS( Tree *tree );
void traverseDFS( Node *node, int depth ) ;
void balance( Tree *tree );
Node *balanceNode( Node *node );
int avlHeight( Node *node );
void insert( int val , Tree *tree) ;
int search( Node *node, int val );
int balanceFactor( Node *node );
Node *removeNode(Node *node, int value);

Tree *create() {
    Tree *tree = NULL;

    if( ( tree = malloc( sizeof( Tree ) ) ) == NULL ) {
	     return NULL;
    }
    tree->root = NULL;

    return tree;
}

Node *createNode() {
    Node *node = NULL;
    if( ( node = malloc( sizeof( Node ) ) ) == NULL ) {
   	    return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->value = 0;
    return node;	
}

int balanceFactor( Node *node ) {
    int bf = 0;

    if( node->left  ){
        bf += avlHeight( node->left );
    }
    if( node->right ){
         bf -= avlHeight( node->right );
    }
    return bf ;
}

int search( Node *node, int val ){
    if( node == NULL  ){
        return 0;
    }
    if( val <  node-> value ){

        search(node->left , val );

    }else if( val > node->value){
        search( node->right , val );

    }else if( val == node->value ){
        return 1;
    }
}
Node *min(Node *node) {
    Node *aux = node;
    while (aux->left != NULL) { 
        aux = aux->left;
    }
    return aux;
}

Node *max(Node *node) {
    Node *aux = node;
    while (aux->right != NULL) { 
        aux = aux->right;
    }
    return aux;
}


Node *removeLeaf(Node *node) {
    free(node);
    return NULL;
}


Node *removeLeft(Node *node) {
    Node *aux = node->left;
    free(node);
    return aux;
}

Node *removeRight(Node *node) {
    Node *aux = node->right;
    free(node);
    return aux;
}


Node *removeBoth(Node *node) {
    Node *aux;
    int value;
    if(balanceFactor(node->right) < balanceFactor(node->left)) aux = max(node->left);
    else aux = min(node->right);
    value = aux->value;
    removeNode(node,aux->value);
    node->value = value;

    return node;
}

Node *_remove(Node *node) {

    if (node->right == NULL && node->left == NULL) {
        node = removeLeaf(node);
    }
    else {
        if (node->right == NULL) {
            node = removeLeft(node);
        }
        else {
            if (node->left == NULL) {
                node = removeRight(node);
            }
            else {
                node = removeBoth(node);
            }
        }
    }
    return node;
}




Node *removeNode(Node *node, int value) {

    if (node != NULL) {

        if (node->value == value) {
            node = _remove(node);
        }
        else {

            if (value < node->value) {
                node->left = removeNode(node->left, value);
            }
            else {
                node->right = removeNode(node->right, value);
            }
               node = balanceNode(node);
        }
 
    }
    else {
        printf("Node : %d Not Found\n", value);
    
    }
    return node;
}

void insert( int val , Tree *tree) {
	Node *node = NULL;
	Node *next = NULL;
	Node *last = NULL;

	if( tree->root == NULL ) {
		node = createNode();
		node->value = val;

		tree->root = node;
	} else {
		next = tree->root;
		while( next != NULL ) {
			last = next;
			if( val < next->value ) {
			    next = next->left;

			} else if( val > next->value ) {
			     next = next->right;

			} else if( val == next->value ) {
                             break;
   		    }
		}

		node = createNode();
		node->value = val;

		if( val < last->value ){
                    last->left = node;
        }
		if( val > last->value ){
                    last->right = node;
        }
		
	}

	balance( tree );
}

int avlHeight( Node *node ) {
	int hLeft = 0;
	int hRight = 0;

	if( node->left ){
            hLeft = avlHeight(node->left);
        }
	if( node->right ){
            hRight = avlHeight( node->right );
        }

	return hRight > hLeft ? ++hRight : ++hLeft;
}


Node *rotateLeftLeft( Node *node ) {

 	Node *a = node;
	Node *b = a->left;
	
	a->left = b->right;
	b->right = a;

	return( b );
}

Node *rotateLeftRight( Node *node ) {

	Node *a = node;
	Node *b = a->left;
	Node *c = b->right;
	
	a->left = c->right;
	b->right = c->left; 
	c->left = b;
	c->right = a;

	return( c );
}


Node *rotateRightLeft( Node *node ) {

	Node *a = node;
	Node *b = a->right;
	Node *c = b->left;
	
	a->right = c->left;
	b->left = c->right; 
	c->right = b;
	c->left = a;

	return( c );
}


Node *rotateRightRight( Node *node ) {

	Node *a = node;
	Node *b = a->right;
	
	a->right = b->left;
	b->left = a; 

	return( b );
}


Node *balanceNode( Node *node ) {
	Node *newroot = NULL;

	if( node->left ){
		node->left  = balanceNode( node->left  );	
        }
	if( node->right ){
		node->right = balanceNode( node->right );
        }

	int bf = balanceFactor( node );

	if( bf >= 2 ) {
            if( balanceFactor( node->left ) <= -1 ){ 
	            newroot = rotateLeftRight( node );
            }else{ 
    	        newroot = rotateLeftLeft( node );
            }
 
	}else{
           if( bf <= -2 ) {
	       if( balanceFactor( node->right ) >= 1 ){
		           newroot = rotateRightLeft( node );
               }else{ 
		           newroot = rotateRightRight( node );
               }

	   }else{
   	        newroot = node;
    	   }
        }

	return( newroot );	
}


void balance( Tree *tree ) {

	Tree *newroot = NULL;

	newroot = balanceNode( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot; 
	}
}

void traverseDFS( Node *node, int depth ) {
	int i = 0;

	if( node->left ){
              traverseDFS( node->left, depth + 2 );
        }
	for( i = 0; i < depth; i++ ) putchar( ' ' );
	printf( "%d : %d\n", node->value,balanceFactor(node));

	if( node->right ) traverseDFS( node->right, depth + 2 );
}


void DFS( Tree *tree ) {
	traverseDFS( tree->root, 0 );
}

inOrder( Node *tree )
{
    if (tree)
    {
        inOrder(tree->left);
        printf("%d\n",tree->value);
        inOrder(tree->right);
    }
}
preOrder(Node *tree)
{
    if ( tree )
    { 
        printf("%d\n", tree->value );
        preOrder( tree->left );
        preOrder( tree->right );
    }

}
posOrder(Node *tree)
{
    if ( tree )
    { 
        posOrder( tree->left );
        posOrder( tree->right );
        printf("%d\n", tree->value );
    }

}

void main(){
 
      tree = create();
      int tmp = 0 ;
      insert(8,tree); 
      insert(5,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(7,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(4,tree);
      insert(12,tree);
      preOrder(tree->root); 
puts("-------------------");
      insert(14,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(10,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(9,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(3,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(6,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(11,tree);
      preOrder(tree->root);
puts("-------------------");
      insert(13,tree);

puts("-------------------");
      tree->root = removeNode(tree->root,3);
      preOrder(tree->root);
puts("-------------------");
    tree->root = removeNode(tree->root,10);
    tree->root = removeNode(tree->root,12);

      puts("-------------------");
      preOrder(tree->root);

}

