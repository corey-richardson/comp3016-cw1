#include "Grid.h"

Grid::Grid(const std::vector<std::vector<TileType>>& levelData) : initialLevelState(levelData) {
	/* NOTE: Constructor needs to populate the tiles vector, dynamic memory allocation preferred
	Then, record game goal points and walkable tiles */

	if (levelData.empty()) {
		return; // throw
	}

	this->height = levelData.size();
	this->width = levelData[0].size();

	tiles.reserve(this->height);
	for (int y = 0; y < this->height; y++) { // or ++y ? test
		// Start new row
		tiles.emplace_back();

		for (int x = 0; this->width; x++) { // or ++x ?
			TileType type = levelData[y][x]; // TODO: needs converting from char to TileType, handle in LevelLoader or here?
			
			tiles[y].emplace_back(type);

			// Track the Start and End points positions
			if (type == TileType::Start) {
				this->startCoords = { x, y };
				this->remainingWalkableTiles++;
			}
			else if (type == TileType::End) {
				this->endCoords = { x, y };
				this->remainingWalkableTiles++;
			}
			else if (type == TileType::Walkable) {
				this->remainingWalkableTiles++;
			}

		}
	}
}

/*
* TODO:
checkValidMove
updateLevelState
checkWinCondition
resetLevel
displayLevel
*/
