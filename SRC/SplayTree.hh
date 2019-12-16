class SplayTree{  
	public:
	
	SplayTree(){
		
	}
	
	
	// Function to print binary tree in 2D  
	// It does reverse inorder traversal  
	void print2DUtil(Node *root, int space)  
	{  
		// Base case  
		if (root == NULL)  
			return;  
	  
		// Increase distance between levels  
		space += COUNT;  
	  
		// Process right child first  
		print2DUtil(root->getRight(), space);  
	  
		// Print current node after space  
		// count  
		std::cout<<std::endl;  
		for (int i = COUNT; i < space; i++)  
			std::cout<<" ";  
		std::cout<<root->value<<"\n";  
	  
		// Process left child  
		print2DUtil(root->getLeft(), space);  
	}  
		
		
	void print2D(Node *root)  
	{  
		// Pass initial space count as 0  
		print2DUtil(root, 0);  
	}  
	  
	
  void left_rotate( Node *x, Node * root ) {
    Node *y = x->getRight();
    if(y) {
      x->setRight(y->getLeft());
      if( y->getLeft() ) y->getLeft()->setParent(x);
      y->setParent(x->getParent());
    }
    
    if( !x->getParent() ) root = y;
    else if( x == x->getParent()->getLeft() ) x->getParent()->setLeft(y);
    else x->getParent()->setRight(y);
    if(y) y->setLeft(x);
    x->setParent(y);
  }
  
  void right_rotate( Node *x , Node * root) {
    Node *y = x->getLeft();
    if(y) {
      x->setLeft(y->getRight());
      if( y->getRight() ) y->getRight()->setParent(x);
      y->setParent(x->getParent());
    }
    if( !x->getParent() ) root = y;
    else if( x == x->getParent()->getLeft() ) x->getParent()->setLeft(y);
    else x->getParent()->setRight(y);
    if(y) y->setRight(x);
    x->setParent(y);
  }
  
  void splay( Node *x , Node * root) {
    while( x->getParent() ) {
      if( !x->getParent()->getParent() ) {
        if( x->getParent()->getLeft() == x ) right_rotate( x->getParent() , root);
        else left_rotate( x->getParent() , root);
      } else if( x->getParent()->getLeft() == x && x->getParent()->getParent()->getLeft() == x->getParent() ) {
        right_rotate( x->getParent()->getParent(), root );
        right_rotate( x->getParent() , root);
      } else if( x->getParent()->getRight() == x && x->getParent()->getParent()->getRight() == x->getParent() ) {
        left_rotate( x->getParent()->getParent(), root );
        left_rotate( x->getParent() , root);
      } else if( x->getParent()->getLeft() == x && x->getParent()->getParent()->getRight() == x->getParent() ) {
        right_rotate( x->getParent(), root );
        left_rotate( x->getParent(), root );
      } else {
        left_rotate( x->getParent() , root);
        right_rotate( x->getParent() , root);
      }
    }
  }
	  
	// Function to insert a new key k  
	// in splay tree with given root  
	Node *insert(Node *root, int value)  
	{  
		// Simple Case: If tree is empty  
		if (root == NULL){
			return (new Node(value));  
		}
	  
		Node * currentNode = root;
		while(true){
			//if vector value is greater than current Node
			//BUT the node to the right is not free
			if(value > currentNode->value && currentNode->getRight()!=NULL){
				//shift the node to the right
				currentNode = currentNode->getRight();
			}
			//if vector value is greater than the current Node
			//and the right node is empty
			else if (value > currentNode->value && currentNode->getRight()==NULL){
				//Create a new node on the heap and have the currentNode point to it						
				Node * splayNode = new Node(value);
				currentNode->setRight(splayNode);
				//print2D(root);
				splayNode->setParent(currentNode);
				splay(splayNode, root);
				return splayNode;
			}
			
			//if vector value is less than the current Node
			//BUT the left node is not empty
			else if(value < currentNode->value && currentNode->getLeft()!=NULL){
				//shift the node to the left
				currentNode = currentNode->getLeft();

			}
			
			//if vector value is less than the current Node
			//and the left node is empty
			else if(value < currentNode->value && currentNode->getLeft()==NULL){
				Node * splayNode = new Node(value);
				currentNode->setLeft(splayNode);
				//print2D(root);
				splayNode->setParent(currentNode);
				splay(splayNode, root);
				return splayNode;
			}
		} 
		
	}
	
	void insertVector(std::vector<int> & vec){
		Node * root = NULL;
		for(int i = 1; i<=vec.size(); i++){
			root = insert(root, vec[i-1]);
			print2D(root);
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			
		}
		//root = search(root, 50);
		print2D(root);
		
	}
	
	/*Node *search(Node * splayNode)  
	{  
    	return splay(splayNode);  
	} */
};  