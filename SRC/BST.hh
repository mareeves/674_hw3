#include <vector>
#include <math.h>

#define COUNT 10  

class BST{	
	private:
	
	public:
		BST(){
		
		}
		
		~BST(){
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
			
		Node * rotateRight(Node * y, Node * root){
			Node* currentNode = root;
		    Node *x = y->getLeft();  
    		Node *T2 = x->getRight();  
  
    		// Perform rotation  
    		x->setRight(y);  
    		y->setLeft(T2);
    		while(true){
    			if(root == x){
    				break;
    			}
    			else if(currentNode->getRight() == y){
    				std::cout << "parentNode is: " << currentNode->value << std::endl;
    				currentNode->setRight(x);
    				break;
    			}
    			else{
    				currentNode = currentNode->getRight();
    			}
    		}
    		return x;
    	}
    	
    	
		
		Node * createBackBone(Node * root){
			Node * currentNode = root;
			while(currentNode!=NULL){
				while(currentNode->getLeft()!=NULL){
					std::cout << "currentNode is: " << currentNode->value << std::endl;
					if(currentNode->getLeft()->value < root->value){
						root = currentNode->getLeft();
					}
					currentNode = rotateRight(currentNode, root);
				}
				currentNode = currentNode->getRight();
			}
			
			return root;	
		}
		
				
		Node *rotateLeft(Node *x)  
		{  
			Node *y = x->getRight();  
			Node *T2 = y->getLeft();  
		  
			// Perform rotation  
			y->setLeft(x);  
			x->setRight(T2);  
		  
		  
			// Return new root  
			return y;  
		}   
		
		Node * balanceTree(Node * root, int nodeCount){
			Node * currentNode1 = root;
			int expected = ceil(log2(nodeCount)) - nodeCount;
			std::cout << "expected: " << expected << " " << "NodeCount: " << nodeCount << std::endl;
			for(int i = 0; i < expected; i++){
				if(i==0){
					root = rotateLeft(currentNode1);
					currentNode1 = root;
				}
				
				else{
					currentNode1->setRight(rotateLeft(currentNode1));
					currentNode1 = currentNode1->getRight();

				}
			}
			int times = nodeCount;
			while(times>1){
				times/=2;
				root = rotateLeft(root);
				Node * currentNode2 = root;
				for(int i = 0 ; i< times-1; i++){
					//std::cout << "parentNode" << currentNode2->value << std::endl;
					//std::cout << "childNode" << currentNode2->getRight()->value << std::endl;
					currentNode2->setRight(rotateLeft(currentNode2->getRight()));
					currentNode2 = currentNode2->getRight();
				}
			}
			
			
			return root;
		}
		
		
		Node * sortDSW(Node * root, int nodeCount){
			std::cout << "createBackbone" << std::endl;
			root = createBackBone(root);
			root = balanceTree(root, nodeCount);
			return root;
		}
		
		Node * insertVectorDSW(std::vector<int> vec){
			Node * root = NULL;
			for(int i = 1; i<=vec.size(); i++){
				root = insert(root, vec[i-1]);
				if(i%10==0){
					root = sortDSW(root, i);
					std::cout << "Tree height is " << findTreeHeight(root) << std::endl;
					print2D(root);
					std::cout << "done" << std::endl;  
				}
				std::cout << "done" << std::endl;  

			}
			std::cout << "done" << std::endl;  

			return root;
		}
		
		Node * insertVector(std::vector<int> vec){
			Node * root = NULL;
			for(int i = 1; i<=vec.size(); i++){
				root = insert(root, vec[i-1]);
				if(i%10==0){
					std::cout << "Tree height is " << findTreeHeight(root) << std::endl;
					print2D(root);  
				}
			}
			
			return root;
		}  

		
		Node * insert(Node * root, int value){
			if(root == NULL){
				root = new Node(value);
				return root;
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
					Node * rightNode = new Node(value);
					currentNode->setRight(rightNode);
					break;
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
					Node * leftNode = new Node(value);
					currentNode->setLeft(leftNode);
					break;
	
				}
			}
			return root;
		}
		
		Node * deleteNode(int value, Node * root){
			Node * currentNode = root;
			Node * parentNode = root;
			while(true){
				//If the value is the root Node
				if(currentNode->value == value){
					if(currentNode->getLeft() == NULL && currentNode->getRight() == NULL){
						//Checking to see if it is the right or left child
						if(parentNode->value > currentNode->value){ //deleting the left
							parentNode->setLeft(NULL);
						}
						else{ // deleting the right
							parentNode->setRight(NULL);
						}
						delete(currentNode);
						break;
					}
					else if(currentNode->getLeft()!=NULL && currentNode->getRight() == NULL){
						//Checking to see if it is the right or the left child.
						if(parentNode->value > currentNode->value){ //Deleting the left 
							parentNode->setLeft(currentNode->getLeft());
						}
						else{ //deleting the right
							parentNode->setRight(currentNode->getLeft());
						}
						delete(currentNode);
						break;
					}
					
					else if(currentNode->getLeft()==NULL && currentNode->getRight() != NULL){
						//Checking to see if it is the right or the left child
						if(parentNode->value > currentNode->value){ //Deleting the left 
							parentNode->setLeft(currentNode->getRight());
						}
						else{ //deleting the right
							parentNode->setRight(currentNode->getRight());
						}
						delete(currentNode);
						break;						
					}
					
					else if(currentNode->getLeft()!=NULL && currentNode->getRight() != NULL){
						currentNode = currentNode->getRight();
						Node * temp = currentNode->getLeft();
						
						while(temp->getLeft()!=NULL){
							temp = temp->getLeft(); //Should be left child of currentNode
							currentNode = currentNode->getLeft(); // Should be parent to tempNode
						}
						
						if(parentNode->value > value){ //If we are deleting the node to the left
							//temp is replacing parentNode->getLeft();
							temp->setRight(parentNode->getLeft()->getRight());
							temp->setLeft(parentNode->getLeft()->getLeft());
							delete(parentNode->getLeft());
							parentNode->setLeft(temp);
							currentNode->setLeft(NULL);
							break;
						}
						else{ //If we are deleting the node to the right
							//temp is replacing parentNode->getRight()
							temp->setRight(parentNode->getRight()->getRight());
							temp->setLeft(parentNode->getRight()->getLeft());
							delete(parentNode->getRight());
							parentNode->setRight(temp);
							currentNode->setLeft(NULL);
							break;
						}						
					}
				}
				else if(currentNode->value < value){
					parentNode = currentNode;
					currentNode = currentNode->getRight();
				}
				else if(currentNode->value > value){
					parentNode = currentNode;
					currentNode = currentNode->getLeft();
				}
					
			}
			std::cout << "Tree height is " << findTreeHeight(root) << std::endl;
			print2D(root);  
			return root;
		}		

};