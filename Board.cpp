#include "Board.h"
#include "Tile.h"
#include <vector>
#include <time.h>

std::vector<Tile*> Board:: get_adj_tiles(unsigned int x, unsigned int y)
{
	std::vector<Tile*> adj_tiles;
	adj_tiles.reserve(5); // most tiles have at least 5 neighbors
	if (x) //make sure not to go out of bounds
		adj_tiles.push_back(&board[y][x - 1]);
	if (y)
		adj_tiles.push_back(&board[y - 1][x]);
	if (x && y)
		adj_tiles.push_back(&board[y - 1][x - 1]);
	if ((x < (width - 1)) && y)
		adj_tiles.push_back(&board[y - 1][x + 1]);
	if (x < (width - 1))
		adj_tiles.push_back(&board[y][x + 1]);
	if ((x < (width - 1)) && (y < (height - 1)))
		adj_tiles.push_back(&board[y + 1][x + 1]);
	if (y < (height - 1))
		adj_tiles.push_back(&board[y + 1][x]);
	if (x && (y < height - 1))
		adj_tiles.push_back(&board[y + 1][x - 1]);

	return adj_tiles;
}

Board::Board(const unsigned int h, const unsigned int w, const unsigned int mines) : height(h), width(w), uncleared_tiles(w* h - mines)
{
	//generate the tiles
	board = new Tile * [h];
	for (unsigned int i = 0; i < height; ++i)
		board[i] = new Tile[width];
	//get the adjacent tiles for each tile
	for (unsigned int i = 0; i < height; ++i)
		for (unsigned int j = 0; j < width; ++j)
		{
			board[i][j].fill_adj_tiles(get_adj_tiles(j, i));
		}
	//generate the mines
	srand(time(0));
	int loc;
	for (unsigned int i = 0; i < mines; ++i)
	{
		loc = rand() % (height * width);
		board[loc / width][loc % width].place_mine();
	}
}

Board::~Board()
{
	for (unsigned int i = 0; i < height; ++i)
		delete[] board[i];
	delete[] board;
}

bool Board::get_mine(int x, int y) const
{
	return board[y][x].get_mine();
}
bool Board::get_reveal(int x, int y) const
{
	return board[y][x].get_reveal();
}
bool Board::get_flag(int x, int y) const
{
	return board[y][x].get_flag();
}
int Board::get_adj_mines(int x, int y) const
{
	return board[y][x].get_adj_mines();
}
int Board::get_board_height() const
{
	return height;
}
int Board::get_board_width() const
{
	return width;
}
int Board::get_uncleared_tiles() const
{
	return uncleared_tiles;
}

void Board::reveal(int x, int y)
{
	board[y][x].reveal(*this);
}
void Board::decrement_uct()
{
	--uncleared_tiles;
}
void Board::flag(int x, int y)
{
	board[y][x].toggle_flag();
}
void Board::place_mine(int x, int y)
{
	board[y][x].place_mine();
}
