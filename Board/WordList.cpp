#include "Board.h"

#define WORDFILE "Board/cleanBoggle.txt"

WordList::WordList() : words(), words_short()
{
	*this = WordList(WORDFILE);
}

WordList::WordList(const string & filename) //for changing languages maybe
{
	ifstream file(filename); //open file
	string s;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> s; //copy word from file and insert into hash
			words.insert(pair<string, bool>(s, true));
			s = s.substr(0, SHORT);
			words_short.insert(pair<string, bool>(s, true));
		}
		file.close();
	}
	else
	{
		cout << "Wordfile didn't open" << endl;
	}
}

bool WordList::has(const string & s) const
{
	auto it = words.find(s);
	//if the word is in there return true
	if (it != words.end()) //hash iterators freak me out
		return true;
	else return false;
}

bool WordList::add(string & s)
{
	cout << s << endl;
	for (string::size_type i = 0; i < s.length(); i++)
	{
		s.at(i) = tolower(s.at(i));
		cout << s << endl;
	}
	//uses same process as the words constructor
	if (!has(s))
	{
		words.insert(pair<string, bool>(s, true));
		cout << s << " was inserted successfully!" << endl;
		s = s.substr(0, SHORT);
		words_short.insert(pair<string, bool>(s, true));
		return true; //returns true on success
	}
	else
	{
		cout << s << " is already in the list!" << endl;
		return false;
	}
}

//really good idea speeds up the runtime by 100fold
//returns false if there is no word longer than 7 characters along the current path
bool WordList::shortCircuit(const string & s) const
{
	auto it = words_short.find(s.substr(0, SHORT));

	if (it != words_short.end())
		return false; //path makes sense, keep going
	else return true; //path sucks, stop before the program slows way down
}
