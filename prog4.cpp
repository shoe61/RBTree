// Scott Schumacher, building on a file by Catherine Stringfellow
// File name:	prog4.cpp
// Description: ***********************************

#include <iostream>
#include "RBTree.h"
using namespace std;

void introMsg(int &);
/*Precond:	None
Postcond:	Displays introductory message and instructions for initiating the game
Checks		None*/

void getPlay(RBTree&, int*player1, int*player2, int[], int SIZE, int subscript);
/*Precond:  Tree and players' arrays are created
Postcond:	Alternately solicits plays from each player;
			Stores each player's plays in a dedicated array
			Adds each play as a node of the tree
Checks:		Ensures plays are valid: that is, 
			integers between 1 and 99 without repetition*/

void shoPlayrsTurns(int SIZE, int*, int*);

void countPoints(RBTree&, int SIZE, int*player1, int*player2, int &score1, int &score2);

void main()
{
	//get number of plays
	int numPlays = 0;
	introMsg(numPlays);
	const int SIZE = numPlays;

	//dynamically allocate arrays to hold each player's entries
	int *player1 = new int[SIZE];
	int *player2 = new int[SIZE];

	//instantiate a tree for the game
	RBTree gameTree;

	//for loop: for indicated number of turns, calls getPlay for each player			
	for (int i = 0; i < SIZE; i++)
	{
		
		getPlay(gameTree, player1, player2, player1, SIZE, i);
		gameTree.Insert(player1[i]);
	
		getPlay(gameTree, player1, player2, player2, SIZE, i);
		gameTree.Insert(player2[i]);
	}

	//print both players' plays (Needs players' arrays)
	shoPlayrsTurns(SIZE, player1, player2);
	gameTree.PrintTree();

	//print (and count) both players' leaves(points)(needs players' arrays and tree)
	int score1 = 0, score2 = 0;
	countPoints(gameTree, SIZE, player1, player2, score1, score2);


	system("pause");
}

void introMsg(int &plays)
{
	//heading for screen output
	cout << "Scott Schumacher\n";
	cout << "File Name: none\n";
	cout << "Description: Screen output, prog4, Red-Black Tree Game\n\n";


	//intro paragraph; explains game and asks a player to select a number of plays
	cout << "Thanks for playing Scott's Red-Black Tree Game. Here's how it works.\n";
	cout << "First, you'll have to decide how long a game you want to play by choosing the\n";
	cout << "depth of the tree. You may choose depths in a range from 1 to 6. The greater\n";
	cout << "the depth, the more turns each player gets- up to a point. Each player will, \n";
	cout << "in turn, play an integer between 1 and 100 to be added as a node to the tree.\n";
	cout << "The player who at the end of the game has the most leaf nodes wins the game.\n\n";
	
	cout << "Please enter the tree depth;\n";
	cout<<"Remember, you must select a depth between 1 and 6: ";
	
	int depth = NULL;
	cin >> depth;
	
	if ((depth<1) || (depth>6))
	{
		cout << "Sorry! You must choose a depth between 1 and 6. I'm outta here.";
		return;
	}
	
	else
	{
		//display the number of turns for each player
		cout << endl;
		cout << "You specified a depth of " << depth << ".\n";
		cout << "That means your tree will have " << depth + 1 << " levels, including the root.\n";
		cout << "Each player will have ";
		if (depth <= 5)
		{
			plays = (pow(2, depth) - 1);
		}
		else
		//depth of 6 would allow up to 63 turns per player, but limited by range (1-100)
		//to 49 turns per player, assuming computer plays the first number.
		{
			plays = 49;
		}
		cout << plays << " turns.\n\n";
	}
}

void getPlay(RBTree &gameTree, int*player1, int*player2, int playr[], int SIZE, int subscript)
{

	int play = NULL;


	if (playr == player1)
	{
		cout << endl << "Enter the number you want to play, Player One: ";
	}
	
	else
	{
		cout << endl << "Enter the number you want to play, Player Two: ";
	}
			
	cin >> play;
	cout << endl;

	if ((play< 1) || (play >100) || (gameTree.findItem(play)))
	{
		cout << "You must play a number between 1 and 100 that hasn't already been played.\n";
		getPlay(gameTree, player1, player2, playr, SIZE, subscript);
	}
	else
	{
		playr[subscript] = play;
	}
		
}

void shoPlayrsTurns(int SIZE, int *player1, int *player2)
{
	cout << endl << "Player One played: " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << player1[i] << ", ";
	}

	cout << endl << "Player Two played: " << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << player2[i] << ", ";
	}

	cout << endl << endl;
}

void countPoints(RBTree &gameTree, int SIZE, int *player1, int *player2, int &score1, int &score2)
{
	cout << endl << endl;

	//loop SIZE times; check to see if player one's moves are leaves
	cout << "Player One's leaf nodes: ";
	for (int i = 0; i < SIZE; i++)
	{
		gameTree.findItem(player1[i]);
		if (gameTree.HasNoChildren())
		{
			//increment player one's tally and list player one's leaves
			score1++;  
			cout << player1[i] << ", ";  
		}
	}

	cout << endl << "Player Two's leaf nodes: ";
	for (int i = 0; i < SIZE; i++)
	{
		gameTree.findItem(player2[i]);
		if (gameTree.HasNoChildren())
		{
			score2++;
			cout << player2[i] << ", ";
		}
	}

	//display scores and declare winner or tie game
	cout << endl << endl;
	cout << "Player One Score: " << score1 << endl;
	cout << "Player Two Score: " << score2 << endl;
	cout << endl;
	if (score1 > score2)
	{
		cout << "Player One wins.";
	}
	if (score1 < score2)
	{
		cout << "Player Two wins.";
	}
	if (score1 == score2)
	{
		cout << "The game is a tie.";
	}
		
	cout << endl << endl;
}
