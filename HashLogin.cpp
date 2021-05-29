/*
 * HashLogin.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: EJ
 */

#include "HashLogin.h"
#include "User.h"
#include "List.h"
#include <iostream>
#include <assert.h>

bool HashLogin::loginCheck(string login,string pass){
	User temp;
	int index = hash(login + pass);

	if(!Table[index].isEmpty()){
		Table[index].startIterator();
		for(int i = 0; i < Table[index].getLength(); i++){
			temp = Table[index].getIterator();
			if(temp.getUserName() == login && temp.getPassword() == pass)
				return true;
			Table[index].advanceIterator();
		}
	}

	return false;
}

int HashLogin::hash(string key) const{	// Hash key based on userName + password
    int index, sum = 0;
    for(int i = 0; i < (int)key.length(); i++)
        sum += (int) key[i];    // Summing the ASCII values for each character in the string
    index = sum % SIZE;         // Dividing the summed ASCII values by SIZE && storing remainder as my index
    return index;
}

int HashLogin::countBucket(int index) const{
    assert(0 <= index && index < SIZE);     // Precondition: Index is not out of bounds

    return Table[index].getLength();        // Returning the row length of the Table at an index
}

int HashLogin::search(User u) const{
    int index = hash(u.getUserName() + u.getPassword());	// Input into hash function to get an index

    if(Table[index].isEmpty())				// If the Table[index] is empty return -1
        return -1;							// Otherwise List.h linearSearch() assertion applies

    return Table[index].linearSearch(u);	// Returns bucket location
}

User HashLogin::getUser(string login,string pass){

	int index = hash(login + pass);
	User temp;

	if(!Table[index].isEmpty()){
		Table[index].startIterator();
		for(int i = 0; i < Table[index].getLength(); i++){
			temp = Table[index].getIterator();
			if(temp.getUserName() == login && temp.getPassword() == pass){
				return Table[index].getIterator();
			}
			Table[index].advanceIterator();
		}
	}

	return temp;
}

void HashLogin::insert(User u){
    int index = hash(u.getUserName() + u.getPassword());   // Input into hash function to get an index

    Table[index].insertLast(u);     // A preoccupied index assures that the next object to be inserted is at the end of the list
}

void HashLogin::remove(User u){
    assert(search(u) != -1);    // Precondition: The User is in the Table

    int index = hash(u.getUserName() + u.getPassword());   // Input into hash function to get an index

    Table[index].advanceToIndex(search(u)); // Advanced to the bucket location of the Book
    Table[index].removeIterator();          // Remove User from the List
}

void HashLogin::printBucket(ostream& out, int index) const{
    assert(0 <= index && index < SIZE); // Precondition: Index is not out of bounds

    Table[index].printList(out);        // Prints the entire 'row' of Users of the Table
}

void HashLogin::printTable(ostream& out) const{
    for(int index = 0; index < SIZE; index++){       // Loop to print a User at each Table[index] if applicable
        if(!Table[index].isEmpty()){
            out << "Group " << index + 1 << endl;
            out << Table[index].getFirst() << endl;
            out << "+" << countBucket(index) - 1 << " more User(s)" << endl << endl;
        }
    }
}


