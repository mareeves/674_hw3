/*
 *  C++ Program to Implement Splay Tree
 */
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
 
struct splay
{
    int key;
    splay* lchild;
    splay* rchild;
};
 
class SplayTree
{
    public:
        SplayTree()
        {
        }
        
        // Function to print binary tree in 2D  
		// It does reverse inorder traversal  
		void print2DUtil(splay *root, int space)  
		{  
			// Base case  
			if (root == NULL)  
				return;  
		  
			// Increase distance between levels  
			space += COUNT;  
		  
			// Process right child first  
			print2DUtil(root->rchild, space);  
		  
			// Print current node after space  
			// count  
			std::cout<<std::endl;  
			for (int i = COUNT; i < space; i++)  
				std::cout<<" ";  
			std::cout<<root->key<<"\n";  
		  
			// Process left child  
			print2DUtil(root->lchild, space);  
		}  
		
		
		void print2D(splay *root)  
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
 
        // RR(Y rotates to the right)
        splay* RR_Rotate(splay* k2)
        {
            splay* k1 = k2->lchild;
            k2->lchild = k1->rchild;
            k1->rchild = k2;
            return k1;
        }
 
        // LL(Y rotates to the left)
        splay* LL_Rotate(splay* k2)
        {
            splay* k1 = k2->rchild;
            k2->rchild = k1->lchild;
            k1->lchild = k2;
            return k1;
        }
 
        // An implementation of top-down splay tree
        splay* Splay(int key, splay* root)
        {
            if (!root)
                return NULL;
            splay header;
            /* header.rchild points to L tree;
            header.lchild points to R Tree */
            header.lchild = header.rchild = NULL;
            splay* LeftTreeMax = &header;
            splay* RightTreeMin = &header;
            while (1)
            {
                if (key < root->key)
                {
                    if (!root->lchild)
                        break;
                    if (key < root->lchild->key)
                    {
                        root = RR_Rotate(root);
                        // only zig-zig mode need to rotate once,
                        if (!root->lchild)
                            break;
                    }
                    /* Link to R Tree */
                    RightTreeMin->lchild = root;
                    RightTreeMin = RightTreeMin->lchild;
                    root = root->lchild;
                    RightTreeMin->lchild = NULL;
                }
                else if (key > root->key)
                {
                    if (!root->rchild)
                        break;
                    if (key > root->rchild->key)
                    {
                        root = LL_Rotate(root);
                        // only zag-zag mode need to rotate once,
                        if (!root->rchild)
                            break;
                    }
                    /* Link to L Tree */
                    LeftTreeMax->rchild = root;
                    LeftTreeMax = LeftTreeMax->rchild;
                    root = root->rchild;
                    LeftTreeMax->rchild = NULL;
                }
                else
                    break;
            }
            /* assemble L Tree, Middle Tree and R tree */
            LeftTreeMax->rchild = root->lchild;
            RightTreeMin->lchild = root->rchild;
            root->lchild = header.rchild;
            root->rchild = header.lchild;
            return root;
        }
 
        splay* New_Node(int key)
        {
            splay* p_node = new splay;
            if (!p_node)
            {
                fprintf(stderr, "Out of memory!\n");
                exit(1);
            }
            p_node->key = key;
            p_node->lchild = p_node->rchild = NULL;
            return p_node;
        }
        
        void insertVector(std::vector<int> vec){
        	splay * root = NULL;
        	
        	    for(int i = 0; i < vec.size(); i++){
        			root = Insert(vec[i], root);
        			if(i%12==0){
        				InOrder(root);
						print2D(root);
        			}
        		}
        }
 
        splay* Insert(int key, splay* root)
        {
            static splay* p_node = NULL;
            if (!p_node)
                p_node = New_Node(key);
            else
                p_node->key = key;
            if (!root)
            {
                root = p_node;
                p_node = NULL;
                return root;
            }
            root = Splay(key, root);
            /* This is BST that, all keys <= root->key is in root->lchild, all keys >
            root->key is in root->rchild. */
            if (key < root->key)
            {
                p_node->lchild = root->lchild;
                p_node->rchild = root;
                root->lchild = NULL;
                root = p_node;
            }
            else if (key > root->key)
            {
                p_node->rchild = root->rchild;
                p_node->lchild = root;
                root->rchild = NULL;
                root = p_node;
            }
            else
                return root;
            p_node = NULL;
            return root;
        }
 
        splay* Delete(int key, splay* root)
        {
            splay* temp;
            if (!root)
                return NULL;
            root = Splay(key, root);
            if (key != root->key)
                return root;
            else
            {
                if (!root->lchild)
                {
                    temp = root;
                    root = root->rchild;
                }
                else
                {
                    temp = root;
                    /*Note: Since key == root->key,
                    so after Splay(key, root->lchild),
                    the tree we get will have no right child tree.*/
                    root = Splay(key, root->lchild);
                    root->rchild = temp->rchild;
                }
                free(temp);
                return root;
            }
        }
 
        splay* Search(int key, splay* root)
        {
            return Splay(key, root);
        }
 
        void InOrder(splay* root)
        {
            if (root)
            {
                InOrder(root->lchild);
                cout<< "key: " <<root->key;
                if(root->lchild)
                    cout<< " | left child: "<< root->lchild->key;
                if(root->rchild)
                    cout << " | right child: " << root->rchild->key;
                cout<< "\n";
                InOrder(root->rchild);
            }
        }
};
