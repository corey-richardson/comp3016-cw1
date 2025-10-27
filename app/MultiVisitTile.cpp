#include "MultiVisitTile.h"

MultiVisitTile::MultiVisitTile(TileType type, int numAllowedVisits)
	: Tile(type), remainingVisits(numAllowedVisits) {
	// Nothing to do
}


bool MultiVisitTile::isWalkable() const {
	return this->remainingVisits > 0;
}


void MultiVisitTile::updateStateOnExit() {
	if (this->remainingVisits > 0) {
		this->remainingVisits--;
	}
}


char MultiVisitTile::tileTypeToChar(TileType type) const {
	if (this->remainingVisits == 0) {
		return '*';
	}

	// Else,
	return static_cast<char>(this->remainingVisits);
}
