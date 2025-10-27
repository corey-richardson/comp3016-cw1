#ifndef MULTI_VISIT_TILE_H
#define MULTI_VISIT_TILE_H

#include "Tile.h"

/**
* @brief Represents a Tile that can be visited multiple times on the game Grid.
* Publicly inherits from the Tile base class.
*/
class MultiVisitTile : public Tile
{
public:
	MultiVisitTile(TileType type, int numAllowedVisits = 2);

	bool isWalkable() const override;
	bool updateStateOnExit() override;

	char tileTypeToChar(TileType type) const override;

private:
	int remainingVisits;
};

#endif
