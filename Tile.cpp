#include "Tile.h"
#include "Board.h"
#include <vector>

void Tile::fill_adj_tiles(std::vector<Tile*> vec)
{
	adj_tiles = vec;
}
//Get Methods:
bool Tile::has_mine() const
{
	return contains_mine;
}
bool Tile::is_revealed() const
{
	return revealed;
}
bool Tile::is_flagged() const
{
	return flagged;
}
int Tile::get_adj_mine_count() const
{
	return adj_mines;
}
//Set Methods:
void Tile::toggle_flag()
{
	if (!revealed)
		flagged = !flagged; //standard bool toggle
}
void Tile::reveal(Board& board)
{
	if (!revealed)
	{
		revealed = true;
		flagged = false;
		board.decrement_uct();
		if (adj_mines == 0)
		{
			for (auto& tile : adj_tiles)
			{
				tile->reveal(board);
			}
		}
	}
}
void Tile::place_mine()
{
	contains_mine = true;
	for (auto& tile : adj_tiles)
	{
		tile->adj_mines++;
	}
}
