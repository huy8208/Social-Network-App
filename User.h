/*
 * User.h
 *
 *  Created on: Mar 2, 2018
 *      Author: etabios
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include <ostream>
#include "List.h"
#include "BST.h"
using namespace std;

class User{

private:
string firstName;
string lastName;
string userName;
string password;
string city;
string company;
int userID;
BST<User> friends;
List<string> interests;

public:
	// Constructor
	User();
	User(const User &u);
	User(string firstName,string lastName,string userName, string password, string city,string company);
	User& operator=(const User &u);
	~User(){}

	// Access Functions
	string getFirstName();
	string getLastName();
	string getUserName();
	string getPassword();
	string getCity();
	string getCompany();
	int getUserID();
	int getNumFriends();
	int getNumInterests();
	bool searchFriends(User u);
	List<User> getFriendsList();
	List<string> getInterests();

	// Manipulation Functions
	void setFirstName(string s);
	void setLastName(string s);
	void setUserName(string s);
	void setPassword(string s);
	void setCity(string s);
	void setCompany(string s);
	void setUserID(int id);
	void addFriend(User& u);
	void removeFriend(User& u);
	void addInterest(string i);
	void removeInterest(string i);

	// Additional Operations
	friend ostream& operator<<(ostream& out,const User& u);
	bool operator==(const User& u);	// For BST Comparison
	bool operator<(const User& u);	// For BST Comparison
	bool operator>(const User& u);	// For BST Comparison
	void printFriendsList(ostream& out);
	void printFriends(ostream& out);
	void printInterests(ostream& out);
	void printUser(ostream& out);



};



#endif /* USER_H_ */
