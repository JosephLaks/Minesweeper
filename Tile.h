#pragma once
#include<vector>
class Board;

class Tile
{
private:
	bool contains_mine = false, revealed = false, flagged = false;
	int adj_mines = 0;
	std::vector<Tile*> adj_tiles;
public:

	void fill_adj_tiles(std::vector<Tile*> vec);
	bool has_mine() const;
	bool is_revealed() const;
	bool is_flagged() const;
	int get_adj_mine_count() const;
	void toggle_flag();
	void reveal(Board& board);
	void place_mine();
};

