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


