#include "StandardTile.h"

StandardTile::StandardTile(TileType type) : Tile(type) {
	// Nothing to do
}


bool StandardTile::isWalkable() const {
	return (
		this->type == TileType::Walkable ||
		this->type == TileType::Start ||
		this->type == TileType::End
	);
}


void StandardTile::updateStateOnExit() {
	if (this->type == TileType::Walkable) {
		this->type = TileType::Visited;
	}
}
