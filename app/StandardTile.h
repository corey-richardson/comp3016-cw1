#ifndef STANDARD_TILE_H
#define STANDARD_TILE_H

#include "Tile.h"

/**
* @brief Represents a Standard Tile on the game Grid. 
* Publicly inherits from the Tile base class.
*/
class StandardTile : public Tile
{
public:
	StandardTile(TileType type);

	using Tile::tileTypeToChar;

	bool isWalkable() const override;
	bool updateStateOnExit() override;
};

#endif
