#include "Groggle.h"

Groggle::Groggle() : words(), board(4,4)
{

}

void Groggle::runApp(void)
{
	string s;
	char c;
	int choice;

	int newDim = 0;

	//Default Board
	board = Board(4,4);

	//menu
	while (true)
	{	
		cout << "BOGGLE START PLAYING YA GUNKUS" << endl;
		cout << "1) Play and Solve" << endl; //this will be different with curses
		cout << "2) Boggle Rules" << endl;
		cout << "3) Generate Board" << endl;
		cout << "4) Solve Board" << endl;
		cout << "5) Dictionary Search" << endl;
		cout << "6) Dictionary Insert" << endl;
		cout << "7) Resize Board" << endl;
		cout << "8) Exit" << endl;
		cout << "Enter your choice: ";
		cin >> s;
		try { choice = stoi(s); } //still crashes when you type garbage fix this
		catch (exception) {}

		//Use choice
		switch (choice)
		{
		case 1: //the game
			playGame();
			break;
		case 2: //the rules
			break;
		case 3:
			randomizeBoard();
			printBoard();
			break;
		case 4:
			cout << "Type in the letters of the board in the order they appear (type l for last board):" << endl;
			if (s != "l")
			{
				cin >> s;
				board.setBoard(s);
			}
			board.print();
			board.findWords(words);
			board.sortWords();
			board.printWords();
			break;
		case 5:
			cout << "Type a word to find in the dictionary: " << endl;
			cin >> s;
			if (words.has(s.c_str()))
			{
				cout << "Congrats, \"" << s << "\" is an official Groggle word!" << endl;
			}
			else
			{
				cout << "Sorry that word is not recognized" << endl;
				cout << "Would you like to add it? (y/n)" << endl;
				cin >> c;
				if (c == 'y' || c == 'Y')
					words.insert(s.c_str());
			}
			break;
		case 6:
			cout << "Type your custom word:" << endl;
			cin >> s;
			words.insert(s.c_str());
			break;
		case 7:
			cout << "Enter new board dimension (NxN): ";
			cin >> newDim;
			board.resizeBoard(newDim, newDim);
			cout << "Board resized to " << std::to_string(newDim) << " x " << std::to_string(newDim) << endl;
			break;
		case 8:
			return;
			break;
		default:
			cout << "Invalid selection what the heck dude" << endl;
			break;
		}
	}
}

void Groggle::playGame(void)
{
	randomizeBoard();
	//loadBoard();
	printBoard();
	//times findWords function
	timeStart();
	this->board.findWords(this->words);
	this->board.sortWords();
	this->board.printWords();
	timeStop();
}

//the dictionary I downloaded was a pile
//THIS CODE IS ROCKIN WORKED FIRST TRY
void cleanDictionary(void)
{
	ifstream infile("Board/cleanBoggle2.txt");
	ofstream outfile("Board/cleanBoggle3.txt");
	string s;
	while (!infile.eof())
	{
		infile >> s;
		string::iterator it = s.begin();
		//string::iterator it = find(s.begin(), s.end(), '\'');
		while (it != s.end())
		{
			if (*it != tolower(*it))
			{
				break;
			}
			// if (!isalpha(*it))
			// {
			// 	break;
			// }
			it++;
		}

		if (it == s.end()) //does not contain an apostrophe
		{
			outfile << s << endl;
		}
		else
		{
			cout << "skipping " << s << endl;
		}
	}
} //now just need to get rid of all those stupid roman numerals

// void clearScreen(void) //won't need this with curses
// {
// 	for (int i = 0; i < 10; i++)
// 	{
// 		cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
// 	}
// }
