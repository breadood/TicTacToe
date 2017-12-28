// TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const char EMPTY = ' ';
const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';
const int NUM_SQUARES = 9;

void displayBoard(const vector<char>& board);
bool isLegalMove(int move, const vector<char>& board);
int getHumanMove(const vector<char>& board);
int getComputerMove(vector<char>& board);
char getWinner(const vector<char>& board);

int main()
{
	vector<char> board(NUM_SQUARES, EMPTY);
	int humanMove, computerMove;
	char winner = NO_ONE, turn = O;
	displayBoard(board);

	while (winner == NO_ONE) {
		if (turn == O) {
			// update computer move
			computerMove = getComputerMove(board);
			board[computerMove] = O;
			displayBoard(board);
			turn = X;
		}
		else {
			// update human move
			humanMove = getHumanMove(board);
			board[humanMove] = X;
			displayBoard(board);
			turn = O;
		}
		winner = getWinner(board);
	}

	system("pause");
    return 0;
}

void displayBoard(const vector<char>& board)
{
	cout << endl;
	cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << "---------" << endl;
	cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "---------" << endl;
	cout << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << endl;
}

bool isLegalMove(int move, const vector<char>& board)
{
	if (move >= 0 && move < board.size()) {
		return board[move] == EMPTY;
	}
	return false;
}

int getHumanMove(const vector<char>& board)
{
	int move = -1;
	while (!isLegalMove(move, board)) {
		cout << "Where to move?" << endl;
		cin >> move;
	}
	return move;
}

int getComputerMove(vector<char>& board)
{
	// TODO: Make this faster!
	int move = 0;
	bool found = false;
	const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

	// search for winning move
	for (int i = 0; i < 8; ++i) {
		if (!found && isLegalMove(i, board)) {
			board[i] = O;
			if (getWinner(board) == O) {
				move = i;
				found = true;
			}
			board[i] = EMPTY;
		}
	}
	// search for losing move
	for (int i = 0; i < 8; ++i) {
		if (!found && isLegalMove(i, board)) {
			board[i] = X;
			if (getWinner(board) == X) {
				move = i;
				found = true;
			}
			board[i] = EMPTY;
		}
	}
	// best move possible
	for (int i = 0; i < 8; ++i) {
		if (!found && isLegalMove(BEST_MOVES[i], board)) {
			move = BEST_MOVES[i];
			found = true;
		}
	}
	return move;
}

char getWinner(const vector<char>& board)
{
	const int TOTAL_COMB = 8;
	const int WINNING_COMB[TOTAL_COMB][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 4, 8},
		{2, 4, 6}, 
		{0, 3, 6}, 
		{1, 4, 7}, 
		{2, 5, 8} 
	};

	// check if anyone wins
	for (int row = 0; row < TOTAL_COMB; ++row) {
		if ((board[WINNING_COMB[row][0]] != EMPTY) &&
			(board[WINNING_COMB[row][0]] == board[WINNING_COMB[row][1]]) &&
			(board[WINNING_COMB[row][1]] == board[WINNING_COMB[row][2]])) {
			return board[WINNING_COMB[row][0]];
		}
	}

	// check tie
	if (find(board.begin(), board.end(), EMPTY) == board.end()) {
		return TIE;
	}

	return NO_ONE;
}


