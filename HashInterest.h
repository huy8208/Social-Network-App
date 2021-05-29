/*
 * HashInterest.h
 *
 *  Created on: Mar 4, 2018
 *      Author: EJ
 */

#ifndef HASHINTEREST_H_
#define HASHINTEREST_H_

#include <string>
#include "List.h"
#include "User.h"
using namespace std;

class HashInterest {
public:
    /**Constructors*/

	HashInterest(){}
    //constructor

    ~HashInterest(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;
    // Hash Function using INTEREST as the key
    // Returns the hash value for the given key
    // The hash value is the sum of the ASCII values of each char in the key % the size the of the table

    int countBucket(int index) const;
    // Counts the number of Users at this index and returns th count
    // pre: 0<= index < SIZE

    int checkInterest (string interest) const;
    // Essentially searching for the interest
    // Return index of interest location otherwise return -1

    bool checkUserWithInterest(string name, string interest);
    // Returns true if the input name of a User has the input interest otherwise return false

    /**Manipulation Procedures*/

    void insertInterest(User u);
    // Extract interests from User and insert into Table[].
    // Inserts unique interests (No duplicates) into the parallel table
    // Calls the hash function on the key to determine the correct bucket

    void removeInterest(string interest);
    // Remove interest and also all the users under that particular interest.

    void removeUser(string Interest, User U);
    // Remove User based on a particular interest.

    /**Additional Functions*/


    void printBucket(ostream& out, int index) const;
    // Prints all User's names at an index of the Interest Table in a numbered list
    // pre: 0<= index < SIZE

    void printSpecialBucket(ostream& out, int index, User u);
    // Special print function for the Menu interface

    void printTable(ostream& out) const;
    // Prints all the data in the HashInterests tables
    

    
    
private:
    static const int SIZE = 60;	// SIZE is a little more than twice the size of our data. Also to accommodate linear probing
    List<User> Table[SIZE];		// Table that contains a list of Users that are mapped by their interests
    string parallelTable[SIZE]; // Parallel Table to store interests at a unique index number with the help of linear probing
};


#endif /* HASHINTEREST_H_ */
