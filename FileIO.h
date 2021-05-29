/*
 * FileIO.h
 *
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "BST.h"
#include "List.h"
#include "HashUser.h"
#include "HashInterest.h"
#include "HashLogin.h"
#include "Graph.h"
#include "User.h"

class FileIO{

public:
	// Constructor
	FileIO();
	~FileIO(){};

	// Additional Functions
	//void loadData(string filename,BST<User> &bst,HashUser &hu, HashInterest &hi,HashLogin &hl,Graph &g);
	void loadData(string filename,BST<User> &bst,HashUser &hu, HashLogin &hl, HashInterest &hi);
	// Loads data from text file to data structures

	void saveData(string filename,BST<User> bst) const;
	// Saves data from data structures to text file


private:
	vector<User> userTable;
	vector<List<string>> userFriends;

};


#endif /* FILEIO_H_ */
