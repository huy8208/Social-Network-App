/*
 * List.h
 *
 *  Created on: Mar 2, 2018
 *      Author: etabios
 */

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>         // for NULL
#include <assert.h>       // Halts program if preconditions are not met
#include <iostream>
//#include "User.h"

using namespace std;

template <class listdata> //list stores generic listdata, not any specific C++ type
class List {

private:
    struct Node {
        listdata data;  // Integer data within the node (Used to display Node usage)
        Node* next;     // Pointer containing the address of the next Node
        Node* prev;     // Pointer containing the address of the previous Node

        Node(listdata newData){ // Node Constructor
            data = newData;     // listdata data (Generic Data)
            next = NULL;        // Refers to next Node (Important to NULL here)
            prev = NULL;        // Refers to prev Node (Important to NULL here)
        }
    };
    Node* first;            // The List's reference to the "head" of the list
    Node* last;             // The List's reference to the "tail" of the last
    Node* iterator;         // Iterator used to traverse the List
    int length;             // Length of List


    /**Accessors*/
    bool isSorted(Node* node) const;
    //Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.

public:


    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: An instance of a List object is created

    List(const List &list);
    // Copy constructor: Deep copies an existing list
    // Postcondition: A deep copy of a list is created

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: Dynamic memory allocated to create this List object is released

    /**Accessors*/

    listdata getFirst() const;
    //Returns the first data in the list
    //Precondition: The list is not empty

    listdata getLast() const;
    //Returns the last data in the list
    //Precondition: The list is not empty

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    listdata getIterator() const;
    // Returns the element currently pointed at the iterator
    // Preconditions: Iterator != NULL

    bool offEnd() const;
    // Returns whether the iterator is off the end of the list (i.e. is NULL)
    // Postcondition: Returns true if iterator == NULL and false otherwise

    bool operator==(const List &list);
    // Tests two lists to determine whether their contents are equal
    // Postcondition: Returns true if lists are equal and false otherwise

    bool isSorted() const;
    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    /**Manipulation Procedures*/

    void removeFirst();
    //Removes the value stored in first node in the list
    //Precondition: The list is not empty
    //Postcondition: The value in the first node is now removed from the list

    void removeLast();
    //Removes the value stored in the last node in the list
    //Precondition: The list is not empty
    //Postcondition: The value in the last node is now removed from the list

    void insertFirst (listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: The new data is now in the front position of the list

    void insertLast(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: The new data is now in the last position of the list

    void startIterator();
    // Points the iterator at the beginning of the list
    // Postcondition: The iterator is pointing at the first data in the list

    void removeIterator();
    // Removes data in the list where the iterator is pointing
    // Precondition: Iterator != NULL
    // Postcondition: The data where the iterator was pointing is removed & Iterator == NULL

    void insertIterator(listdata data);
    // Inserts new data after the iterator
    // Precondition: iterator != NULL
    // Postcondition: A new node has been inserted after the iterator

    void advanceIterator();
    // Advances the iterator by one node in the list
    // Precondition: iterator != NULL
    // Postcondition: The iterator has moved by one position forward

    void reverseIterator();
    // Reverses the iterator by one node in the list
    // Precondition: iterator != NULL
    // Postcondition: The iterator has moved by one position in reverse

    void advanceToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size

    /**Additional List Operations*/

    List& operator=(const List &list);
    // Overload operator =

    void printList(ostream& out) const;
    //Takes ostream type and outputs the value of each data in the list sequentially

    void printNameNumberedList(ostream& out) const;
    // Print first and last name of Users in the list

    void printNumberedList() const;
    // Prints to contents of the linked list to the screen
    // in the format "#. <element>" followed by newline

    void printInterests(ostream& out) const;

    void printNamesAtInterests(ostream& out) const;
    // Prints Users from the Interests Table based on index


};

template <class listdata>
List<listdata>::List(){
    first = NULL;
    last = NULL;
    iterator = NULL;
    length = 0;
}

template<class listdata>
List<listdata>::List(const List &list){
	if(list.first == NULL){							// Edge Case: List is empty
		    first = last = iterator = NULL;
	}
	else{											// General Case: Everything Else
		first = new Node(list.first->data); 		// Calling Node constructor
		Node* temp = list.first;            		// Set a temporary node pointer to point at the first of the original list
		iterator = first;                   		// Set iterator to point to first node of the new list

		while(temp->next != NULL){
		    temp = temp->next;                      // Advance up to the next node in the original list
		    iterator->next = new Node(temp->data);  // Using node constructor to create new node with copy of data
		    iterator->next->prev = iterator;        // Connecting the new node's 'prev' to point back to where iterator is
		    iterator = iterator->next;              // Advance to this new node
		}
		last = iterator; 							// Iterator should be at the very last node of the list so 'last' points to where iterator is
		iterator = NULL; 							// Should not leave iterator anywhere unexpected
	}

	length = list.length;
}

template <class listdata>
List<listdata>::~List(){
     Node* b = first;
     Node* a = NULL;        // a stands for "after" (i.e. after b)
     while (b != NULL)
     {
        a = b->next;        // move a to node after b
        delete b;           // remove b (you know it is not NULL from if)
        b = a;              // b "catches up" with a (both point to same place in list)
     }
}

template <class listdata>
listdata List<listdata>::getFirst() const{
    assert(length != 0);   // Program halts execution if list is empty
    return first->data;
}

template <class listdata>
listdata List<listdata>::getLast() const{
    assert(length != 0);
    return last->data;
}

template <class listdata>
bool List<listdata>::isEmpty() const{
    return length == 0;
}

template <class listdata>
int List<listdata>::getLength() const{
    return length;
}

template <class listdata>
listdata List<listdata>::getIterator() const{
    assert(!offEnd());
    return iterator->data;
}

template <class listdata>
bool List<listdata>::offEnd() const{
    return iterator == NULL;
}

template <class listdata>
bool List<listdata>::operator ==(const List &list){
    if(length!=list.length)             // Check first if lists length are equal
        return false;
    Node* temp1 = first;                // Temporary iterator for left list
    Node* temp2 = list.first;           // Temporary iterator for right list

    while(temp1 != NULL)                // While loop cycling through both lists
    {                                   // Checking for matching data
        if(temp1->data != temp2->data)
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

template <class listdata>
bool List<listdata>::isSorted() const{
    if(length == 0 || length == 1)  // A list of 0 or 1 elements is considered sorted
        return true;
    else                            // Anything else call the recursive isSorted function
        return isSorted(last);
}

template <class listdata>
bool List<listdata>::isSorted(Node* node) const{

    if(node->prev == NULL)             // Base Case: Cycled through entire list with no faults
        return true;                   // Therefore list is sorted

    if(node->data < node->prev->data)  // Base Case: A number was found not be in the appropriate order
        return false;                  // Therefore list is not sorted

    return isSorted(node->prev);       // Recursive Step
}

template <class listdata>
int List<listdata>::getIndex() const{
    assert(iterator != NULL);          // Precondition: Iterator is not NULL || !offEnd()

    int index = 1;
    Node* temp = first;                // Temporary Iterator will search where Iterator is located
    while(temp != iterator){           // While loop will count the index spaces
        temp = temp->next;
        index++;
    }

    return index;
}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const{
    assert(length != 0);                // Precondition: List is not empty

    Node* temp = first;                 // Temporary Iterator

    for(int i = 0; i < length; i++){ 	// For loop through each node
        if(temp->data == data)          // Search for matching data
            return i+1;                 // Returns index location
        temp = temp->next;              // Traversing
    }

    return -1;                          // Return -1 when data not found
}

template <class listdata>
void List<listdata>::removeFirst()
{
    assert(length != 0);     // Precondition: List is empty

    if(iterator == first)    // Iterator should not point to deallocated memory
        iterator = NULL;

    if(length == 1)          // Edge Case 1: List has exactly one Node
    {                        // Important since 'first' and 'last' will need to point to NULL
        delete first;        // Node deallocated
        first = last = NULL; // 'first' and 'last' point adjusted to NULL
        length = 0;          // Length of list adjusted
    }
    else                     // General Case: List has more than one Node
    {
        Node* temp = first;  // Temporary Node is created to hold the Node to be removed
        first = first->next; // 'first' now points to the appropriate Node
        first->prev = NULL;  // The new first Node's 'prev' points to NULL
        delete temp;         // The Node to be removed is now deallocated
        length--;            // Length of list adjusted
    }
}

template <class listdata>
void List<listdata>::removeLast()
{
    assert(length != 0);     // Precondition: List is empty

    if(iterator == last)     // Iterator should not point to deallocated memory
        iterator = NULL;

    if(length == 1){         // Edge Case 1: List has exactly one Node
        delete last;
        first = last = NULL;
        length = 0;
    }
    else {                    // General Case: List has more than one Node
        Node* temp = first;
        temp = last->prev;    // temp is set to the second to last node of the list
        delete last;
        last = temp;          // Set last to be the former second to last node stored in temp
        last->next = NULL;    // Set pointer to point at NULL rather than deallocated memory
        length--;
    }

}

template <class listdata>
void List<listdata>::insertFirst(listdata data){

    Node* N = new Node(data);   // Create new Node
        if (length == 0)        // Edge Case 1: List is empty
        {
            first = last = N;   // first and last point to this new Node
        }
        else                    // General Case: List is not empty
        {
            N->next = first; 	// The new Node now points to the current first Node
            first->prev = N; 	// The current first Node's 'prev' points to the new Node
            first = N;          // The new Node is now the first Node
        }
        length++;               // Length of list adjusted
}

template <class listdata>
void List<listdata>::insertLast(listdata data){

    Node* N = new Node(data);       // Create new Node

    if(length == 0)                 // Edge Case 1: List is empty
    {
        first = last = N;           // 'first' and 'last' point to this new Node
    }
    else                            // General Case: List is empty
    {
        last->next = N;             // The current last Node points to the new Node
        N->prev = last;             // The new Node points back to the current last Node
        last = N;                   // The new Node is now the last Node
    }
    length++;                       // Length of list adjusted
}

template <class listdata>
void List<listdata>::startIterator(){
    iterator = first;
}

template <class listdata>
void List<listdata>::removeIterator(){

    assert(offEnd() == false);      // Precondition: Iterator != NULL

    if(iterator == first){          // Edge Case 1: Iterator at 'first'
        removeFirst();
    }
    else if (iterator == last){     // Edge Case 2: Iterator at 'last'
        removeLast();
    }
    else{                           // General Case: Everything else
        iterator->prev->next = iterator->next;
        iterator->next->prev = iterator->prev;
        delete iterator;
        iterator = NULL;
        length--;
    }

}

template <class listdata>
void List<listdata>::insertIterator(listdata data){

    assert(offEnd() == false); // Precondition: Iterator != NULL

    if(iterator == last)       // Edge Case 1: Iterator pointing to last Node
        insertLast(data);
    else                       // General Case: Everything Else
    {

    Node* N = new Node(data);  // Creating new Node

    N->next = iterator->next;  // New Node's 'next' points to the Node after Iterator
    N->prev = iterator;        // New Node's 'prev' points to the Iterator
    iterator->next = N;        // Iterator's 'next' correctly points to New Node
    N->next->prev = N;         // The Node after New Node has its 'prev' correctly pointed back

    length++;
    }

}

template <class listdata>
void List<listdata>::advanceIterator(){
    assert(iterator != NULL);   // Precondition: Iterator is not NULL
    iterator = iterator->next;
}

template <class listdata>
void List<listdata>::reverseIterator(){
    assert(iterator != NULL);   // Precondition: Iterator is not NULL
    iterator = iterator->prev;
}

template <class listdata>
void List<listdata>::advanceToIndex(int index){
    assert(length != 0);         	// Precondition: List is not empty
    assert(index <= length);     	// Precondition: The 'index' cannot be go beyond the list length
                                 	// Wasn't clarified if 0 was entered otherwise assert(index != 0);
    startIterator();

    for(int i = 1; i < index; i++)  // For loop to traverse iterator to indicated index
        advanceIterator();
}

template <class listdata>
List<listdata>& List<listdata>::operator=(const List& list){

	if(list.first == NULL){							// Edge Case: List is empty
	    first = last = iterator = NULL;
	}
	else{											// General Case: Everything Else
	    first = new Node(list.first->data); 		// Calling Node constructor
	    Node* temp = list.first;            		// Set a temporary node pointer to point at the first of the original list
	    iterator = first;                   		// Set iterator to point to first node of the new list

	    while(temp->next != NULL){
	        temp = temp->next;                      // Advance up to the next node in the original list
	        iterator->next = new Node(temp->data);  // Using node constructor to create new node with copy of data
	        iterator->next->prev = iterator;        // Connecting the new node's 'prev' to point back to where iterator is
	        iterator = iterator->next;              // Advance to this new node
	    }
	    last = iterator; 							// Iterator should be at the very last node of the list so 'last' points to where iterator is
	    iterator = NULL; 							// Should not leave iterator anywhere unexpected
	}

	length = list.length;

	return *this;
}

template <class listdata>
void List<listdata>::printList(ostream& out) const{
    Node* temp = first;
    while(temp != NULL){
        out << temp->data << endl;
        temp = temp->next;
    }
}

template <class listdata>
void List<listdata>::printNameNumberedList(ostream& out) const{
    Node* temp = first;
    int num = 1;
    while(temp != NULL){
        out << num++ << ". " << temp->data.getFirstName() << " " << temp->data.getLastName() << ", ";
        temp = temp->next;
    }
    out << endl;
}


template <class listdata>
void List<listdata>::printNumberedList() const{
    Node* temp = first;
    int num = 1;
    while(temp != NULL){
        cout << num << ". " << temp->data << endl;
        temp = temp->next;
        num++;
    }
    cout << endl;
}

template <class listdata>
void List<listdata>::printInterests(ostream& out) const{
	Node* temp = first;
	while(temp != NULL){
		if(temp == last)
			out << temp->data << " ";
		else
			out << temp->data << ", ";
		 temp = temp->next;
	}
	out << endl;
}

template <class listdata>
void List<listdata>::printNamesAtInterests(ostream& out) const{
	Node* temp = first;
	int num = 1;
	while(temp != NULL){
		out << num++ << ". " << temp->data.getFirstName() << " " << temp->data.getLastName() << endl;
		temp = temp->next;
	}
	out << endl;
}



#endif /* LIST_H_ */
