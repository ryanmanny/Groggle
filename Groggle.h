#pragma once

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

//#include "extraFunctions.h"

#define wordfile "cleanBoggle.txt" //removed the apostrophe words
#define boardHeight 4
#define boardWidth 4
#define boardSize boardHeight * boardWidth
#define dieSides 6
#define SHORT 6

#define FILEMODE 0
#define STRINGMODE 1

#define lineBreak " -----------------"
#define space " | "
#define qSpace "| "

#define timeStart(); clock_t start = clock();
#define timeStop(); clock_t end = clock(); cout << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

using namespace std;

void cleanDictionary(void);

class Groggle;
class WordList;
class Board;

class WordList
{
public:
	WordList(string filename = wordfile) //for changing languages maybe
	{
		ifstream file(filename); //open file
		string s;
		while (!file.eof())
		{
			file >> s; //copy word from file and insert into hash
			words.insert(pair<string, bool>(s, true));
			s = s.substr(0, SHORT);
			words_short.insert(pair<string, bool>(s, true));
		}
		file.close();
	}
	bool has(const string & s) const
	{
		auto it = words.find(s);
		//if the word is in there return true
		if (it != words.end()) //hash iterators freak me out
			return true;
		else return false;
	}
	bool add(string s)
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
	bool shortCircuit(const string & s) const
	{
		auto it = words_short.find(s.substr(0, SHORT));

		if (it != words_short.end())
			return false; //path makes sense, keep going
		else return true; //path sucks, stop before the program slows way down
	}
private:
	map<string, bool> words; //hash table for instant searching
	map<string, bool> words_short;
};

class Board
{
public:
	Board() : dist_board(0, boardSize - 1) ,  dist_side(0, dieSides - 1)//inits board
	{
		//chrono usage from cplusplus
		rand.seed((unsigned int)chrono::system_clock::now().time_since_epoch().count());

		for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth ; j++)
			board[i][j] = ' ';

		//initializes all the dice. MIGHT be a better way to do this
		dice[0] = { 'a', 'e', 'a', 'n', 'e', 'g' };
		dice[1] = { 'a', 'h', 's', 'p', 'c', 'o' };
		dice[2] = { 'a', 's', 'p', 'f', 'f', 'k' };
		dice[3] = { 'o', 'b', 'j', 'o', 'a', 'b' };
		dice[4] = { 'i', 'o', 't', 'm', 'u', 'c' };
		dice[5] = { 'r', 'y', 'v', 'd', 'e', 'l' };
		dice[6] = { 'l', 'r', 'e', 'i', 'x', 'd' };
		dice[7] = { 'e', 'i', 'u', 'n', 'e', 's' };
		dice[8] = { 'w', 'n', 'g', 'e', 'e', 'h' };
		dice[9] = { 'l', 'n', 'h', 'n', 'r', 'z' };
		dice[10] = { 't', 's', 't', 'i', 'y', 'd' };
		dice[11] = { 'o', 'w', 't', 'o', 'a', 't' };
		dice[12] = { 'e', 'r', 't', 't', 'y', 'l' };
		dice[13] = { 't', 'o', 'e', 's', 's', 'i' };
		dice[14] = { 't', 'e', 'r', 'w', 'h', 'v' };
		dice[15] = { 'n', 'u', 'i', 'h', 'm', 'q' };
	}

	//file constructors for debugging the word finder
	Board(const string & s, const int & mode = FILEMODE) //combo string constructor and file constructor
	{
		if (mode == FILEMODE)
		{
			ifstream file(s);
			*this = Board(file); //I cannot believe this works
		}
		else if (mode == STRINGMODE)
		{
			*this = Board(); //default constructor

							 //must be the proper length if not the program would be dunksis
			if (s.size() == boardSize) //this should be a member of the board, not #defined
			{
				//technically these can be numbers or whitespace but if they want a nasty board so bad let em have it
				for (int i = 0; i < boardWidth; i++)
					for (int j = 0; j < boardHeight; j++)
						board[i][j] = s.at(i*boardWidth + j);
			}
			else
			{
				//just give them a random board
				cout << "Wrong number of letters, randomizing board" << endl;
				this->randomize();
			}
		}
	}
	Board(ifstream & file)
	{
		*this = Board();
		char c = '\0';
		for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth ; j++)
		{
			file >> c;
			board[i][j] = c;
		}
	}

	vector<string> getFoundWords(void) //returns copy of foundWords
	{
		return foundWords;
	}

	void randomize(void)
	{
		int randomArr[boardSize];
		//populates an sequential array with 0-boardSize
		for (int i = 0; i < boardSize; i++)
			randomArr[i] = i;

		//randomly orders the boardSize numbers
		for (int i = 0; i < boardSize; i++)
			swap(randomArr[dist_board(rand)], randomArr[i]);

		int j = 0;
		//use this ordering to place the blocks in the board, random side up
		for (int i : randomArr)
		{
			//goes to a random position and places the dice in order, random side up
			board[i / boardHeight][i % boardWidth] = dice[j++].at(dist_side(rand));
		}
	}

	void print(void)
	{
		for (int i = 0; i < boardHeight; i++)
		{
			cout << lineBreak << endl << space;
			for (int j = 0; j < boardWidth; j++)
			{
				if (board[i][j] != 'q')
					cout << (char)toupper(board[i][j]) << space;
				else
					cout << "Qu" << qSpace; //a little sloppy
			}
			cout << endl;
		}
		cout << lineBreak << endl;
	}

	vector<string> findWords(const WordList & words) //a bit scary (the biggest data structure ever) but will work
	{
		//resets foundWords
		foundWords.clear();

		string s;
		bool nullBoard[boardHeight][boardWidth];

		for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth ; j++)
			nullBoard[i][j] = false;

		//needs to make every possible permutation through the board and check them against the hash
		////there is probably a way to short circuit stupid paths but I don't know how to do that I DID IT
		for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth ; j++)
		{
			//need to make boardHeight * boardWidth recursive calls. since you can start from any position on the board
			//this for loop is needed. can't use recursion for everything
			findWordsFromPos(nullBoard, i, j, s, words);
		}
		//all strings found, let's print them
		// for (string word : foundWords)
		// 	cout << word << endl;
		// cout << "Number of words found: " << foundWords.size() << endl;

		return foundWords;
	}

	//sort words from longest to shortest
	void sortWords()
	{
		std::sort(foundWords.begin(), foundWords.end(), [] (const string &lhs, const string &rhs)
		{
			return lhs.length() > rhs.length();
		});
	}

	//precondition: words must be found first
	void printWords()
	{
		for (string word : foundWords)
			cout << word << endl;
		cout << "Number of words found: " << foundWords.size() << endl;
	}
private:
	char board[boardHeight][boardWidth];
	vector<string> foundWords;
	vector<char> dice[boardSize]; //find out why array didn't work here because that will use less memory
	default_random_engine rand; //rand objects
	uniform_int_distribution<int> dist_board;
	uniform_int_distribution<int> dist_side;

	void findWordsFromPos(bool nullBoard[boardHeight][boardWidth], const int & i, const int & j, string & s, const WordList & words) //hopefully the stack is okay
	{
		//check if recursive call is in the bounds of the board AND if the letter hasn't been used yet
		//if (i >= 0 && i < boardHeight && j >= 0 && j < boardWidth && nullBoard[i][j] == false) TOO SLOW, moved this to the for loop

		if (s.size() < SHORT || !words.shortCircuit(s)) //quits if going down a stupid path
		{
			//cout << i << " " << j << endl;
			s += board[i][j]; //add letter to current word
			if (board[i][j] == 'q')
				s += 'u'; //adds the bonus u attached to qs
			//nullboard stops recursion from using a letter more than once
			nullBoard[i][j] = true;

			//if the word is in the wordList hash table, add it to the newWords list
			if (words.has(s))
			{
				//cout << s << endl;
				if (s.length() >= 3 && find(foundWords.begin(), foundWords.end(), s) == foundWords.end() )
					foundWords.push_back(s);
			}

			//recursion time - moves to all 9 surrounding letters
			//these will all happen while the current letter is blocked off
			for (int k = i - 1; k <= i + 1; k++)
			for (int l = j - 1; l <= j + 1; l++)
			if (k >= 0 && k < boardHeight && l >= 0 && l < boardWidth && nullBoard[k][l] == false) //don't do recursive calls unless we have to
				findWordsFromPos(nullBoard, k, l, s, words);

			//backs up a letter to go somewhere else
			s.erase(s.length() - 1);
			if (s.length() > 0 && s.at(s.length() - 1) == 'q')
			{
				//cout << "q alert" << endl;
				s.erase(s.length() - 1); //case for removing both letters of q and u combo
			}

			nullBoard[i][j] = false;
		}
		else return;
	}
};

class Groggle
{
public:
	void runApp(void);
	void playGame(void);
	void display(void);
	void printBoard(void)
	{
		board.print();
	}
	void randomizeBoard(void)
	{
		board.randomize();
	}
	void loadBoard(void)
	{
		board = Board("exampleboard.txt");
	}
private:
	WordList words;
	Board board;
};
