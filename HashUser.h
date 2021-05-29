/*
 * HashUser.h
 *
 *  Created on: Mar 4, 2018
 *      Author: EJ
 */

#ifndef HASHUSER_H_
#define HASHUSER_H_

#include <string>
#include <cstdlib>
#include "List.h"
#include "User.h"
using namespace std;

class HashUser {
public:
    /**Constructors*/

	HashUser(){}
    //constructor

    ~HashUser(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;	// PROJECT: Hash Function using NAMES as the key
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table
    //Key for this table: firstName + lastName

    int countBucket(int index) const;	// PROJECT: Doesn't seem necessary for project
    //counts the number of Users at this index
    //returns the count
    //pre: 0<= index < SIZE

    int search(User u) const;	// PROJECT: If the user exist -> Prompt User to Add Friend
    //Searches for u in the table
    //returns the index at which u is located
    //returns -1 if u is not in the table

    void searchByFirstName(string s);

    User getUser(string name);

    /**Manipulation Procedures*/

    void insert(User u);	// PROJECT: Necessary for loading Users from our input text file
    //inserts a new book into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(User u);	// PROJECT: Doesn't seem necessary for project
    //removes u from the table
    //calls the hash function on the key to determine
    //the correct bucket
    //pre: u is in the table

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;	// PROJECT: Only use should be for debugging
    //Prints all the Users at index
    //pre: 0<= index < SIZE


    void printTable(ostream& out) const;	// PROJECT: Only use should be for debugging
    // Print the first User at each index

    void printUserAtIndex(ostream& out, User u, int index);

private:
    static const int SIZE = 30;	// PROJECT: Our total data of Users is 15 -> SIZE = 2(15)
    List<User> Table[SIZE];		// PROJECT: Our array of Lists that contain User objects
};



#endif /* HASHUSER_H_ */
