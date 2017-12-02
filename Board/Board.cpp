#include "Board.h"

Board::Board(const int newBoardWidth, const int newBoardHeight) : dist_board(0, (newBoardWidth * newBoardHeight) - 1) , dist_side(0, DIESIDES - 1) , dist_letters(0.0, 100.0) ,//Inits board 
likelihoods{ 8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03, 5.92, 7.31, .10, .69, 3.98, 2.61, 6.95, 7.68, 1.82, .11, 6.02, 6.28, 9.10, 2.88, 1.11, 2.09, .17, 2.11, .07 }
{
	//Chrono usage from cplusplus
	rand.seed((int) std::chrono::system_clock::now().time_since_epoch().count());

	//Resizes board and initializes letters to spaces
	resizeBoard(newBoardWidth, newBoardHeight);

	//We need enough dice to fill up the whole board
	dice.resize(BOARDSIZE);

	//Gets proper number of dice and dice distribution based on boardSize
	resetDice();
}

//File and string constructors for debugging the word finder
//Since there's no way to have two constructors for two types of strings... it takes a mode also
Board::Board(const int newBoardWidth, const int newBoardHeight, const string & s, const loadMode & mode) //combo string constructor and file constructor
{
	//Default constructor should always be called!
	*this = Board(newBoardWidth, newBoardHeight);
	string newBoard = s;

	//This one is pretty much for debugging
	if (mode == loadMode::FILEMODE)
	{
		ifstream file(s);
		getline(file, newBoard);
	}

	//Must be the proper length, if not the program would be dunksis
	if (!setBoard(newBoard))
	{
		//If string was the wrong size just give them a random board
		cout << "Wrong number of letters, randomizing board instead..." << endl;
		this->randomize();
	}
}

Board::~Board()
{

}

//Sets the letters board to a string value - used by string constructors
bool Board::setBoard(const string & s)
{
	if (s.size() == (unsigned int) BOARDSIZE)
	{
		//Board successfully initialized
		auto it = s.begin();
		for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth ; j++)
		{
			board[i][j] = *(it++);
		}
		return true;
	}
	else
	{
		//Wrong string length
		return false;
	}
}

//Resizes and wipes board
void Board::resizeBoard(const int newBoardWidth, const int newBoardHeight)
{
	//Initializes board width and height
	boardWidth  = newBoardWidth;
	boardHeight = newBoardHeight;

	//Actually resizes board
	//Resizes column to be height tall
	board.resize(newBoardHeight);

	//Resizes every row in the board
	for (int i = 0; i < newBoardWidth; i++)
	{
		board.at(i).resize(newBoardWidth);
	}

	resetDice();

	//Initializes every square on the board to space... a bit dangerous, and not really necessary
	for (int i = 0; i < newBoardHeight; i++)
	for (int j = 0; j < newBoardWidth ; j++)
		board[i][j] = ' ';

	//Reconstructs the random board position object
	dist_board = std::uniform_int_distribution<int>(0,BOARDSIZE - 1);
}

void Board::resetDice(void)
{
	//Now there have to be boardSize dice
	dice.resize(BOARDSIZE);

	//Initializes all the dice. MIGHT be a better way to do this
	//These are the official BOGGLE 4x4 board dice
	if (boardWidth == 4 && boardHeight == 4)
	{
		dice[0]  = { 'a', 'e', 'a', 'n', 'e', 'g' };
		dice[1]  = { 'a', 'h', 's', 'p', 'c', 'o' };
		dice[2]  = { 'a', 's', 'p', 'f', 'f', 'k' };
		dice[3]  = { 'o', 'b', 'j', 'o', 'a', 'b' };
		dice[4]  = { 'i', 'o', 't', 'm', 'u', 'c' };
		dice[5]  = { 'r', 'y', 'v', 'd', 'e', 'l' };
		dice[6]  = { 'l', 'r', 'e', 'i', 'x', 'd' };
		dice[7]  = { 'e', 'i', 'u', 'n', 'e', 's' };
		dice[8]  = { 'w', 'n', 'g', 'e', 'e', 'h' };
		dice[9]  = { 'l', 'n', 'h', 'n', 'r', 'z' };
		dice[10] = { 't', 's', 't', 'i', 'y', 'd' };
		dice[11] = { 'o', 'w', 't', 'o', 'a', 't' };
		dice[12] = { 'e', 'r', 't', 't', 'y', 'l' };
		dice[13] = { 't', 'o', 'e', 's', 's', 'i' };
		dice[14] = { 't', 'e', 'r', 'w', 'h', 'v' };
		dice[15] = { 'n', 'u', 'i', 'h', 'm', 'q' };
	}
	//These are the official BIG BOGGLE 5x5 dice
	else if (boardWidth == 5 && boardHeight == 5)
	{
		dice[0]  = { 'a', 'a', 'a', 'f', 'r', 's'};
		dice[1]  = { 'a', 'a', 'e', 'e', 'e', 'e'};
		dice[2]  = { 'a', 'a', 'f', 'i', 'r', 's'};
		dice[3]  = { 'a', 'd', 'e', 'n', 'n', 'n'};
		dice[4]  = { 'a', 'e', 'e', 'e', 'e', 'm'};

		dice[5]  = { 'a', 'e', 'e', 'g', 'm', 'u'};
		dice[6]  = { 'a', 'e', 'g', 'm', 'n', 'n'};
		dice[7]  = { 'a', 'f', 'i', 'r', 's', 'y'};
		dice[8]  = { 'b', 'j', 'k', 'q', 'x', 'z'};
		dice[9]  = { 'c', 'c', 'e', 'n', 's', 't'};

		dice[10] = { 'c', 'e', 'i', 'i', 'l', 't'};
		dice[11] = { 'c', 'e', 'i', 'l', 'p', 't'};
		dice[12] = { 'c', 'e', 'i', 'p', 's', 't'};
		dice[13] = { 'd', 'd', 'h', 'n', 'o', 't'};
		dice[14] = { 'd', 'h', 'h', 'l', 'o', 'r'};

		dice[15] = { 'd', 'h', 'l', 'n', 'o', 'r'}; 
		dice[16] = { 'd', 'h', 'l', 'n', 'o', 'r'};
		dice[17] = { 'e', 'i', 'i', 'i', 't', 't'};
		dice[18] = { 'e', 'm', 'o', 't', 't', 't'};
		dice[19] = { 'e', 'n', 's', 's', 's', 'u'};

		dice[20] = { 'f', 'i', 'p', 'r', 's', 'y'};
		dice[21] = { 'g', 'o', 'r', 'r', 'v', 'w'};
		dice[22] = { 'i', 'p', 'r', 'r', 'r', 'y'};
		dice[23] = { 'n', 'o', 'o', 't', 'u', 'w'};
		dice[24] = { 'o', 'o', 'o', 't', 't', 'u'};
	}
	//Calculated distribution
	//Actually generates a set of die instead of just plastering the board with a good distribution of letters. This one may be dangerous
	else
	{
		//A way of triggering the board randomizer to just randomize the board
		//dice[0] = { '0','0','0','0','0','0' };

		//Is & the way to do this?
		for (array<char, 6> & die : dice)
		{
			for (int i = 0; i < DIESIDES; i++)
			{
				//We'll see if this works
				die.at(i) = getLetter(dist_letters(rand));
			}
		}
	}
}

//Returns copy of foundWords
vector<string> Board::getFoundWords(void) 
{
	return foundWords;
}

//Randomly shakes up the dice
void Board::randomize(void)
{
	vector<int> randomArr;
	randomArr.resize(BOARDSIZE);

	//Populates an sequential array with 0-boardSize
	for (int i = 0; i < BOARDSIZE; i++)
		randomArr[i] = i;

	//Randomly orders the boardSize numbers
	for (int i = 0; i < BOARDSIZE; i++)
		{
			std::swap(randomArr.at(dist_board(rand)), randomArr.at(i));
		}

	int j = 0;
	//Use this ordering to place the blocks in the board, random side up
	for (int i : randomArr)
	{
		//Goes to a random position and places the dice in order, random side up
		board[i / boardHeight][i % boardWidth] = dice.at(j++).at(dist_side(rand));
	}
}

//Prints the board to the screen. Will be removed in curses version
void Board::print(void)
{
	for (int i = 0; i < boardHeight; i++)
	{
		cout << " ";
		for (int j = 0; j < boardWidth; j++)
		{
			cout << lineBreak;
		}
		cout << "-" << endl << space;
		for (int j = 0; j < boardWidth; j++)
		{
			if (board[i][j] != 'q')
				cout << (char)toupper(board[i][j]) << space;
			else
				cout << "Qu" << qSpace; //a little sloppy
		}
		cout << endl;
	}
	cout << " ";
	for (int j = 0; j < boardWidth; j++)
	{
		cout << lineBreak;
	}
	cout << "-" << endl;
}

//Recursively checks the entire board to find all words
vector<string> Board::findWords(const WordList & words)
{
	//Resets foundWords if this isn't the first board
	foundWords.clear();

	string s;
	vector<vector<bool>> nullBoard;

	//Sets height of nullBoard
	nullBoard.resize(boardHeight);

	//Sets width of each row
	for (int i = 0; i < boardHeight; i++)
	{
		nullBoard.at(i).resize(boardWidth);
	}

	for (int i = 0; i < boardWidth ; i++)
	for (int j = 0; j < boardHeight; j++)
		nullBoard[i][j] = false;

	//Needs to make every possible permutation through the board and check them against the hash table
	//There is probably a way to short circuit stupid paths but I don't know how to do that UPDATE: I DID IT
	for (int i = 0; i < boardWidth ; i++)
	for (int j = 0; j < boardHeight; j++)
	{
		//Need to make boardHeight * boardWidth recursive calls. since you can start from any position on the board
		//This for loop is needed. can't use recursion for everything
		findWordsFromPos(nullBoard, i, j, s, words);
	}

	//All strings found, return them
	return foundWords;
}

//Sort words from longest to shortest
void Board::sortWords()
{	
	//sort alphabetically, then by length
	std::sort(foundWords.begin(), foundWords.end(), [] (const string &lhs, const string &rhs)
	{
		if (lhs.length() == rhs.length())
			return lhs < rhs;
		else
			return lhs.length() > rhs.length();
	});
}

//Remove in curses version
void Board::printWords()
{
	if (foundWords.size() > 0)
	{
		for (string word : foundWords)
		{
			std::transform(word.begin(), word.end(), word.begin(), ::toupper);
			cout << word << endl;
		}
		cout << "Number of words found: " << foundWords.size() << endl;
	}
	else
		cout << "Words have not been found yet or this board really has no words..." << endl;
}

//PRIVATE FUNCTIONS - don't look

//Hopefully the stack is okay. Called BOARDSIZE times by findWords
void Board::findWordsFromPos(vector<vector<bool>> & nullBoard, const int i, const int j, string & s, const WordList & words)
{
	//Check if recursive call is in the bounds of the board AND if the letter hasn't been used yet
	//if (i >= 0 && i < boardHeight && j >= 0 && j < boardWidth && nullBoard[i][j] == false) TOO SLOW, moved this to the for loop

	if (s.size() < SHORT || !words.shortCircuit(s)) //quits if going down a stupid path
	{
		s += board[i][j]; //add letter to current word
		if (board[i][j] == 'q')
			s += 'u'; //adds the bonus u attached to qs
		//nullboard stops recursion from using a letter more than once
		nullBoard[i][j] = true;

		//If the word is in the wordList hash table, add it to the newWords list
		if (words.has(s))
		{
			//cout << s << endl;
			if (s.length() >= 3 && find(foundWords.begin(), foundWords.end(), s) == foundWords.end() )
			{
				//cout << s << endl;
				foundWords.push_back(s);
			}
		}

		//Recursion time - moves to all 9 surrounding letters
		//These will all happen while the current letter is blocked off
		for (int k = i - 1; k <= i + 1; k++)
		for (int l = j - 1; l <= j + 1; l++)
		if (k >= 0 && k < boardWidth && l >= 0 && l < boardHeight && nullBoard[k][l] == false) //don't do recursive calls unless we have to
			findWordsFromPos(nullBoard, k, l, s, words);

		//Backs up a letter to go somewhere else
		s.erase(s.length() - 1);
		//Case for removing both letters of q and u combo
		if (s.length() > 0 && s.at(s.length() - 1) == 'q')
		{
			//cout << "q alert" << endl;
			s.erase(s.length() - 1);
		}

		nullBoard[i][j] = false;
	}
	else return;
}

//Precondition: takes a random number from 0.0 to 100.0 and returns a character based on letter distribition
//I should probably write good test code for this function, although if generates all letters and not just 'a' or 'z' it's probably right
char Board::getLetter(double randNum)
{
	double distribution = 0.0;
	char c = 'z';
	//Pretty cool alogithm if I do say so myself. Adds number frequencies in order until it hits the number passed in, then returns the corresponding character
	//Should return a 1:1 distribution of the English letters
	for (c = 'a'; c <= 'z' && distribution < randNum; c++)
	{
		//Likelihoods is a member 
		distribution += likelihoods[c - 'a'];
	}
	return c;

	//The only problem with this method is caused by 'Q' having 'u' built into it, which disproportionately increases the likelihood of 'u' appearing
	//Solutions? Figure out later
}