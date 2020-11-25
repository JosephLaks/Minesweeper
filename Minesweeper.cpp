// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Board.h"
#include "Tile.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <string>

enum class action { reveal, flag, exit, cheat, none };

class User_Input
{
private:
	action player_action;
	int x, y;
	std::string x_in, y_in;
public:
	User_Input(const int board_width, const int board_height)
	{
		std::cout << "Enter an x coordinate and then a y coordinate:" << std::endl;
		std::cin >> x_in;
		std::cin >> y_in;
		try
		{
			x = std::stoi(x_in, nullptr, 10) % board_width;
		}
		catch (std::exception e)
		{
			x = x_in[0] % board_width;
		}
		try
		{
			y = std::stoi(y_in, nullptr, 10) % board_height;
		}
		catch (std::exception e)
		{
			y = y_in[0] % board_height;
		}
		do
		{
			std::cout << "Type 'r' to reveal the tile, or 'f' to flag it; to exit, press 'x':" << std::endl;
			char act;
			std::cin >> act;
			if (act == 'f')
				player_action = action::flag;
			else if (act == 'r')
				player_action = action::reveal;
			else if (act == 'e')
				player_action = action::exit;
			else if (act == 'c')
				player_action = action::cheat;
			else
				player_action = action::none;
		} while (player_action == action::none);
	}

	int get_x() const
	{
		return x;
	}
	int get_y() const
	{
		return y;
	}
	action get_player_action() const
	{
		return player_action;
	}
};

void print_board(const Board& board)
{
	std::cout << "    "; //Make sure things align
	for (int i = 0; i < board.get_board_width(); ++i) //column numbers
	{
		std::cout << ' ' << i;
		if (i < 10)
			std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < board.get_board_height(); ++i)
	{
		if (i < 10)
			std::cout << ' ';
		std::cout << i << ": "; //row numbers
		for (int j = 0; j < board.get_board_width(); ++j)
		{
			if (board[j][i].is_flagged())
				std::cout << "[f]";
			else if (!board[j][i].is_revealed())
				std::cout << "[ ]";
			else
				std::cout << '[' << board[j][i].get_adj_mine_count() << ']';
		}
		std::cout << std::endl;
	}
}

void reveal_board(const Board& board)
{
	std::cout << "    "; //Make sure things align
	for (int i = 0; i < board.get_board_width(); ++i) //column numbers
	{
		std::cout << ' ' << i;
		if (i < 10)
			std::cout << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < board.get_board_height(); ++i)
	{
		if (i < 10)
			std::cout << ' ';
		std::cout << i << ": "; //row numbers
		for (int j = 0; j < board.get_board_width(); ++j)
		{
			if (!board[j][i].has_mine())
				std::cout << "[" << board[j][i].get_adj_mine_count() << "]";
			else
			{
				if (board[j][i].is_revealed())
					std::cout << "[X]"; //Show user which mine they tripped
				else
					std::cout << "[M]";
			}
		}
		std::cout << std::endl;
	}

}

void print_defeat()
{
	std::cout << "Thou hast failed. The mines have ripped apart thine feeble body as though it were made of paper." << std::endl;
}
void print_victory()
{
	std::cout << std::endl << "Congragulations. Your ingenuity and indomitable will have triumphed. The minefield is cleared, and the way is free to advance further." << std::endl
		<< "Glory to the cause!!" << std::endl;
}

int main()
{
	const int width = 15;
	const int height = 15;
	const int num_mines = 5;

	Board board(height, width, num_mines);
	bool game_over = false;
	bool won = false;
	while (!game_over)
	{
		print_board(board);
		User_Input input(width, height);
		action act = input.get_player_action();
		switch (act)
		{
		case action::reveal:
			board[input.get_x()][input.get_y()].reveal(board);
			if (board[input.get_x()][input.get_y()].has_mine())
			{
				game_over = true;
				won = false;
			}
			break;
		case action::flag:
			board[input.get_x()][input.get_y()].toggle_flag();
			break;
		case action::exit:
			game_over = true;
			break;
		case action::cheat:
			reveal_board(board);
			break;
		default:
			break;
		}
		if (board.get_uncleared_tiles() == 0)
		{
			won = true;
			game_over = true;
		}
	}
	reveal_board(board);
	if (!won)
		print_defeat();
	else
		print_victory();
}

