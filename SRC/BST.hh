#include <vector>
class BST{	
	private:
	
	public:
		BST(){
		
		}
		
		~BST(){
		}
		
		Node * insertVector(std::vector<int> & vec){
			Node * root = NULL;
			if(vec.size()>0){
				root = new Node(vec[0]);
			}
			for(int i =1; i<vec.size(); i++){
				Node * currentNode = root;
				while(true){
					//if vector value is greater than current Node
					//BUT the node to the right is not free
					if(vec[i] > currentNode->value && currentNode->getRight()!=NULL){
						//shift the node to the right
						currentNode = currentNode->getRight();
					}
					//if vector value is greater than the current Node
					//and the right node is empty
					else if (vec[i] > currentNode->value && currentNode->getRight()==NULL){
						//Create a new node on the heap and have the currentNode point to it
						Node * rightNode = new Node(vec[i]);
						currentNode->setRight(rightNode);
						break;
					}
					
					//if vector value is less than the current Node
					//BUT the left node is not empty
					else if(vec[i] < currentNode->value && currentNode->getLeft()!=NULL){
						//shift the node to the left
						currentNode = currentNode->getLeft();

					}
					
					//if vector value is less than the current Node
					//and the left node is empty
					else if(vec[i] < currentNode->value && currentNode->getLeft()==NULL){
						//Create a new node on the heap and have the currentNode point to it
						Node * leftNode = new Node(vec[i]);
						currentNode->setLeft(leftNode);
						break;

					}
				}
			}
			return root;
		}


};