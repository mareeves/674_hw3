class Node{
	private:
	Node *left;
	Node *right;
	public:
	int value;
	int height;
	Node(int value){
		left = NULL;
		right = NULL;
		height = 1;
		this->value = value;
	}
	
	~Node(){
	}
	
	void deleteFullTree(){
		Node * left = this->getLeft();
		Node * right = this->getRight();
		if(left!=NULL){
			delete(left);
		}
		else if(right!=NULL){
			delete(right);
		}
	}
	
	
	void setLeft(Node * left){
		this->left = left;
	}
	
	Node * getLeft(){
		return this->left;
	}
	
	void setRight(Node * right){
		this->right = right;
	}
	
	Node * getRight(){
		return this->right;
	}
	
	
	
	
};