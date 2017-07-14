#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RbRotations.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

char depth[ 2056 ];
int di;




int height(RB_Tree *tree, RB_Node *node );

void preorder(RB_Tree *tree,RB_Node *node);

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



RB_Node *max(RB_Tree *tree, RB_Node *node);
int balanceFactor(RB_Tree *tree, RB_Node *node );
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





void rbDotNil(int key, int nullcount, FILE* stream){
    fprintf(stream, "    null%d [label=\"NIL\", shape=record, width=.4,height=.25, fontsize=16];\n", nullcount);
    fprintf(stream, "    %d -> null%d ;\n", key, nullcount);
}

void rbToDot(RB_Tree *tree, RB_Node * node, FILE* stream){
    static int nullcount = 0;

    if (node->left != tree->external){
        if(node->left->color == RED)
            fprintf(stream, "    %d [fillcolor=red]\n%d -> %d;\n", node->left->value,node->value, node->left->value);
        else
            fprintf(stream, "    %d -> %d ;\n", node->value, node->left->value);
        rbToDot(tree,node->left, stream);
    }else
        rbDotNil(node->value, nullcount++, stream);

    if (node->right != tree->external){
        if(node->right->color == RED)
            fprintf(stream, "    %d[fillcolor=red]\n%d -> %d [weight=%d];\n",node->right->value, node->value, node->right->value);
        else
            fprintf(stream, "    %d -> %d ;\n", node->value, node->right->value);
        rbToDot(tree,node->right, stream);
    }else
        rbDotNil(node->value, nullcount++, stream);
}

void rbDot(RB_Tree* tree,RB_Node *node, FILE* stream){
    fprintf(stream, "digraph RBTREE {\n");
    fprintf(stream, "  graph [ratio=.48];\nnode [style=filled, color=black, shape=circle, width=.6\nfontname=Helvetica,fontweight=bold, fontcolor=white,fontsize=24, fixedsize=true];\n");

    rbToDot(tree,node, stream);

    fprintf(stream, "}\n");
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


void preorder(RB_Tree *tree,RB_Node *node){
	
    if ( node != tree->external )
    { 	
 		printf("%d %s\n", node->value,(node->color == 1 ? "RED" : "BLACK"));
        preorder(tree, node->left );
        preorder(tree, node->right );
    }
    
}


