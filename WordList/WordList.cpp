#include "WordList.h"

#define WORDFILE "Board/cleanBoggle3.txt"

//Must be constructed somehow I guess. Change this later
WordList::WordList()
{
	*this = WordList(WORDFILE);
}

WordList::WordList(const string & filename) //For changing languages maybe
{
	for (int i = 0; i < ALPHA; i++)
	{
		pRoot.at(i) = new Node(false); //Assume there exists a word that starts with every letter
	}

	ifstream file(filename); //Open the file
	string s;

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> s; //copy word from file and insert into tree
			// std::cout << s << std::endl;
			insert(s.c_str());
			//words.insert(pair<string, bool>(s, true));
			//s = s.substr(0, shortLength);
			//words_short.insert(pair<string, bool>(s, true));
		}
		file.close();
	}
	else
	{
		cout << "Wordfile didn't open" << endl;
	}
}

WordList::~WordList()
{
	//DEALLOCATE QUICK THE TREE IS ABOUT TO GO OUT OF SCOPE

}

bool WordList::insert(const string & str)
{
	return insert(str.c_str());
}

//ITERATIVE NOW BECAUSE IT MAKES WAY MORE SENSE THAT WAY
//EXCEPT WITHOUT RECURSION IT IS VERY DIFFICULT TO ACTUALLY MODIFY THE DATA STRUCTURE
bool WordList::insert(const char * str) //Now insert doesn't modify original string
{
	//Get the pointer to pRoot so we can modify it later and the changes will persist
	//pCur needs to be a double pointer so we can save changes to the 
	Node ** pCur = &(pRoot.at(*str++ - 'a'));

	//While the string still needs some inserting
	while (*str != '\0') //Will not work with one character words
	{
		//YOU MAY FIND YOURSELF IN A TREE WITH SOME AMOUNT OF STRING LEFT
		//1) We are at the end of the string, in which case, set term to true
		//2) We are not at the end of the string, in which case just continue

		//Advances down the path and increments
		//Again, get a pointer to the next child
		pCur = &((*pCur)->child.at(*str++ - 'a'));

		if (*pCur == nullptr)
		{
			//Overwrite pCur with this new Node. Should propogate through the rest of the tree
			*pCur = new Node(false); //Always assume terminator is false. This will be corrected if we are at the end
		}
	}
	//WE ARE AT THE NULL CHARACTER - So this is a termination character, which marks a valid word
	(*pCur)->term = true;
	return true;
}

int WordList::has(const string & str) const
{
	return has(str.c_str());
}

//Returns -1 if bad path happens somewhere along the way, 0 if potential correct path, 1 if found
int WordList::has(const char * str) const
{
	//Start with first letter
	Node * pCur = pRoot.at(*str++ - 'a');

	//Iterative
	//Until we get to the null character, let's go
	while (*str != '\0' && isalpha(*str))
	{
		//Advance down the path of the next letter
		pCur = pCur->child.at(*str++ - 'a');

		//Check to see if that path is any good
		if (pCur == nullptr)
		{
			//Path n'existe pas, return -1
			return -1;
		}
	}

	//We made it to the end of the string, is it a valid word?
	//If we are at a terminating character we should be at the end
	if (pCur->term == true)
	{
		//Found
		return 1;
	}
	//Potential valid path - not end of the string OR end of the line. EXCELLENT
	return 0;
}


// bool WordList::has(const string & s) const
// {
// 	auto it = words.find(s);
// 	//if the word is in there return true
// 	if (it != words.end()) //hash iterators freak me out
// 		return true;
// 	else return false;
// }

// bool WordList::add(string & s)
// {
// 	cout << s << endl;
// 	for (string::size_type i = 0; i < s.length(); i++)
// 	{
// 		s.at(i) = tolower(s.at(i));
// 	}
// 	//Uses same process as the words constructor
// 	if (!has(s))
// 	{
// 		words.insert(pair<string, bool>(s, true));
// 		cout << s << " was inserted successfully!" << endl;
// 		s = s.substr(0, shortLength);
// 		words_short.insert(pair<string, bool>(s, true));
// 		return true; //Returns true on success
// 	}
// 	else
// 	{
// 		cout << s << " is already in the list!" << endl;
// 		return false;
// 	}
// }

// void WordList::changeShort(const unsigned int newShort)
// {
// 	shortLength = newShort;
// }

// //Really good idea speeds up the runtime by an order of magnitude
// //Returns false if there is no word longer than SHORT characters along the current path
// //Turns N! Factorialish behavior into N! divided by something probably
// bool WordList::shortCircuit(const string & s) const
// {
// 	auto it = words_short.find(s.substr(0, shortLength));

// 	if (it != words_short.end())
// 		return false; //path makes sense, keep going
// 	else return true; //path sucks, stop before the program slows way down
// }
