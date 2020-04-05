#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct players
{
	size_t points;
	char side;
	std::string name;
} p1, p2;

const std::size_t row = 3;
const std::size_t column = 3;

/**
Prints the current state of the gameboard.
@param char _board[row][column] : the char gameboard with row and column
*/
void printGameboard(char (&_board)[row][column]);

/**
Assigns X or O to the players.
@param char _token : the token that holds X or O
@param size_t _playerTurn : the random turn assigned to players
*/
void chooseToken(char &_token, size_t &_playerTurn);

/**
The game in action where Player 1 places a mark followed by PLayer 2
until a winner or draw is determined.
@param char _board[row][column] : the gameboard
@param char _token : the token holding X or O
*/
void playerMove(char(&_board)[row][column], char &_token, size_t &_playerTurn);

/**
Checks for a winner by iterating through rows, columns,
and diagonals.
@param char _board[row][column] : the gameboard
@param char _token : token holding X or O
@return true if there is a winner
*/
bool checkWinner(char(&_board)[row][column], char& _token);

/**
Checks for a full board and a draw.
@param char _board[row][column]
@return true if full board and false if not
*/
bool fullBoard(char(&_board)[row][column]);

int main() 
{
	std::size_t rounds;
	std::size_t playerTurn;

	std::cout << "This is a Tic Tac Toe game!\n";
	std::cout << "How many rounds would you like to play? ";
	std::cin >> rounds;
	while (!std::cin) {
		std::cout << "Enter a number of rounds: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> rounds;
	}

	std::cout << "\n";
	std::cout << "Please enter the name of Player 1: ";
	std::getline(std::cin, p1.name);
	while (!std::getline(std::cin, p1.name)) {
		std::cout << "Enter a proper name: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, p1.name);
	}

	std::cout << "\n";
	std::cout << "Thanks. Please enter the name of Player 2: ";
	std::getline(std::cin, p2.name);
	while (!std::getline(std::cin, p2.name)) {
		std::cout << "Enter a proper name: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, p2.name);
	}
	
	std::cout << "\n";
	std::cout << "Let the game begin!\n";
	char token;
	char board[row][column]{ {'1','2','3'},{'4','5','6'}, {'7','8','9'} };

	for (size_t n = 1; n <= rounds; ++n) 
	{
		printGameboard(board);
		chooseToken(token, playerTurn);
		playerMove(board, token, playerTurn);
	}

	std::cout << "\n" << "FINAL RESULT:\n";
	std::cout << "\n" << p1.name << " 's points: " << p1.points << "\n";
	std::cout << p2.name << " 's points: " << p2.points << "\n";

	if (p1.points > p2.points) 
	{
		std::cout << "\n" << p1.name << " wins the match!\n";
	}
	else if (p1.points < p2.points) 
	{
		std::cout << "\n" << p2.name << " wins the match!\n";
	}
	else 
	{
		std::cout << "\n" << "The match ended in a draw!";
	}
	return 0;
}

void printGameboard(char (&_board)[row][column]) 
{

	std::cout << "\n";
	std::cout << "\t " << _board[0][0] << "  | " << _board[0][1] << "  | " << _board[0][2] << "\n";
	std::cout << "\t-------------\n";
	std::cout << "\t " << _board[1][0] << "  | " << _board[1][1] << "  | " << _board[1][2] << "\n";
	std::cout << "\t-------------\n";
	std::cout << "\t " << _board[2][0] << "  | " << _board[2][1] << "  | " << _board[2][2] << "\n";
	std::cout << "\n";

}

void chooseToken(char &_token, size_t &_playerTurn) 
{

	char x = 'X';
	char o = 'O';

	std::cout << "\n";
	std::cout << "The first person to go is randomly chosen!\n";

	srand(time(NULL));
	size_t random = rand();

label:
	if (random % 2 == 0)
	{
		std::cout << p1.name << " goes first\n";
		_playerTurn = 1;
		std::cout << p1.name << ", pick X or O: ";
		std::cin >> _token;

		if (_token == 'X')
		{
			p1.side = x;
			p2.side = o;
			std::cout << p1.name << " is " << p1.side << " and " << p2.name << " is " << p2.side << "!\n";
		}
		else if (_token == 'O')
		{
			p1.side = o;
			p2.side = x;
			std::cout << p1.name << " is " << p1.side << " and " << p2.name << " is " << p2.side << "!\n";
		}
		else
		{
			std::cout << "Choose X or O.\n";
			goto label;
		}
	}
	else
	{
		std::cout << p2.name << " goes first\n";
		_playerTurn = 2;
		std::cout << p2.name << ", pick X or O: ";
		std::cin >> _token;

		if (_token == 'X')
		{
			p2.side = x;
			p1.side = o;
			std::cout << p2.name << " is " << p2.side << " and " << p1.name << " is " << p1.side << "!\n";

		}
		else if (_token == 'O')
		{
			p2.side = o;
			p1.side = x;
			std::cout << p2.name << " is " << p2.side << " and " << p1.name << " is " << p1.side << "!\n";

		}
		else
		{
			goto label;
		}
	}
}	

void playerMove(char(&_board)[row][column], char& _token, size_t& _playerTurn) 
{
	size_t prow;
	size_t pcolumn;

	printGameboard(_board);

	std::cout << "\n";
	std::cout << "It is Player " << _playerTurn << "'s turn\n";
	while (true)
	{
		std::cout << "\n" << "Where would you like to play? Enter your row position and column position: row col: ";
		std::cin >> prow;
		std::cout << " ";
		std::cin >> pcolumn;
		std::cout << "\n";

		if (_board[prow][pcolumn] != (p1.side && p2.side))
		{
			_board[prow][pcolumn] = _token;
			if (_token == p1.side)
			{
				_token = p2.side;
			}
			else
			{
				_token = p1.side;
			}
		}
		printGameboard(_board);
		std::cout << "\n";
		std::cout << "It is the next player's turn.";
		std::cout << "\n";

		if((checkWinner(_board, _token)) && (_token == p2.side))
		{
			std::cout << p1.name << " wins!\n";
			p1.points += 1;
			break;
		}
		else if((checkWinner(_board, _token)) && (_token == p1.side))
		{
			std::cout << p2.name << " wins!\n";
			p2.points += 1;
			break;
		}
		else if (fullBoard(_board)) {
			break;
		}
	}
	std::cout << "\n" << p1.name << " 's points: " << p1.points << "\n";
	std::cout << p2.name << " 's points: " << p2.points << "\n";
}

bool checkWinner(char(&_board)[row][column], char& _token) 
{
	size_t r, c;
	size_t ccount = 0;

	for (c = 0; c < 3; ++c)
	{
		for (r = 0; r < 3; ++r)
		{
			//rows WORKS
			if (_board[r][0] == _board[r][1] && _board[r][1] == _board[r][2])
			{
				return true;
			}
			//columns WORKS
			else if (_board[0][c] == _board[1][c] && _board[1][c] == _board[2][c])
			{
				return true;
			}

		}
	}
	//downwards diagonal
	if (_board[0][0] == _board[1][1] && _board[1][1] == _board[2][2])
		{
		std::cout << "downwards\n";
			return true;
		}
	//upwards diagonal
	else if (_board[0][2] == _board[1][1] && _board[1][1] == _board[2][0])
		{
			return true;
		}
	return false;
}

bool fullBoard(char(&_board)[row][column]) 
{
	std::cout << "Checking board..\n";
	for (size_t r = 0; r < 3; ++r) 
	{
		for (size_t c = 0; c < 3; ++c) 
		{
			if ((_board[r][c] != 'X') && (_board[r][c] != 'O')) {
				std::cout << "not full board";
				return false;
			}
		}
	}
	std::cout << "Draw!\n";
	return true;
}

