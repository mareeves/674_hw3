#include <iostream>
#include "Node.hh"
#include "BST.hh"
#include <vector>
#define COUNT 10  


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


int main(){
	
	//sequential list
	std::vector<int> S1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
	11, 12, 13, 14, 15, 16, 17, 18, 19, 
	20, 21, 22, 23, 24, 25,26, 27, 28, 29, 
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 
	70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100};
	
	//random list
	std::vector<int> S2 = {17,4,32,72,94,34,56,100,
	1,43,71,78,68,93,70,92,65,77,60,49,76,74,13,
	38,51,41,91,20,16,18,19,85,39,6,75,2,28,99,
	87,5,8,81,57,63,55,23,59,46,66,79,86,64,67,
	95,12,42,97,62,69,11,50,44,14,37,98,9,7,45,
	29,24,84,54,83,82,27,33,96,21,35,26,61,3,52,
	31,58,88,47,25,10,30,53,22,80,90,40,89,73,15,48,36
};
	BST *bst = new BST();
	Node * root =  bst->insertVector(S2);
	print2D(root);  
	
	delete(bst);
	delete(root);
	return 0;
}