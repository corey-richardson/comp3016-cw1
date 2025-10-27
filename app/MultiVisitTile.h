#ifndef MULTI_VISIT_TILE_H
#define MULTI_VISIT_TILE_H

#include "Tile.h"

class MultiVisitTile : public Tile
{
public:
	MultiVisitTile(TileType type, int numAllowedVisits);

	bool isWalkable() const override;
	void updateStateOnExit() override;

	char tileTypeToChar(TileType type) const override;

private:
	int remainingVisits;
};

#endif
