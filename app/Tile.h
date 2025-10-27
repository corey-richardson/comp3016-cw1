#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <map>

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


/**
* @brief Base abstract class representing a tile within the game Grid
*/
class Tile {
protected:
	TileType type;
	Tile(TileType type = TileType::Invalid) : type(type) {}

public:
	/**
	* @brief Virtual destructor for safe polymorphic cleanup
	*/
	virtual ~Tile() = default;

	/**
	* @brief Getter method to retrieve the base TileType
	* @return The TileType of this Tile
	*/
	TileType getType() const {
		return this->type;
	}

	/**
	* @brief Convert a TileType to a display character
	* @param type The TileType to convert
	* @return A character representing the Tile visually
	*/
	virtual char tileTypeToChar(TileType type) const;

	/* '= 0' notates the methods that a derived class MUST override a virtual method
	Pure Virtual */

	/**
	* @brief Determine whether the Tile can be moved to.
	*
	* Pure Virtual - must be overriden by derived class
	* @return True if the Tile permits movement, else false
	*/
	virtual bool isWalkable() const = 0;

	/**
	* @brief Update the Tile state when the player leaves it.
	*
	* Pure Virtual - must be overriden by derived class
	* @return True if the update succeeded, else false
	*/
	virtual bool updateStateOnExit() = 0;
};

#endif
