#include "MultiVisitTile.h"

/**
* @brief Constructs a MultiVisitTile of given type.
* @param type The TileType of the Tile
* @param numAllowedVisits The number of times a tile can be stepped on. 
* Defaulted to 2 in header file.
*/
MultiVisitTile::MultiVisitTile(TileType type, int numAllowedVisits)
	: Tile(type), remainingVisits(numAllowedVisits) {
	// Nothing to do
}


/**
* @brief Determine whether the Tile can be moved to.
* Overrides the pure virtual method Tile::isWalkable.
* @return True if the Tile has remaining visits, else false
*/
bool MultiVisitTile::isWalkable() const {
	return this->remainingVisits > 0;
}


/**
* @brief Update the Tile state when the player leaves it.
* Overrides the pure virtual method Tile::updateStateOnExit.
* Decrements the number of remaining visits for the Tile if gt zero.
* @return True if the update succeeded (remainingVisits decremented), else false
*/
bool MultiVisitTile::updateStateOnExit() {
	if (this->remainingVisits > 0) {
		this->remainingVisits--;
		return true;
	}
	return false;
}


/**
* @brief Converts a TileType value to its corresponding display character
* * Overrides the method Tile::tileTypeToChar.
* @return type The TileType object that is to be converted to a display character; should be TileType::MultiVisit
* @params A character representing the given TileType, depending on remainingVisits
*/
char MultiVisitTile::tileTypeToChar(TileType type) const {
	switch (this->remainingVisits) {
		case (2):
			return '2';
		case (1):
			return '1';
		case (0):
			return '*';
		default:
			return '+';
	}
}
