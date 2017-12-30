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

#include "../Board/Board.h"
#include "../WordList/WordList.h"

#define timeStart(); clock_t start = clock();
#define timeStop(); clock_t end = clock(); cout << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

using std::cin;
using std::exception;
using std::ofstream;

void cleanDictionary(void);

class Groggle
{
public:
	Groggle();
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
		board = Board(4,4,"exampleboard.txt");
	}
private:
	WordList words;
	Board board;
};
