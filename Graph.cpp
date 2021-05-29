/**

* Trevor Hansen

* CIS 22C, Lab 8

*/

#include <iostream>
#include "Graph.h"

using namespace std;

/**Constructors and Destructors*/

Graph::Graph(int n){
	vertices = n;
	edges = 0;
	User temp;
	allUsers[0] = temp;
	for(int i = 0; i <= n; i++){
		List<int> list;
		adj.push_back(list);
		color.push_back('W');
		distance.push_back(-1);
		parent.push_back(0);
	}
}
//initializes an empty graph to have n vertices

/*** Access Functions ***/

int Graph::getNumEdges() const{
	return edges;
}

int Graph::getNumVertices() const{
	return vertices;
}

bool Graph::isEmpty() const{
	return (vertices == 0);
}

int Graph::getDistance(int v) const{
	assert(v <= getNumVertices());
	return distance[v];
}

int Graph::getParent(int v) const{
	assert(v <= getNumVertices());
	return parent[v];
}

char Graph::getColor(int v) const{
	assert(v <= getNumVertices());
	return color[v];
}

/*** Manipulation Procedures ***/

void Graph::addEdge(User& u, User& v){
	if(adj[u.getUserID()].isEmpty()){
		adj[u.getUserID()].insertLast(v.getUserID());
		adj[v.getUserID()].insertLast(u.getUserID());
		edges++;
	}else{
		if(adj[u.getUserID()].linearSearch(v.getUserID()) == -1){
			adj[u.getUserID()].insertLast(v.getUserID());
			adj[v.getUserID()].insertLast(u.getUserID());
			edges++;
		}
	}
}
//inserts vertex v into the adjacency list of vertex u (i.e. inserts v into the list at index u)
//and inserts u into v.

void Graph::removeEdge(User& u, User& v){
	if(adj[u.getUserID()].isEmpty() || adj[v.getUserID()].isEmpty())
		return;
	int indexU = adj[u.getUserID()].linearSearch(v.getUserID());//Find index for v in u's list
	int indexV = adj[v.getUserID()].linearSearch(u.getUserID());//Find index for u in v's list
	if(indexU != -1){
		adj[u.getUserID()].advanceToIndex(indexU);
		adj[u.getUserID()].removeIterator();
	}
	if(indexV != -1){
		adj[v.getUserID()].advanceToIndex(indexV);
		adj[v.getUserID()].removeIterator();
	}
}

User Graph::searchByUserID(int ID){
	return allUsers[ID];
}

void Graph::insert(User u){
	allUsers[u.getUserID()] = u;
}

void Graph::friendsList(List<User>& list, User u){
	int ID = u.getUserID();
	adj[ID].startIterator();
	while(!adj[ID].offEnd()){
		User temp = searchByUserID(adj[ID].getIterator());
		list.insertLast(temp);
		adj[ID].advanceIterator();
	}
}

/*** Additional Operations ***/

void Graph::printGraph(ostream& out){
	for(int i = 1; i < getNumVertices(); i++){
		out << i << ". " << allUsers[i].getFirstName() << ": ";
		adj[i].startIterator();
		while(!adj[i].offEnd()){
			out << allUsers[adj[i].getIterator()].getFirstName() << "(" << adj[i].getIterator() << "), ";
			adj[i].advanceIterator();
		}
		out << endl;
	}
}
//Prints the adjacency list of each vertex in the graph,
//vertex: <space separated list of adjacent vertices>
//Prints to the console or to an output file given the ostream parameter

void Graph::printBFS(ostream& out){
	out << "v	c	p	d	\n";
	for(int i = 1; i < getNumVertices(); i++){
		out << allUsers[i].getFirstName() << "\t" << color[i] << "\t"
			<< allUsers[parent[i]].getFirstName() << "\t" << distance[i] << endl;
	}
}
//Prints the current values in the parallel vectors after executing BFS
//Prints to the console or to an output file given the ostream parameter
//First prints the heading:
//v <tab> c <tab> p <tab> d <tab>
//Then, prints out this information for each vertex in the graph
//Note that this function is intended purely to help you debug your code

void Graph::BFS(int source){
	assert(getNumVertices() > 0 && source < getNumVertices() && source > 0); // The second part might need to be changed
	List<int> que; //add all adjacent vertices to que so the algorithm can explore their adj vertices after

	//Sets all vertices to white, -1 as distance from source, and parent 0
	for(int i = 0; i < getNumVertices(); i++){
		color[i] = 'W';
		distance[i] = -1;
		parent[i] = 0;
	}
	color[source] = 'G';
	distance[source] = 0;
	que.insertLast(source);
	while(!que.isEmpty()){
		int x = que.getFirst();
		que.removeFirst();
		adj[x].startIterator();
		//Explore all adjacent vertices (y) of x
		while(!adj[x].offEnd()){
			int y = adj[x].getIterator();
			if(color[y] == 'W'){
				color[y] = 'G';
				distance[y] = distance[x] + 1;
				parent[y] = x;
				que.insertLast(y);
			}
			adj[x].advanceIterator();//Next adjacent vertex in adj[x]
		}
		color[x] = 'B'; // Have explored everything in adj[x]
	}
}
//Performs breath first search on this Graph give a source vertex
//pre: at least one vertex must exist
//pre: source is a vertex in the graph

void Graph::printPath(int source, int destination, ostream& out){
	if(source == destination){
		out << allUsers[source].getFirstName() << " ";
	}else if(parent[destination] == 0){
		out << "No path from " << allUsers[source].getFirstName() << " to " << allUsers[destination].getFirstName() << " exists";
	}else{
		printPath(source, parent[destination], out);
		out << allUsers[destination].getFirstName() << " ";
	}
}
//Prints the path from the source to the destination vertex
//Prints to the console or to an output file given the ostream parameter

void Graph::getFriendRecs(User u, List<friendRec>& rankedUsers){
	List<User> uFriendsList;//Holds users list of friends
	friendsList(uFriendsList, u);
	List<string> uInterestsList = u.getInterests();

	BFS(u.getUserID());

	for(int i = 1; i < getNumVertices(); i++)
	{
		if(getDistance(i) == 2)//Will only recommend friends that have mutual friends
		{
			friendRec temp;
			temp.newfriend = searchByUserID(i);
			List<User> tempFriendsList;
			friendsList(tempFriendsList, temp.newfriend);
			List<string> tempInterestsList = temp.newfriend.getInterests();

			//This will check see which friends the user and friendRec have in common
			uFriendsList.startIterator();
			while(!uFriendsList.offEnd())
			{
				int found = tempFriendsList.linearSearch(uFriendsList.getIterator());
				if(found != -1)
				{
					temp.mutualFriends.insertLast(uFriendsList.getIterator());
					temp.numMutualFriends++;
				}
				uFriendsList.advanceIterator();
			}

			//This will check see which interests the user and friendRec have in common
			uInterestsList.startIterator();
			while(!uInterestsList.offEnd())
			{
				int found = tempInterestsList.linearSearch(uInterestsList.getIterator());
				if(found != -1)
				{
					temp.mutualInterests.insertLast(uInterestsList.getIterator());
					temp.numMutualInterests++;
				}
				uInterestsList.advanceIterator();
			}

			if(rankedUsers.isEmpty())
			{
				rankedUsers.insertFirst(temp);
			}
			else
			{
				rankedUsers.startIterator();
				while(!rankedUsers.offEnd() && (temp.numMutualFriends < rankedUsers.getIterator().numMutualFriends
						|| (temp.numMutualInterests < rankedUsers.getIterator().numMutualInterests
						&& temp.numMutualFriends == rankedUsers.getIterator().numMutualFriends)))
				{
					rankedUsers.advanceIterator();
				}
				if(rankedUsers.offEnd())
				{
					rankedUsers.insertLast(temp);
				}
				else
				{
					if(rankedUsers.getFirst().newfriend == rankedUsers.getIterator().newfriend)
					{
						rankedUsers.insertFirst(temp);
					}
					else
					{
						rankedUsers.reverseIterator();
						rankedUsers.insertIterator(temp);
					}
				}
			}
		}
	}
}
