/*
 * HashLogin.h
 *
 *  Created on: Mar 6, 2018
 *      Author: etabios
 */

#ifndef HASHLOGIN_H_
#define HASHLOGIN_H_

#include "List.h"
#include "User.h"
#include <string>
using namespace std;

class HashLogin{

public:
    /**Constructors*/
	HashLogin(){}
    ~HashLogin(){}


    /**Access Functions*/

    bool loginCheck(string login,string pass);
    // Checks if login and password correctly match a User
    // Returns true if login information is valid otherwise false

    int hash(string key) const;
    // Hash Function using 'username + password' as the key
    // Returns the hash value for the given key
    // The hash value is the sum of the ASCII values of each char in the key
    // each char in the key % the size the of the table

    int countBucket(int index) const;
    // Counts the number of Users at this index
    // Returns the count
    // Pre: 0<= index < SIZE

    int search(User u) const;
    // Searches for User in the table
    // Returns the bucket index at which User is located
    // Returns -1 if User is not in the table

    User getUser(string login, string pass);
    // Returns a User corresponding with the login and password

    /**Manipulation Procedures*/

    void insert(User u);
    // Inserts a new User into the table
    // Calls the hash function on the key to determine the correct bucket

    void remove(User u);
    // Removes User from the table
    // Calls the hash function on the key to determine the correct bucket
    // Pre: User is in the table

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;
    // PROJECT: Format should print a numbered list of Users
    // Prints all the interest at index
    // Pre: 0<= index < SIZE

    void printTable(ostream& out) const;
    // PROJECT: Only use should be for debugging
    //Prints the first User at each index

private:
    static const int SIZE = 30;
    List<User> Table[SIZE];

};



#endif /* HASHLOGIN_H_ */
