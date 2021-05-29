//
//  HashUser.cpp
//  CIS22C-Project
//
//  Created by SuperNOVA on 3/9/18.
//  Copyright © 2018 SuperNOVA. All rights reserved.
//


#include "HashUser.h"
#include "User.h"
#include "List.h"
#include <iostream>
#include <assert.h>
#include <cstdlib>

int HashUser::hash(string key) const
{
    int index, sum = 0;
    for(int i = 0; i < (int)key.length(); i++)
        sum += (int) key[i];
    index = sum % SIZE;
    return index;
}

int HashUser::countBucket(int index) const
{
    assert (index >= 0);
    assert (index < SIZE);
    return Table[index].getLength();
}

void HashUser::insert (User U)
{
    int index = hash((U.getFirstName() + U.getLastName()));
    Table[index].insertLast(U);
}

void HashUser::printTable(ostream& out) const
{
	/*
    cout<<"***Printing HashUser Table***"<<endl<<endl;
    for (int i = 0; i < SIZE; i++)
    {
        if (Table[i].isEmpty())
        {
            out<<endl;;
        }
        else
        {
            out<<"Group "<<i + 1<<endl;
            out<<Table[i].getFirst();
            out<<"+"<<countBucket(i) - 1<<" more User(s)"<<endl<<endl<<endl;
        }
    }
    */
    for(int index = 0; index < SIZE; index++){       // Loop to print a User at each Table[index] if applicable
    	if(!Table[index].isEmpty()){
    		out << "Group " << index + 1 << endl;
    		out << Table[index].getFirst() << endl;
    		out << "+" << countBucket(index) - 1 << " more User(s)" << endl << endl;;
       }
    }
}

void HashUser::printBucket(ostream &out, int index) const
{
    assert(index >= 0);
    assert(index < SIZE);
    Table[index].printList(out);
}

int HashUser::search(User U) const
{
    int index = hash((U.getFirstName() + U.getLastName()));

    if(Table[index].isEmpty())
    	return -1;

    return Table[index].linearSearch(U);
}

void HashUser::remove(User U)
{
    int index = hash((U.getFirstName() + U.getLastName()));
    assert (Table[index].linearSearch(U) != -1);
    Table[index].startIterator();
    Table[index].advanceToIndex(Table[index].linearSearch(U));
    Table[index].removeIterator();
}

void HashUser::searchByFirstName(string s){
	User temp;
	int num = 1;
	for(int i = 0; i < SIZE; i++){
		if(!Table[i].isEmpty()){
			Table[i].startIterator();
			while(!Table[i].offEnd()){
				temp = Table[i].getIterator();
				if(temp.getFirstName() == s)
					cout << num++ << ". " << temp.getFirstName() << " " << temp.getLastName() << endl;
				Table[i].advanceIterator();
			}
		}
	}
	cout << endl;
}

User HashUser::getUser(string name) {
	int index = hash(name);
	User temp;

	if(!Table[index].isEmpty()){
		Table[index].startIterator();
		for(int i = 0; i < Table[index].getLength(); i++){
			temp = Table[index].getIterator();
			if(temp.getFirstName() + temp.getLastName() == name){
				return Table[index].getIterator();
			}
			Table[index].advanceIterator();
		}
	}

	return temp;
}
