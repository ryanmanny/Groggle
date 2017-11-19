#include "Groggle.h"

void Groggle::runApp(void)
{
	//removed system() calls to prepare for port to curses

	string s;
	int choice;
	//menu
	while (true)
	{
		do {
			cout << "BOGGLE START PLAYING YA GUNKUS" << endl;
			cout << "1) play" << endl;
			cout << "2) the rules if I ever add them" << endl;
			cout << "3) generate board for pen and paper" << endl;
			cout << "4) exit" << endl;
			cout << "Enter your choice: ";
			cin >> s;
			try { choice = stoi(s); } //still crashes when you type garbage fix this
			catch (exception) {}
		} while (choice < 1 || choice > 4);

		//we now have a proper choice

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
			return;
			break;
		}
	}
}

void Groggle::playGame(void)
{
	//randomizeBoard();
	loadBoard();
	printBoard();
	//times findWords function
	timeStart();
	this->board.findWords(this->words);
	timeStop();
}
