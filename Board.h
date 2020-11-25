#pragma once
#include<vector>
class Tile;

class Board
{
private:
	Tile** board;
	unsigned int height, width;
	int uncleared_tiles; // track how many tiles are unrevealed and unmined for victory condition
	Board(const Board& old); //make it impossible to copy a board. Always use const reference.
	Board* operator= (const Board& old);
	std::vector<Tile*> get_adj_tiles(unsigned int x, unsigned int y);

public:
	Board(const unsigned int h, const unsigned int w, const unsigned int mines);
	~Board();
	bool get_mine(int x, int y) const;
	bool get_reveal(int x, int y) const;
	bool get_flag(int x, int y) const;
	int get_adj_mines(int x, int y) const;
	int get_board_height() const;
	int get_board_width() const;
	int get_uncleared_tiles() const;
	void reveal(int x, int y);
	void decrement_uct();
	void flag(int x, int y);
	void place_mine(int x, int y);
};

