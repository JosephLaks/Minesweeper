#pragma once
#include<vector>
class Board;

class Tile
{
private:
	bool has_mine = false, revealed = false, flagged = false;
	int adj_mines = 0;
	std::vector<Tile*> adj_tiles;
public:

	void fill_adj_tiles(std::vector<Tile*> vec);
	bool get_mine() const;
	bool get_reveal() const;
	bool get_flag() const;
	int get_adj_mines() const;
	void toggle_flag();
	void reveal(Board& board);
	void place_mine();
};

