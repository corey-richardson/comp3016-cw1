#ifndef STANDARD_TILE_H
#define STANDARD_TILE_H

#include "Tile.h"

class StandardTile : public Tile
{
public:
	StandardTile(TileType type);

	using Tile::tileTypeToChar;

	bool isWalkable() const override;
	bool updateStateOnExit() override;
};

#endif
