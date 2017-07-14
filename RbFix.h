void rBFix(RB_Node *root,RB_Node *node,RB_Tree *tree);

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

