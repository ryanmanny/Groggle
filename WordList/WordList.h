#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <iterator>
#include <cctype>

#define ALPHA 26

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::array;
using std::iterator;
using std::input_iterator_tag;

struct Node
{
	bool term; //True if this is the last letter of a word (so Groggl doesn't trigger Groggle even though it's in the tree)
	array<Node *, ALPHA> child; //Every letter is only instantiated when necessary. Letter is in the identity of the branch

	Node()
	{
		for (int i = 0; i < ALPHA; i++)
		{
			child.at(i) = nullptr;
		}
		term = false;
	}
	Node(bool newTerm)
	{
		*this = Node();
		term = newTerm;
	}
};

//Contains every word in English languages in hash table for fast lookup
class WordList
{
public:
	WordList();
	WordList(const string & filename);
	~WordList(); //DEAR GOD DEALLOCATE THE TREE

	int has(const string & str) const;
	int has(const char * str) const;

	bool insert(const string & str);
	bool insert(const char * str);
	
	//bool shortCircuit(const string & s) const;
	//void changeShort(const unsigned int newShort);
private:
	//First layer of the tree. No single root because words can start with different letters :)
	array<Node *, ALPHA> pRoot;

	//OLD IMPLEMENTATION
	//Hash table for instant lookup - TODO: Find out if an unordered map would be better. It is
	//unordered_map<string, bool> words; 
	//Abridged version of hash table for short circuiting board paths... really speeds up searchtimes
	//unordered_map<string, bool> words_short;
	//Short length replaces SHORT - dynamically calculated based on board size
	//unsigned int shortLength;
};
