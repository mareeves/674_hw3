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
	  
	//Used to rotate Right 
	Node *rightRotate(Node *x)  
	{  
		Node *y = x->getLeft();  
		x->setLeft(y->getRight());  
		y->setRight(x);  
		return y;  
	}  
	  
	//Used to Rotate Left 
	Node *leftRotate(Node *x)  
	{  
		Node *y = x->getRight();  
		x->setRight(y->getLeft());  
		y->setLeft(x);  
		return y;  
	}  
	  
	
	Node *splay(Node *root, int value)  
	{  
		
		//Base Case 
		if (root == NULL || root->value == value)  
			return root;  
	  
		// value in the left subtree  
		if (root->value > value)  
		{  
			// if the value is not in tree, we are done  
			if (root->getLeft() == NULL) return root;  
	  
			// Zig-Zig (Left Left)  
			if (root->getLeft()->value > value)  
			{
				std::cout << "Zig Zig (Left Left)" << std::endl; 
				root->getLeft()->setLeft(splay(root->getLeft()->getLeft(), value));  
	  
				// Do first rotation for root,  
				// second rotation is done after else  
				root = rightRotate(root);  
			}  
			else if (root->getLeft()->value < value) // Zig-Zag (Left Right)  
			{  
			
				std::cout << "Zig Zag (Left Right)" << std::endl; 
 				root->getLeft()->setRight(splay(root->getLeft()->getRight(), value));  
	  
				// Do first rotation for root->left  
				if (root->getLeft()->getRight() != NULL)  
					root->setLeft(leftRotate(root->getLeft()));  
			}  
	  
			// Do second rotation for root  
			return (root->getLeft() == NULL)? root: rightRotate(root);  
		}  
		else // Key lies in right subtree  
		{  
			// Key is not in tree, we are done  
			if (root->getRight() == NULL) return root;  
	  
			// Zig-Zag (Right Left)  
			if (root->getRight()->value > value)  
			{  
				std::cout << "Zig Zag (Right Left)" << std::endl; 

				root->getRight()->setLeft(splay(root->getRight()->getLeft(), value));  
	  
				// Do first rotation for root->right  
				if (root->getRight()->getLeft() != NULL)  
					root->setRight(rightRotate(root->getRight()));  
			}  
			else if (root->getRight()->value < value)// Zag-Zag (Right Right)  
			{  
				// Bring the key as root of  
				// right-right and do first rotation
				std::cout << "Zag Zag (Right Right)" << std::endl; 
  
				root->getRight()->setRight(splay(root->getRight()->getRight(), value));  
				root = leftRotate(root);  
			}  
	  
			// Do second rotation for root  
			return (root->getRight() == NULL)? root: leftRotate(root);  
		}  
	}  
	  
	// Function to insert a new key k  
	// in splay tree with given root  
	Node *insert(Node *root, int k)  
	{  
		// Simple Case: If tree is empty  
		if (root == NULL){
			return (new Node(k));  
		}
	  
		// Bring the closest leaf node to root  
		root = splay(root, k);  
	  
		// If key is already present, then return  
		if (root->value == k) return root;  
	  
		// Otherwise allocate memory for new node  
		Node *newnode = new Node(k);  
	  
		// If root's key is greater, make  
		// root as right child of newnode  
		// and copy the left child of root to newnode  
		if (root->value > k)  
		{  
			newnode->setRight(root);  
			newnode->setLeft(root->getLeft());  
			root->setLeft(NULL);  
		}  
	  
		// If root's key is smaller, make  
		// root as left child of newnode  
		// and copy the right child of root to newnode  
		else
		{  
			newnode->setLeft(root);  
			newnode->setRight(root->getRight());  
			root->setRight(NULL);  
		}  
	  
		return newnode; // newnode becomes new root  
	}
	
	void insertVector(std::vector<int> & vec){
		Node * root = NULL;
		for(int i = 1; i<=vec.size(); i++){
			root = insert(root, vec[i-1]);
			print2D(root);
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			
		}
		root = search(root, 50);
		print2D(root);
		
	}
	
	Node *search(Node *root, int key)  
	{  
    	return splay(root, key);  
	} 
};  