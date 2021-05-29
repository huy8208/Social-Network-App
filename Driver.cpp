/* Project Team 5: Elmer Tabios, Duc Huy Nguyen, Trevor Hansen,
 * 				   Gia Trinh, Octvaio Cruz, Ninh Nguyen
 * Driver.cpp
 *
 * Description: Main function of our program responsible for presenting a user interface
 * 				while creating Data Structure and FileIO objects and how they will be handled
 * 				when a user interacts with the program.
 */

#include <iostream>
#include "BST.h"			// Binary Search Tree
#include "List.h"			// Linked List
#include "Graph.h"			// Graph
#include "HashUser.h"		// Hash containing Users indexed by
#include "HashInterest.h"	// Hash containing Interests
#include "HashLogin.h"		// Hash containing Users indexed by login+pass (no space)
#include "FileIO.h"			// Handles File Input & Output
#include "User.h"			// Our Abstract Data

using namespace std;

void debugDataStructures(BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin, HashInterest &hashInterests){

	cout << "--------------- DEBUG - End of Program Status ---------------\n\n\n";
	cout << "------------------ userBST --------------------" << endl;
	userBST.inOrderPrint(cout);

	cout << "------------------ hashLogin ------------------" << endl;
	hashLogin.printTable(cout);

	cout << "------------------ hashUsers ------------------" << endl;
	hashUsers.printTable(cout);

	cout << "----------------- hashInterests ---------------" << endl;
	hashInterests.printTable(cout);

	cout << endl << endl;
}

void formatString(string &f, string &l){
	f[0] = toupper(f[0]);
	l[0] = toupper(l[0]);

	for(int i = 1; i < (int)f.length(); i++)
		f[i] = tolower(f[i]);

	for(int j = 1; j < (int)l.length(); j++)
		l[j] = tolower(l[j]);
}

void singleFormatString(string &s){
	if(int(s.length()) > 0){
		s[0] = toupper(s[0]);

		for(int i = 1; i < (int)s.length(); i++){
			if(s[i-1] == ' ')
				s[i] = toupper(s[i]);
			else
				s[i] = tolower(s[i]);
		}
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
	}
}

// Menu Interface: Login Screen -> Home Screen -> Logout
void logoutScreen(){
	string input;
	cout << "--------------- Logout Screen --------------\n\n";
	cout << "You have successfully logged out\n\n";
	cout << "Thank you for using our program!\n\n";
	cout << "Enter any key to return to login screen: ";
	cin >> input;
	cin.ignore();
	cout << "\n\n--------------------------------------------\n\n\n";

}

// Unique Function: Updates all Data Structures when a User adds a friend
void userAddFriend(User &sourceUser, User temp, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin){
	// In sourceUser's friends list, remove User temp
	// Get User Temp from hashUsers, remove source from Temp's friend list
	sourceUser.addFriend(temp);
	temp.addFriend(sourceUser);

	// insert source and temp into BST // insert is modified to swap data
	// insert source and temp into HashUser // you need to remove each first then insert both
	userBST.insert(sourceUser);
	userBST.insert(temp);

	hashUsers.remove(sourceUser);
	hashUsers.remove(temp);
	hashUsers.insert(sourceUser);
	hashUsers.insert(temp);

	hashLogin.remove(sourceUser);
	hashLogin.remove(temp);
	hashLogin.insert(sourceUser);
	hashLogin.insert(temp);

}

// Unique Function - Updates all Data Structures when a User removes a friend
void userRemoveFriend(User &sourceUser, User temp, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin){
	// In sourceUser's friend list, remove temp
	// Get User Temp from hashUsers, remove sourceUser from Temp's friend list
	sourceUser.removeFriend(temp);
	temp.removeFriend(sourceUser);

	// Insert updated sourceUser and temp into BST // Insert is modified to swap data
	// Insert updated sourceUser and temp into HashUser // You need to remove each first, then insert both
	// Insert updated sourceUser and temp into HashLogin // You need to remove each first, then insert both
	userBST.insert(sourceUser);
	userBST.insert(temp);

	hashUsers.remove(sourceUser);
	hashUsers.remove(temp);
	hashUsers.insert(sourceUser);
	hashUsers.insert(temp);

	hashLogin.remove(sourceUser);
	hashLogin.remove(temp);
	hashLogin.insert(sourceUser);
	hashLogin.insert(temp);

}

// Menu Interface: Login Screen -> Home Screen -> Search For New Friends -> Search By Interest
void searchByInterest(User &source, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin, HashInterest &hashInterests){
	int index;
	string interest,fInterest,i,name;
	User temp;
	while(true){
		cout << "------------- Search By Interest -----------\n\n\n";
		cout << "Find people with a common interest\n\n";

		cout << "Enter an interest to get started: ";
		getline(cin, interest);
		cout << endl;
		fInterest = interest;
		singleFormatString(fInterest);
		index = hashInterests.checkInterest(fInterest);
		formatString(interest,fInterest);

		if(index != -1){

			cout << "Search Results for (" << interest  << "): \n";
			hashInterests.printSpecialBucket(cout,index,source);
			cout << "Do you want to add any of these users? (Y/N): ";
			getline(cin,i);
			cout << endl;

			while(i == "Y" || i == "y"){
				cout << "Enter the name of the user you want to add from the list: ";
				getline(cin,name);
				singleFormatString(name);
				cout << endl;
				temp = hashUsers.getUser(name);
				if(name == source.getFirstName()+source.getLastName()){
					cout << "ERROR: You can't add yourself!\n";
					cout << "Do you want to to add a user from the list?(Y/N): ";
					cin >> i;
					cin.ignore(10000,'\n');
					if(i != "Y" || i != "y")
					break;
					cout << "Search Results: \n";
					hashInterests.printSpecialBucket(cout,index,source);

				}else if(hashInterests.checkUserWithInterest(name,fInterest) && source.searchFriends(temp) == false){
					//temp = hashUsers.getUser(name);
					userAddFriend(source,temp,userBST,hashUsers,hashLogin);
					cout << "You are now friends with " << temp.getFirstName() << " " << temp.getLastName() << "!\n\n";
					break;

				}else{
					if(source.searchFriends(temp) == true)
						cout << "ERROR: You are already friends with " << temp.getFirstName() << " " << temp.getLastName() << "!\n";
					else
						cout << "ERROR: Please enter a valid name from the list\n";
					cout << "Do you want to to add a user from the list?(Y/N): ";
					cin >> i;
					cin.ignore(10000,'\n');
					cout << endl;
					if(i != "Y" && i != "y")
						break;
					cout << "Search Results for (" << interest  << "): \n";
					hashInterests.printSpecialBucket(cout,index,source);
				}
			}

		}else{
			cout << "No results for \"" << interest << "\" \n\n";
		}


		cout << "Enter any key to return to 'Search For New Friends': ";
		cin >> i;
		cout << "\n\n--------------------------------------------\n\n\n";
		return;


	}
}

// Menu Interface: Login Screen -> Home Screen -> Search For New Friends -> Search By Name
void searchByName(User &source, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin){
	int input;
	bool error = false;
	string errorType,firstName,lastName,i;
	User temp;

	while(true){
		cout << "--------------- Search By Name -------------\n\n\n";
		cout << "Who are you searching for?\n\n";
		cout << "Options: \n";
		cout << "1. Enter a name\n";
		cout << "2. Back (Return to 'Search For New Friends')\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-2): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
			cin.ignore(10000,'\n');
			error = true;
			errorType = "ERROR: Please enter numbers not letters";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input < 1 || 2 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 2";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input == 1){
			error = false;
			cout << "Enter the User's first and last name: ";
			cin >> firstName >> lastName;
			cin.ignore(10000,'\n');
			cout << endl;

			formatString(firstName,lastName);
			temp.setFirstName(firstName);
			temp.setLastName(lastName);


			if(hashUsers.search(temp) != -1 && source.searchFriends(temp) == false){
				temp = hashUsers.getUser(firstName+lastName);
				cout << "We found " << firstName << " " << lastName << endl << endl;
				cout << "Related Results: " << endl;
				hashUsers.searchByFirstName(firstName);
				cout << "Would you like to add " << firstName << " " << lastName << "? (Y/N): ";
				cin >> i;
				cin.ignore(10000,'\n');
				if(i == "Y" || i == "y"){
					userAddFriend(source,temp,userBST,hashUsers,hashLogin);
					cout << "You are now friends with " << firstName << " " << lastName << "!\n\n";
					cout << "Enter any key to return to 'Search By Name': ";
					cin >> i;
					cin.ignore(10000,'\n');
				}else{
					cout << "You did not add " << firstName << " " << lastName << ".\n";
					cout << "Enter any key to return to 'Search By Name': ";
					cin >> i;
					cin.ignore(10000,'\n');
				}

			}else if(source.searchFriends(temp) == true){
				cout << "ERROR: You are already friends with " << firstName << " " << lastName << endl;
				cout << "Enter any key to return to 'Search By Name': ";
				cin >> i;
				cin.ignore(10000,'\n');
				cout << "\n--------------------------------------------\n\n\n";
			}else{
				cout << "ERROR: Sorry, unable to find \"" << firstName << " " << lastName << "\"\n";
				cout << "Enter any key to return to 'Search By Name': ";
				cin >>i;
				cin.ignore(10000,'\n');
				cout << "\n--------------------------------------------\n\n\n";
			}
			cout << "\n\n--------------------------------------------\n\n\n";

		}else if(input == 2){
			cout << "\n\n--------------------------------------------\n\n\n";
			return;
		}
	}

}

// Menu Interface: Login Screen -> Home Screen -> Search For New Friends
void searchForNewFriends(User &source, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin, HashInterest &hashInterests){
	int input;
	bool error = false;
	string errorType;

	while(true){
		cout << "----------- Search For New Friends ---------\n\n\n";
		cout << "Meet someone new!\n\n";
		cout << "Options: \n";
		cout << "1. Search by Name\n";
		cout << "2. Search by Interest\n";
		cout << "3. Back (Return to Home Screen)\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-3): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
			cin.ignore(10000,'\n');
			error = true;
			errorType = "ERROR: Please enter numbers not letters";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input < 1 || 3 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 3";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else{
			cout << "\n\n--------------------------------------------\n\n\n";
			error = false;
			switch(input){
					// Search by Name
			case 1: searchByName(source,userBST,hashUsers,hashLogin);
					break;
					// Search by Name
			case 2: searchByInterest(source,userBST,hashUsers,hashLogin,hashInterests);
					break;
			case 3: return;
					break;
			default: cout << "Driver.cpp: searchForNewFriends() error\n";
					 break;
			}
		}
	}
}

// Menu Interface: Login Screen -> Home Screen -> View My Friends -> Remove A Friend
void removeFriend(User &source, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin){
	int input;
	bool error = false;
	string errorType,firstName,lastName,i;
	User temp;
	while(true){
		cout << "--------------- Remove Friend -------------\n\n\n";
		cout << "Someone weighing you down?\n\n";
		cout << "Options: \n";
		cout << "1. Enter a name\n";
		cout << "2. Back (Return to View My Friends)\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-2): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
			cin.ignore(10000,'\n');
			error = true;
			errorType = "ERROR: Please enter numbers not letters";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input < 1 || 3 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 2";
			cout << "\n\n--------------------------------------------\n\n\n";
		}

		if(input == 1){
			cout << "Enter the User's first name and last name: ";
			cin >> firstName >> lastName;
			cin.ignore(10000,'\n');
			cout << endl;

			formatString(firstName,lastName);
			temp.setFirstName(firstName);
			temp.setLastName(lastName);

			if(source.searchFriends(temp)){
				cout << "Are you sure you want to remove " << temp.getFirstName() << " " << temp.getLastName() << "?\n";
				cout << "Enter (Y/N): ";
				cin >> i;
				cin.ignore(10000,'\n');
				if(i == "Y" || i == "y"){
					// Execute code to remove friend
					temp = hashUsers.getUser(firstName + lastName);
					userRemoveFriend(source,temp,userBST,hashUsers,hashLogin);
					cout << "You have removed " << temp.getFirstName() << " " << temp.getLastName() << "\n\n";
				}else if(i != "N" || i != "n")
					cout << "ERROR: Invalid Input\n";

				cout << "Enter any key to return to 'Remove Friend': ";
				cin >> i;
				cin.ignore(10000,'\n');
				cout << "\n--------------------------------------------\n\n\n";
			}else{
				cout << "ERROR: No user \"" << firstName << " " << lastName << "\" exists in your friend list\n";
				cout << "Enter any key to return to 'Remove Friend': ";
				cin >>i;
				cout << "\n--------------------------------------------\n\n\n";
			}
		}
		if(input == 2){
			cout << "\n--------------------------------------------\n\n\n";
			break;
		}
	}
}

// Menu Interface: Login Screen -> Home Screen -> View My Friends -> View A Friend's Profile
void viewFriendProfile(User &source, BST<User> &userBST, HashUser &hashUsers){
	int input;
	bool error = false;
	string errorType,firstName,lastName,i;
	User temp;
	while(true){
		cout << "----------- View Friend's Profile ----------\n\n\n";
		cout << "Check out a profile\n\n";
		cout << "Options: \n";
		//cout << "1. Select from your friend list\n";
		cout << "1. Enter a name\n";
		cout << "2. Back (Return to View My Friends)\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-2): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
			cin.ignore(10000,'\n');
			error = true;
			errorType = "ERROR: Please enter numbers not letters";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input < 1 || 3 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 2";
			cout << "\n\n--------------------------------------------\n\n\n";
		}
		error = false;
		while(input == 1){
			cout << "Enter the User's first name and last name: ";
			cin >> firstName >> lastName;
			cin.ignore(10000,'\n');
			cout << endl;

			formatString(firstName,lastName);
			temp.setFirstName(firstName);
			temp.setLastName(lastName);

			if(source.searchFriends(temp)){
				temp = hashUsers.getUser(firstName + lastName);
				cout << "---------------- User Profile --------------\n\n";
				temp.printUser(cout);
				cout << "\n--------------------------------------------\n\n";
				cout << "Enter any key to return to 'View Friend's Profile': ";
				cin >> i;
				cin.ignore(10000,'\n');
				cout << endl << endl;
				break;
			}else{
				cout << "ERROR: No user \"" << firstName << " " << lastName << "\" exists in your friend list\n";
				cout << "Enter any key to return to 'View Friend's Profile: ";
				cin >>i;
				cin.ignore(10000,'\n');
				cout << "\n--------------------------------------------\n\n\n";
				break;
			}
		}
		if(input == 2){
			cout << "\n\n--------------------------------------------\n\n\n";
			break;
		}
	}
}

// Menu Interface: Login Screen -> Home Screen -> View My Friends -> View All Friends
void viewAllFriends(User &source){
	string input;

	cout << "-------------- View All Friends ------------\n\n\n";
	cout << "Here's a list of your friends " << source.getFirstName() << "\n\n";
	cout << "Friends(" << source.getNumFriends() << "):\n";
	source.printFriendsList(cout);
	cout << "Enter any key to return to 'View My Friends': ";
	cin >> input;
	cin.ignore(10000,'\n');
	cout << "\n\n--------------------------------------------\n\n\n";
}

// Menu Interface: Login Screen -> Home Screen -> View My Friends
void viewMyFriends(User &source, BST<User> &userBST, HashUser &hashUsers, HashLogin &hashLogin){
	int input;
	bool error = false;
	string errorType;
	while(true){
		cout << "-------------- View My Friends -------------\n\n\n";
		cout << "Manage Your Friends\n\n";
		cout << "Options: \n";
		cout << "1. View all Friends\n";
		cout << "2. View a friend's profile\n";
		cout << "3. Remove a friend\n";
		cout << "4. Back (Return to Home Screen)\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-4): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
			cin.ignore(10000,'\n');
			error = true;
			errorType = "ERROR: Please enter numbers not letters";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else if(input < 1 || 4 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 4";
			cout << "\n\n--------------------------------------------\n\n\n";
		}else{
			error = false;
			cout << "\n\n--------------------------------------------\n\n\n";
			switch(input){

			case 1: viewAllFriends(source);
					break;
			case 2: viewFriendProfile(source,userBST,hashUsers);
					break;
			case 3: removeFriend(source,userBST,hashUsers,hashLogin);
					break;
			case 4: return;
					break;
			default: cout << "Driver.cpp: viewMyFriends() error" << endl;
					 break;
			}
		}
	}
}

// Menu Interface: Login Screen -> Home Screen
int mainMenuPrompt(User source){
	int input;
	bool error = false;
	string errorType;

	while(true){
		cout << "---------------- Home Screen ---------------\n\n\n";
		cout << "Welcome " << source.getFirstName() << " " << source.getLastName() << "!\n\n";
		cout << "Main Menu: \n";
		cout << "1. View my friends" << endl;
		cout << "2. Search for new friends" << endl;
		cout << "3. Get Friend Recommendations" << endl;
		cout << "4. Logout" << endl << endl;
		cout << "5. (DEBUG) - EXIT AND FINISH PROGRAM.\n\n";
		if(error)
			cout << errorType << endl;
		cout << "Enter your choice (1-4): ";
		cin >> input;
		cin.ignore(10000,'\n');
		if(!cin){
			cin.clear();
		    cin.ignore(10000,'\n');
		    error = true;
		    errorType = "ERROR: Please enter numbers not letters";
		}else if(input < 1 || 5 < input){
			error = true;
			errorType = "ERROR: Please enter a choice 1 - 4";
		}
		else
		  break;
		cout << "\n\n--------------------------------------------\n\n\n";
	}

	cout << "\n\n--------------------------------------------\n\n\n";

	return input;
}

// Menu Interface: Login Screen
void loginScreen(HashLogin hl,User &source){
	bool flag = true;
	string valid = "Welcome to the Friend App!";
	string invalid = "Invalid Username or Password";
	string login,pass;

	while(true){
		cout << "--------------- Login Screen ---------------\n\n\n";
		if(flag == true)
			cout << valid << endl << endl;
		else
			cout << invalid << endl << endl;

		cout << "Sign-In" << endl << endl;
		cout << "Enter Username: ";
		cin >> login;
		cin.ignore(10000,'\n');
		cout << "Enter Password: ";
		cin >> pass;
		cin.ignore(10000,'\n');

		if(hl.loginCheck(login,pass)){
			source = hl.getUser(login,pass);
			cout << "\n\nLogin Successful!";
			cout << "\n\n--------------------------------------------\n\n\n";
			break;
		}

		flag = false;
		cout << "\n\n--------------------------------------------\n\n\n";
	}

}

int main(){

	FileIO file;				// FileIO object - Handles loading/saving data from/to text file
	BST<User> userBST;			// Ordered User List - Used for printing
	HashUser hashUsers;			// Hashed Users - Search User by Name
	HashInterest hashInterests;	// Hashed Interests - Search User by Interest
	HashLogin hashLogin;		// Hashed Logins - Search User by Login (login + pass)
	//Graph userNetwork;			// Network of Users - Used for recommended friends
	User sourceUser;			// Source User - The User currently logged on
	int input = 4;				// Menu Selection - Used to traverse menu

	//file.loadData("UserData.txt",userBST,hashUsers,hashInterests,hashLogin,userNetwork);
	file.loadData("UserData.txt",userBST,hashUsers,hashLogin,hashInterests);
    

	/*	// Added function to get a User's friends in a form of a list
	List<User> billsFriends = two.getFriendsList();

	billsFriends.printList(cout);

	billsFriends = one.getFriendsList();

	billsFriends.printList(cout);
	*/


	///*
	// Main User Interface
	while(true){
		if(input == 4)
			loginScreen(hashLogin,sourceUser);

		input = mainMenuPrompt(sourceUser);

		switch(input){

		case 1: viewMyFriends(sourceUser,userBST,hashUsers,hashLogin);						// View My Friends
				break;
		case 2: searchForNewFriends(sourceUser,userBST,hashUsers,hashLogin,hashInterests);	// Search For New Friends
				break;
		case 3: 																			// Get Friend Recommendations
				break;
		case 4: logoutScreen();																// Logout Screen & Save Data
				file.saveData("OutputUserData.txt",userBST);
				break;
		case 5: file.saveData("OutputUserData.txt",userBST);								// Exit Program & Debug Status
				debugDataStructures(userBST,hashUsers,hashLogin,hashInterests);
				cout << "Have a nice day! :)\n\n";
				exit(0);
				break;
		default:cout << "Driver.cpp: Main User Interface error\n";							// Something Broke
				exit(-1);
				break;
		}

	}
	//*/

	return 0;
}

