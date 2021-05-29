/*
 * User.cpp
 *
 */

#include "User.h"
#include <iostream>
#include <iomanip>

User::User():firstName(""),lastName(""),userName(""),password(""),city(""),company(""),userID(0){}

User::User(const User &u){
	firstName = u.firstName;
	lastName = u.lastName;
	userName = u.userName;
	password = u.password;
	city = u.city;
	company = u.company;
	userID = u.userID;

	friends = u.friends;
	interests = u.interests;
}

User::User(string fn,string ln,string u, string p, string c,string cn){
	firstName = fn;
	lastName = ln;
	userName = u;
	password = p;
	city = c;
	company = cn;
	userID = 0;
}

User& User::operator=(const User &u){

	firstName = u.firstName;
	lastName = u.lastName;
	userName = u.userName;
	password = u.password;
	city = u.city;
	company = u.company;
	userID = u.userID;

	friends = u.friends;
	interests = u.interests;

	return *this;
}

// Access Functions
string User::getFirstName(){
	return firstName;
}

string User::getLastName(){
	return lastName;
}

string User::getUserName(){
	return userName;
}

string User::getPassword(){
	return password;
}

string User::getCity(){
	return city;
}

string User::getCompany(){
	return company;
}

int User::getUserID(){
	return userID;
}

int User::getNumFriends(){
	return friends.getSize();
}

int User::getNumInterests(){
	return interests.getLength();
}

bool User::searchFriends(User u){
	return friends.search(u);
}

List<User> User::getFriendsList(){
	List<User> temp;
	friends.getFriendList(temp);

	return temp;
}

List<string> User::getInterests(){
	return interests;
}

// Manipulation Functions

void User::setFirstName(string s){
	firstName = s;
}

void User::setLastName(string s){
	lastName = s;
}

void User::setUserName(string s){
	userName = s;
}

void User::setPassword(string s){
	password = s;
}

void User::setCity(string s){
	city = s;
}
void User::setCompany(string s){
	company = s;
}

void User::setUserID(int id){
	userID = id;
}

void User::addFriend(User &u){
	friends.insert(u);
}
void User::removeFriend(User &u){
	friends.remove(u);
}
void User::addInterest(string i){
	interests.insertLast(i);
}
void User::removeInterest(string i){
	int index = interests.linearSearch(i);
	if(index != -1){
		interests.advanceToIndex(index);
		interests.removeIterator();
		cout << "You have removed \"" << i << "\" as an interest" << endl;
	}else{
		cout << "Unable to remove \"" << i << "\" as an interest" << endl;
	}
}

// Additional Operations
ostream& operator<<(ostream& out,const User& u){
	out << "First name: " << u.firstName << endl;
	out	<< "Last name: " << u.lastName << endl;
	out << "Login: " << u.userName << endl;
	out << "Password: " << u.password << endl;
	out << "Company: " << u.company << endl;
	out << "City: " << u.city << endl;
	out << "User ID: " << u.userID << endl;
	out << "Friends: ";
	u.friends.inOrderFriendNamesPrint(out);
	out << "Interests: ";
	u.interests.printInterests(out);
	return out;
}

bool User::operator==(const User& u){
	return (firstName == u.firstName && lastName == u.lastName);
}
bool User::operator<(const User& u){
	if(firstName == u.firstName && lastName == u.lastName)
		return false;

	if(firstName == u.firstName)
		return lastName < u.lastName;

	return firstName < u.firstName;

}

bool User::operator>(const User& u){
	if(firstName == u.firstName && lastName == u.lastName)
		return false;

	if(firstName == u.firstName)
		return lastName > u.lastName;

	return firstName > u.firstName;
}

void User::printFriendsList(ostream& out){
	friends.numberedFriendListPrint(out);
}

void User::printFriends(ostream& out){
	friends.inOrderFriendNamesPrint(out);
}

void User::printInterests(ostream& out){
	interests.printInterests(out);
}

void User::printUser(ostream& out){
	out << "Name: " << firstName << " " << lastName << endl;
	out << "City: " << city << endl;
	out << "Company: " << company << endl;
	out << "Friends: ";
	friends.inOrderFriendNamesPrint(out);
	out << "Interests: ";
	interests.printInterests(out);
}
