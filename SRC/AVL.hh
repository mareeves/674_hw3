class AVL{

	private:
	
	public:
	
	AVL (){
	}
	
	~AVL(){
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
	
	
	int findTreeHeight(Node* node)  
	{  
		if (node == NULL)  
			return 0;  
		else
		{  
			/* compute the depth of each subtree */
			int leftHeight = findTreeHeight(node->getLeft());  
			int rightHeight = findTreeHeight(node->getRight());  
		  
			/* use the larger one */
			if (leftHeight > rightHeight)  
				return(leftHeight + 1);  
			else return(rightHeight + 1);  
		}  
	}
	
	
	/* Given a non-empty binary search tree,  
	return the node with minimum key value  
	found in that tree. Note that the entire  
	tree does not need to be searched. */
	Node * minValueNode(Node* node)  
	{  
		Node* current = node;  
	  
		/* loop down to find the leftmost leaf */
		while (current->getLeft() != NULL)  
			current = current->getLeft();  
	  
		return current;  
	}  
	
	
	// Recursive function to delete a node  
	// with given key from subtree with  
	// given root. It returns root of the  
	// modified subtree.  
	Node* deleteNode(Node* root, int value)  
	{  
		  
		// STEP 1: PERFORM STANDARD BST DELETE  
		if (root == NULL)  
			return root;  
	  
		// If the key to be deleted is smaller  
		// than the root's key, then it lies 
		// in left subtree  
		if ( value < root->value )  
			root->setLeft(deleteNode(root->getLeft(), value));  
	  
		// If the key to be deleted is greater  
		// than the root's key, then it lies  
		// in right subtree  
		else if( value > root->value )  
			root->setRight(deleteNode(root->getRight(), value));  
	  
		// if key is same as root's key, then  
		// This is the node to be deleted  
		else
		{  
			// node with only one child or no child  
			if( (root->getLeft() == NULL) || 
				(root->getRight() == NULL) )  
			{  
				Node *temp = root->getLeft() ?  
							 root->getLeft() :  
							 root->getRight();  
	  
				// No child case  
				if (temp == NULL)  
				{  
					temp = root;  
					root = NULL;  
				}  
				else // One child case  
				*root = *temp; // Copy the contents of  
							   // the non-empty child  
				free(temp);  
			}  
			else
			{  
				// node with two children: Get the inorder  
				// successor (smallest in the right subtree)  
				Node* temp = minValueNode(root->getRight());  
	  
				// Copy the inorder successor's  
				// data to this node  
				root->value = temp->value;  
	  
				// Delete the inorder successor  
				root->setRight(deleteNode(root->getRight(), temp->value));  
			}  
		}  
	  
		// If the tree had only one node 
		// then return  
		if (root == NULL)  
		return root;  
	  
		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
		root->height = 1 + max(height(root->getLeft()),  
							   height(root->getRight()));  
	  
		// STEP 3: GET THE BALANCE FACTOR OF  
		// THIS NODE (to check whether this  
		// node became unbalanced)  
		int balance = getBalance(root);  
	  
		// If this node becomes unbalanced,  
		// then there are 4 cases  
	  
		// Left Left Case  
		if (balance > 1 &&  
			getBalance(root->getLeft()) >= 0)  
			return rightRotate(root);  
	  
		// Left Right Case  
		if (balance > 1 &&  
			getBalance(root->getLeft()) < 0)  
		{  
			root->setLeft(leftRotate(root->getLeft()));  
			return rightRotate(root);  
		}  
	  
		// Right Right Case  
		if (balance < -1 &&  
			getBalance(root->getRight()) <= 0)  
			return leftRotate(root);  
	  
		// Right Left Case  
		if (balance < -1 &&  
			getBalance(root->getRight()) > 0)  
		{  
			root->setRight(rightRotate(root->getRight()));  
			return leftRotate(root);  
		}  
	  
		return root;  
	}  
	
	 
	
	// Check to see the difference in height between the left
	// and the right nodes  
	int getBalance(Node *N)  
	{  
		if (N == NULL)  
			return 0;  
		return height(N->getLeft()) - height(N->getRight());  
	}
	  
	//return the height of the Node
	int height(Node *N)  
	{  
		if (N == NULL)  
			return 0;  
		return N->height;  
	} 
	
	//Get the maximum of two integers
	// of two integers  
	int max(int a, int b)  
	{  
		return (a > b)? a : b;  
	}
	 
	
	//Left rotate 
	Node *leftRotate(Node *x)  
	{  
	
		/*
		
			x
			 \
			  y
			 /
			yLeft
			
			ROTATE
			
			y
		   /
		  x
		   \
		    yLeft
		
		
		*/
		
		//Set y equal to x right
		Node *y = x->getRight();

		//yLeft equal to y left   
		Node *yLeft = y->getLeft();  

		// Perform rotation  
		y->setLeft(x);  
		x->setRight(yLeft);
		
		std::cout << "Rotating Left" << std::endl; 
  
	  
		// Update heights  
		x->height = max(height(x->getLeft()),     
						height(x->getRight())) + 1;  
		y->height = max(height(y->getLeft()),  
						height(y->getRight())) + 1;  
	  
		// Return the new root
		  
		return y;  
	}
	
	Node *leftRotate(Node *x, Node * parent){
		//Set y equal to x right
		Node *y = x->getRight();

		//yLeft equal to y left   
		Node *yLeft = y->getLeft();  

		// Perform rotation  
		y->setLeft(x);  
		x->setRight(yLeft);
		parent->setRight(y);
		std::cout << "Rotating Left" << std::endl; 
  
	  
		// Update heights  
		x->height = max(height(x->getLeft()),     
						height(x->getRight())) + 1;  
		y->height = max(height(y->getLeft()),  
						height(y->getRight())) + 1;  
	  
		// Return the new root
		  
		return parent; 
	}   
	
	//Right rotate function
	Node *rightRotate(Node *y)  
	{  
	
		/*
				y
			   /
			  x
			   \
			   	xRight
			   	
			   	ROTATE
			   	
			   	x
			   	 \
			   	  y
			   	 /
		      xRight
		      
		*/
		
		   
		// Get the y's left Node
		Node *x = y->getLeft();
		//get x's Right node  
		Node *xRight = x->getRight();  
	  
	  	std::cout << "Rotate right" << std::endl; 

		//x's right node is now y  
		x->setRight(y);
		
		//y's left node is nor x'Right node
		y->setLeft(xRight);
		  
	  	
		// Update heights  
		y->height = max(height(y->getLeft()), 
						height(y->getRight())) + 1;  
		x->height = max(height(x->getLeft()), 
						height(x->getRight())) + 1;  
	  
		// Return new root  
		return x;  
	}
	
	
	Node *rightRotate(Node *y, Node * parent)  
	{  
	
		/*
				y
			   /
			  x
			   \
			   	xRight
			   	
			   	ROTATE
			   	
			   	x
			   	 \
			   	  y
			   	 /
		      xRight
		      
		*/
		
		   
		// Get the y's left Node
		Node *x = y->getLeft();
		//get x's Right node  
		Node *xRight = x->getRight();  
	  
	  	std::cout << "Rotate right" << std::endl; 

		//x's right node is now y  
		x->setRight(y);
		
		//y's left node is nor x'Right node
		y->setLeft(xRight);
		  
	  	parent->setLeft(x);
		// Update heights  
		y->height = max(height(y->getLeft()), 
						height(y->getRight())) + 1;  
		x->height = max(height(x->getLeft()), 
						height(x->getRight())) + 1;  
	  
		// Return new root  
		return parent;  
	}  
	
	void insertVector(std::vector<int> vec){
		Node * root = NULL;
		for(int i = 1; i <= vec.size(); i++){
			//std::cout << "Vec[i] is " << vec[i] << std::endl;
			root = insert(root, vec[i-1]);
			print2D(root);
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
		}
		
		deleteNode(root, 3);
		print2D(root);
	}
	
	// Recursive function to insert a key 
	// in the subtree rooted with node and 
	// returns the new root of the subtree.  
	Node* insert(Node* node, int value)  
	{  
		//When the tree is empty return the root
		if (node == NULL){ 
			node = new Node(value);
			return(node);
		}  
	  	//If the value is less than the node value
	  	//insert into the left side
		if (value < node->value){ 
		  node->setLeft(insert(node->getLeft(), value)); 
		}
		//If the value is greater than the node value
		//insert into the right side 
		else if (value > node->value){
		  node->setRight(insert(node->getRight(), value));  
		}
		else{
			return node;
		}  
	  
		//Update the height of the parent Node
		node->height = 1 + max(height(node->getLeft()),  
							height(node->getRight()));  
	  
		//We need to check to see if the Node has become unbalanced
		std::cout << node->value << std::endl;
		std::cout << height(node) << std::endl;
		std::cout << height(node->getLeft()) << std::endl;
		std::cout << height(node->getRight()) << std::endl; 
		int balance = getBalance(node);  
	  
		//Now we got through the cases where the Node has become unbalanced
		//There are four altogether 
	  
	  
		// Left Left Case  
		if (balance > 1 && value < node->getLeft()->value){
		  	std::cout << "Left-Left Case" << std::endl;
			return rightRotate(node);  
		}
	  
		// Right Right Case  
		if (balance < -1 && value > node->getRight()->value) {
			std::cout << "Right-Right Case" << std::endl;
			return leftRotate(node);
		} 
	  
		// Left Right Case  
		if (balance > 1 && value > node->getLeft()->value){
			std::cout << "Left-Right Case" << std::endl;
  
			node->setLeft(leftRotate(node->getLeft()));  
			return rightRotate(node);  
		}  
	  
		// Right Left Case  
		if (balance < -1 && value < node->getRight()->value) {
			std::cout << "Right-Left Case" << std::endl;
  
			node->setRight(rightRotate(node->getRight()));  
			return leftRotate(node);  
		}
		  
	  	//If the node was not unbalanced then return the node pointer
		return node;  
	}

};