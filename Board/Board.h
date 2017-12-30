#include "../WordList/WordList.h"

#include <iostream>
//#include <fstream>
#include <string>
#include <ctype.h> //toupper()
#include <vector>
#include <array>
//#include <unordered_map> //hash table for words
#include <stdexcept> //for trying to catch the exception that stoi throws :(
#include <random> //random generator and distribution
#include <chrono> //seeding random
#include <curses.h>
#include <algorithm>

#define BOARDSIZE boardHeight * boardWidth
#define DIESIDES 6
//#define DEFAULTSHORT 6 //This is SLOW for the 5x5 boards. Find deterministic way to find better SHORT

enum loadMode
{
	FILEMODE, STRINGMODE
};

using std::cout;
using std::endl; //remove these two when curses added

using std::string;
using std::vector;
using std::array;

#define lineBreak  "----"
#define space " | "
#define qSpace "| "

class Board
{
public:
	Board(const int newBoardWidth, const int newBoardHeight);
	Board(const int newBoardWidth, const int newBoardHeight, const string & s, const loadMode & mode = loadMode::FILEMODE);
	~Board();

	bool setBoard(const string & s);
	void resizeBoard(const int newBoardWidth, const int newBoardHeight);
	void resetDice(void);

	//Calculates short length based on board size
	unsigned int getShortLength(void);

	//Returns copy of foundWords... fairly BIG memory
	//If I allocated foundWords on the heap I could pass back a reference or pointer... hmmm
	vector<string> getFoundWords(void); 

	void print(void);
	void randomize(void);
	vector<string> findWords(const WordList & words);
	
	void sortWords();
	void printWords();
private:
	//FUNCTIONS:
	//void findWordsFromPos(bool nullBoard[boardHeight][boardWidth], const int & i, const int & j, string & s, const WordList & words);
	void findWordsFromPos(vector<vector<bool>> & nullBoard, const int i, const int j, string & s, const WordList & words);

	//Precondition: Takes a double number between 0.0 and 100.0 and generates a letter based on English letter distribution
	char getLetter(double randNum);

	//DATA:
	int boardWidth;
	int boardHeight;

	//2D Vector to hold the board
	vector<vector<char>> board;
	//Vector of char arrays to hold the dice
	vector<array<char, DIESIDES>> dice;

	//Vector of strings to hold all valid words in the board
	vector<string> foundWords;
	
	std::default_random_engine rand; //rand objects
	std::uniform_int_distribution<int>     dist_board;
	std::uniform_int_distribution<int>     dist_side;
	std::uniform_real_distribution<double> dist_letters;

	//Letter dist from http://www.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
	//Likelihoods stores all distribution values in order. Used by getLetter
	double likelihoods[26];
};
