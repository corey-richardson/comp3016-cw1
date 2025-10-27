#include "StandardTile.h"

/**
* @brief Constructs a StandardTile of given type.
* @param type The TileType of the Tile
*/
StandardTile::StandardTile(TileType type) : Tile(type) {
	// Nothing to do
}


/**
* @brief Determine whether the Tile can be moved to.
* Overrides the pure virtual method Tile::isWalkable.
* @return True if the Tile permits movement, else false
*/
bool StandardTile::isWalkable() const {
	return (
		this->type == TileType::Walkable ||
		this->type == TileType::Start ||
		this->type == TileType::End
	);
}


/**
* @brief Update the Tile state when the player leaves it.
* Overrides the pure virtual method Tile::updateStateOnExit.
* @return True if the update succeeded, else false
*/
bool StandardTile::updateStateOnExit() {
	if (this->type == TileType::Walkable) {
		this->type = TileType::Visited;
		return true;
	}
	return false;
}
