#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h> //toupper()
#include <vector>
#include <map> //hash table for words
#include <stdexcept> //for trying to catch the exception that stoi throws :(
#include <random> //random generator and distribution
#include <chrono> //seeding random
#include <curses.h>
#include <algorithm>

#define boardHeight 4
#define boardWidth 4
#define boardSize boardHeight * boardWidth
#define dieSides 6
#define SHORT 6

enum loadMode
{
	FILEMODE, STRINGMODE
};

using std::cout;
using std::endl; //remove these two when curses added

using std::map;
using std::string;
using std::vector;
using std::ifstream;
using std::pair;

#define lineBreak " -----------------"
#define space " | "
#define qSpace "| "

//contains every word in English languages in hash table for fast lookup
class WordList
{
public:
	WordList();
	WordList(const string & filename);
	bool has(const string & s) const;
	bool add(string & s);
	bool shortCircuit(const string & s) const;
private:
	map<string, bool> words; //hash table for instant searching
	map<string, bool> words_short;
};

class Board
{
public:
	Board();
	Board(const string & s, const loadMode & mode = loadMode::FILEMODE);
	Board(ifstream & file);

	vector<string> getFoundWords(void); //returns copy of foundWords

	void print(void);
	void randomize(void);
	vector<string> findWords(const WordList & words);
	
	void sortWords();
	void printWords();
private:
	char board[boardHeight][boardWidth];
	vector<char> dice[boardSize]; //find out why array didn't work here because that will use less memory

	vector<string> foundWords;
	
	std::default_random_engine rand; //rand objects
	std::uniform_int_distribution<int> dist_board;
	std::uniform_int_distribution<int> dist_side;

	void findWordsFromPos(bool nullBoard[boardHeight][boardWidth], const int & i, const int & j, string & s, const WordList & words);
};
