#include "MultiVisitTile.h"

MultiVisitTile::MultiVisitTile(TileType type, int numAllowedVisits)
	: Tile(type), remainingVisits(numAllowedVisits) {
	// Nothing to do
}


bool MultiVisitTile::isWalkable() const {
	return this->remainingVisits > 0;
}


bool MultiVisitTile::updateStateOnExit() {
	if (this->remainingVisits > 0) {
		this->remainingVisits--;
		return true;
	}
	return false;
}


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
