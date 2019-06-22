#pragma once

#include <vector>

struct Position {
	int lin, col;
};

class Ship {
public:
	Ship(unsigned int identifier, char symbol,
		Position position, char direction,
		size_t size);
	unsigned int id() const;	//returns identifier
	Position pos() const;		//returns position   
	char dir() const;			//returns direction  
	size_t size() const;		//returns size
	// ... OTHER METHODS
private:
	unsigned int identifier;	// ship id number
	// ... OTHER ATTRIBUTES AND/OR METHODS
};

class Board {
public:
	Board(size_t numLines = 10, size_t numColumns = 10);
	bool putShip(const Ship& s); //add ship to board, if possible
	// ... OTHER METHODS
private:
	bool canPutShip(Position pos, char dir, size_t size);
	size_t numLines, numColumns;
	vector<vector<int>> board;	// each element = ship id or ‐1   
	vector<Ship> ships;
	// ... OTHER ATTRIBUTES AND/OR METHODS
};