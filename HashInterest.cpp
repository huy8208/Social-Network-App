/*
 * HashInterest.cpp
 *  version 1
 *  Created on: Mar 10, 2018
 *      Author: Huy
 */

#include "HashInterest.h"
#include <cstddef>
#include <iomanip>


using namespace std;

int HashInterest::hash(string key) const
{
    int index;
    int sum = 0;
    for(int i = 0; i < (int)key.length() ; i++){
        sum += (int) key[i];
    }
    index = sum % SIZE;
    return index;
}


int HashInterest::countBucket(int index) const
{
    assert (index >= 0);
    assert (index < SIZE);
    return Table[index].getLength();
}

int HashInterest::checkInterest (string interest) const
{
    int index = hash(interest);
    while (parallelTable[index] != interest)
    {
    	index++;
        if (index > SIZE)
        {
            return -1;
        }
    }
    return index;
}

bool HashInterest::checkUserWithInterest(string name, string interest){
	int index = checkInterest(interest);
	User temp;

	if(index == -1)
		return false;

	for(int i = 1; i < Table[index].getLength()+1; i++){
		Table[index].advanceToIndex(i);
		temp = Table[index].getIterator();
		if(temp.getFirstName() + temp.getLastName() == name)
			return true;

	}

	return false;
}

void HashInterest::insertInterest(User u)
{
    List<string> temp (u.getInterests());
    temp.startIterator();

    for (int i = 0; i < temp.getLength() ; i++){			// Iterating through a User's interest list
        int index = hash(temp.getIterator());				// Inserting unique interests (No Duplicates) into a table of interests
        													// and inserting Users into a different table mapped by interests

        if (parallelTable[index].empty()) 					// CASE 1: Interest Table index is empty
        {
            parallelTable[index] = temp.getIterator();		// Insert Interest into empty Table Index
            Table[index].insertLast(u);						// Insert User into the matching index of the Parallel Table
        }
        else if(parallelTable[index] == temp.getIterator()) // CASE 2: Interest Table index matches with interest string
        {
            Table[index].insertLast(u);						// Insert User into the matching index of the Parallel Table
        }
        else 												// CASE 3: Interest Table index does not match with string and is not empty
        {
        	bool found = false;

        	for(int i = index; i < SIZE; i++){				// Linear Search the Interest Table if the interest exists
        		if(parallelTable[i] == temp.getIterator()){
        			Table[i].insertLast(u);
        			found = true;
        			i = SIZE;
        		}
        	}

        	if(found == false){								// If interest was not found in table, Then Linear Probe
        		int num = index;
        		while(!parallelTable[num].empty() ){		// num Index may go out of bounds once it passes capacity (SIZE of 60)
        			num++;									// It may be optimal to change hash function to sum % 50 or sum % 55
        			if(num == SIZE+1)						// to allow 5-10 reserve slots. (Or just increase capacity)
                        assert(num < SIZE + 1);
        				break;
        		}
        		parallelTable[num] = temp.getIterator();
        		Table[num].insertLast(u);
        	}
        }
        temp.advanceIterator();
    }

}

void HashInterest::removeInterest(string interest)
{
    cout<<endl;
    if (checkInterest(interest) == -1)
    {
        cout<<interest<<" is not found in our Hash Interest Table. Can not be remove !!!"<<endl;
    }
    else
    {
        cout<<"Successfully removed "<<interest<<" interest from Hash Interest Table."<<endl;
        cout<<"Successfully removed all the users under "<<interest<<" interest from Hash Interest Table."<<endl;
        for (int i = 0; i < Table[checkInterest(interest)].getLength(); i++)
        {
            Table[checkInterest(interest)].removeLast();
        }
        parallelTable[checkInterest(interest)].clear();
    }
    cout<<endl<<endl;
}

void HashInterest::removeUser (string Interest, User U)
{
    if (checkInterest(Interest) == -1)
    {
        cout<<Interest<<" interest is not found in Hash Table. Can not be removed !!!"<<endl;
    }
    else if (Table[checkInterest(Interest)].linearSearch(U) == -1)
    {
        cout<<"There are no users under the name: "<<U.getFirstName()<<" "<<U.getLastName()<<" with "<<Interest<<" interest !!!"<<endl;
    }
    else
    {
        int index = Table[checkInterest(Interest)].linearSearch(U);
        Table[checkInterest(Interest)].startIterator();
        Table[checkInterest(Interest)].advanceToIndex(index);
        Table[checkInterest(Interest)].removeIterator();
        cout<<"Successfully removed user: "<<U.getFirstName()<<" "<<U.getLastName()<<" under "<<Interest<<" interest."<<endl;
    }
    cout<<endl<<endl;
}

void HashInterest::printBucket(ostream& out, int index) const{
	assert(0 <= index && index < SIZE);			// Precondition: Index is not out of bounds

    Table[index].printNamesAtInterests(out);	// Prints all of the User's names who have this interest
}

void HashInterest::printSpecialBucket(ostream& out, int index, User u){
	assert(0 <= index && index < SIZE);
	User temp;
	int num = 1;
	for(int i = 1; i < Table[index].getLength() + 1; i++){
		Table[index].advanceToIndex(i);
		temp = Table[index].getIterator();

		if(temp.getUserID() != u.getUserID() && u.searchFriends(temp) == false){
			out << num++ << ". " << temp.getFirstName() << " " << temp.getLastName() << endl;
		}
	}
	out << endl;
}

void HashInterest::printTable(ostream& out) const{
    for (int index = 0; index < SIZE; index++){
        if (!parallelTable[index].empty()){
            out << setw(2) << right << index << ". " << setw(13) << left << parallelTable[index] << "| ";
            Table[index].printNameNumberedList(out);
        }
    }
}






