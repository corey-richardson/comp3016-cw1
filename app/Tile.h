#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <map>

/* TODO:
Convert Tile to an abstract class
Then,

StandardTile : public Tile
MultiVisitTile : public Tile

This demonstrates polymorphism!
*/

// https://www.geeksforgeeks.org/cpp/virtual-base-class-in-c/

enum class TileType {
	Void,
	Walkable,
	Start,
	End,
	Visited,
	Invalid,
	MultiVisit,
};

class Tile {
protected:
	TileType type;
	Tile(TileType type = TileType::Invalid) : type(type) {}

public:
	virtual ~Tile() = default;

	TileType getType() const {
		return this->type;
	}

	virtual char tileTypeToChar(TileType type) const;

	/* '= 0' notates the methods that a derived class MUST override a virtual method
	Pure Virtual */
	virtual bool isWalkable() const = 0;
	virtual bool updateStateOnExit() = 0;
};

#endif
