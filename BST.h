/*
 * BST.h
 *
 *  Created on: Mar 2, 2018
 *      Author: etabios
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <assert.h>
#include <algorithm>
//#include "User.h"
#include "List.h"

using namespace std;
template<typename bstdata>
class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata){
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    /**Private helper functions*/
    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a value into the BST

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void inOrderFriendNamesPrint(ostream& out, Node* root) const;
    //private helper function for inOrderFriendNamesPrint
    //recursively prints tree values in order from smallest to largest alphabetical

    void numberedFriendListPrint(ostream&out, Node* root, int &num) const;

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the value is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum value in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

    void viewAtIndex(Node* root,int &index,int num);

    void getFriendList(Node* root, List<bstdata> &list);
    // Helper function to get list of friends


public:

    /**constructors and destructor*/

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    //https://stackoverflow.com/questions/1734628/copy-constructor-and-operator-overload-in-c-is-a-common-function-possible
    BST& operator=(const BST& bst);

    /**access functions*/

    bstdata minimum() const;
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum value in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the value stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()

    void getFriendList(List<bstdata> &list);
    // Copies the User's friends data from BST<User> into the List

    /**manipulation procedures*/

    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified value from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()

    /**additional functions*/

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void inOrderFriendNamesPrint(ostream& out) const;
    //calls the inOrderPrint function to print out names of the Users
    //stored in the BST

    void numberedFriendListPrint(ostream&out) const;

    void viewAtIndex(int num);


};

template <class bstdata>
BST<bstdata>::BST(){
    root = NULL;
}

template <class bstdata>
BST<bstdata>::BST(const BST &bst){
    // Copy Constructor inserts node in <root><left><right> order (preOrder)

    if(bst.root == NULL)
        root = NULL;
    else{
        //root = new Node(bst.root->data);
        root = NULL;                // Minor but avoids inserting root twice opposed to first line
        copyNode(bst.root);
    }

}

template <class bstdata>
void BST<bstdata>::copyNode(Node* copy){

    if(copy != NULL){
        insert(copy->data);
        copyNode(copy->left);
        copyNode(copy->right);
    }
}

template <class bstdata>
BST<bstdata>::~BST(){
    // Destructor deletes in <left><right><root> order (postOrder)

    if(root != NULL){
        freeNode(root);
        delete root;
        root = NULL;
    }
}

template <class bstdata>
void BST<bstdata>::freeNode(Node* root){
    if(root->left != NULL){
        freeNode(root->left);
        delete root->left;
        root->left = NULL;
    }

    if(root->right != NULL){
        freeNode(root->right);
        delete root->right;
        root->right = NULL;
    }
}

template <class bstdata>
BST<bstdata>& BST<bstdata>::operator=(const BST& bst){

	if(bst.root == NULL)
		root = NULL;
	else{
		root = NULL;
		copyNode(bst.root);
	}

	return *this;
}

template <class bstdata>
bstdata BST<bstdata>::minimum() const{
    assert(!isEmpty());                 // Precondition: BST is not empty || root != NULL
    return minimum(root);
}
template <class bstdata>
bstdata BST<bstdata>::minimum(Node* root) const{
    if(root->left != NULL)               // Recursive Step: Root has a left node
        return minimum(root->left);
    else                                // Base Case: Root's left is NULL
        return root->data;
}

template <class bstdata>
bstdata BST<bstdata>::maximum() const{
    assert(!isEmpty());                 // Precondition: BST is not empty || root != NULL
    return maximum(root);
}

template <class bstdata>
bstdata BST<bstdata>::maximum(Node* root) const{
    if(root->right != NULL)              // Recursive Step: Root has a right node
        return maximum(root->right);
    else                                // Base Case: Root's right is NULL
        return root->data;
}

template <class bstdata>
bool BST<bstdata>::isEmpty() const{
    return root == NULL;
}

template <class bstdata>
int BST<bstdata>::getSize() const{
    int size = 0;
    getSize(root,size);     // Size is passed by reference
    return size;
}

template <class bstdata>
void BST<bstdata>::getSize(Node* root, int& size) const{
    if(root != NULL){
        size++;
        getSize(root->left,size);
        getSize(root->right,size);
    }
}

template <class bstdata>
bstdata BST<bstdata>::getRoot() const{
    assert(root != NULL);               // Precondition: BST is not empty || !isEmpty()
    return root->data;
}

template <class bstdata>
int BST<bstdata>::getHeight() const{
    return getHeight(root);
}

template <class bstdata>
int BST<bstdata>::getHeight(Node* root) const{
    if(root == NULL)    // Base Case: Root is NULL - NULL has a height of -1
        return -1;

    return max(getHeight(root->left),getHeight(root->right)) + 1;  // Recursive Step: Counting Edges - For each edge +1
}


template <class bstdata>
bool BST<bstdata>::search(bstdata data) const{
    assert(root != NULL);               // Precondition: BST is not empty || !isEmpty()
    if(data == root->data)
        return true;
    else
        return searchNode(root,data);
}

template <class bstdata>
bool BST<bstdata>::searchNode(Node* root, bstdata data) const{
    if(data == root->data)                       // Base Case: Data Match
        return true;
    if(data < root->data){                       // Data less than root data, search left subtree
        if(root->left == NULL)
            return false;                        // NULL indicates no more nodes to check. Return false
        else
            return searchNode(root->left,data);  // Recursive Step: Pass root's left node with data
    }
    else{                                        // Data greater than root data, search right subtree
        if(root->right == NULL)
            return false;                        // NULL indicates no more nodes to check. Return false
        else
            return searchNode(root->right,data); // Recursive Step: Pass root's right node with data
    }

    return false;
}

template <class bstdata>
void BST<bstdata>::insert(bstdata data){
    if (root == NULL)
    {
        root = new Node(data);  //if the tree is empty insert the value at the root
    }
    else
    {
        insertNode(root, data); //otherwise call the helper function, passing it the root
    }
}

template <class bstdata>
void BST<bstdata>::insertNode(Node* root, bstdata data){

    if(data == root->data){					// Base Case: No Duplicates in Binary Search Tree
    	root->data = data;
        return;
    }
    if(data < root->data){                  // Data is less than root data, Traverse left subtree
        if(root->left == NULL)
            root->left = new Node(data);	// If left node is NULL, insert data here
        else
            insertNode(root->left,data);	// Recursive Step: Pass in root's left node
    }
    else{									// Data is greater than root data, Traverse right subtree
        if(root->right == NULL)
            root->right = new Node(data);	// If right node is NULL, insert data here
        else
            insertNode(root->right,data);	// Recursive Step: Pass in root's right node
    }

}

template <class bstdata>
void BST<bstdata>::remove(bstdata data){
    assert(search(data));           // Precondition: Data is located in BST
    assert(!isEmpty());             // Precondition: BST is not empty

    root = removeNode(root,data);
}

template <class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data)
{
    if(root == NULL){                                   // First 3 set of statements locate the Node
        return root;
    }
    else if(data < root->data){
        root->left = removeNode(root->left,data);
    }
    else if(data > root->data){
        root->right = removeNode(root->right,data);
    }
    else{
        if(root->right == NULL && root->left == NULL){  // Case 1: 0 Children
            delete root;                                // Root can simply be deleted since no important connections
            root = NULL;                                // Important to NULL - Returning root should be NULL
        }
        else if(root->right == NULL){                   // Case 2: 1 Children (Left Child)
            Node* temp = root;                          // Temporary pointer at the node to be deleted
            root = root->left;                          // root->left is shifted to where root is
            delete temp;                                // The node to be removed is now deleted
        }
        else if(root->left == NULL){                 	// Case 2: 1 Children (Right Child)
            Node* temp = root;                          // Temporary pointer at the node to be deleted
            root = root->right;                         // root->right is shifted to where root is
            delete temp;                                // The node to be removed is now deleted
        }
        else{                                           // Case 3: 2 Children (Minimum of Right Subtree)
            bstdata min = minimum(root->right);         // Find the minimum of the right subtree
            root->data = min;                           // Replace the root data with the right subtree's minimum
            root->right = removeNode(root->right,min);  // Find the original node with that minimum and delete (No Duplicates)

            //bstdata max = maximum(root->left);     	// Case 3: 2 Children (Maximum of Left Subtree) - Alternate Solution
            //root->data = max;
            //root->left = removeNode(root->left,max);
        }
    }

    return root;
}

template <class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const{
    if(root != NULL)
        inOrderPrint(out,root);
    out << endl;
}

template <class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out,Node* root) const{
    if(root != NULL){
        inOrderPrint(out,root->left);
        out << root->data << endl;
        inOrderPrint(out,root->right);
    }
}

template <class bstdata>
void BST<bstdata>::inOrderFriendNamesPrint(ostream& out) const{
	if(root != NULL)
		inOrderFriendNamesPrint(out,root);
	out << endl;
}

template <class bstdata>
void BST<bstdata>::inOrderFriendNamesPrint(ostream& out,Node* root) const{

    if(root != NULL){
    	inOrderFriendNamesPrint(out,root->left);
        out << root->data.getFirstName() << " " << root->data.getLastName() << ", ";
        inOrderFriendNamesPrint(out,root->right);
    }
}

template <class bstdata>
void BST<bstdata>::numberedFriendListPrint(ostream& out) const{
	int num = 1;
	if(root != NULL)
		numberedFriendListPrint(out,root,num);
	out << endl;
}

template <class bstdata>
void BST<bstdata>::numberedFriendListPrint(ostream& out,Node* root,int &num) const{

    if(root != NULL){
    	numberedFriendListPrint(out,root->left,num);
        out << num++ << ". " << root->data.getFirstName() << " " << root->data.getLastName() << endl;
        numberedFriendListPrint(out,root->right,num);
    }
}

template <class bstdata>
void BST<bstdata>::viewAtIndex(int num){
	int index = 1;
	if(root != NULL)
		viewAtIndex(root,index,num);
}

template <class bstdata>
void BST<bstdata>::viewAtIndex(Node* root,int &index,int num){

    if(root != NULL){
    	viewAtIndex(root->left,index,num);
    	if(num == index){
    		//remove(root->data);
    		root->data.printUser(cout);
    		index = 0;
    		return;
    	}else if(index == 0)
    		return;
    	index++;
    	viewAtIndex(root->right,index,num);
    }
}

template <class bstdata>
void BST<bstdata>::getFriendList(List<bstdata> &list){
	if(root != NULL)
		getFriendList(root,list);
}

template <class bstdata>
void BST<bstdata>::getFriendList(Node* root, List<bstdata> &list){
	if(root != NULL){
		getFriendList(root->left,list);
		list.insertLast(root->data);
		getFriendList(root->right,list);
	}
}


#endif /* BST_H_ */
