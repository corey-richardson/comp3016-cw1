#include "Grid.h"
#include "StandardTile.h"
#include "MultiVisitTile.h"
#include "LevelLoader.h"

/**
* @brief A factory method to create a new Tile instance based on the given type
* 
* Allocates memory based on the derived type:
* 
* - MultiVisitTile for TileType::MultiVisit
* 
* - StandardTile as a default
* 
* Method is extensible for future TileTypes, ie TrapTiles?
* 
* Grid destructor handles memory deallocation for Tile object
* 
* @param type The TileType indicating which type of derived Tile to create
* @return A pointer to the allocated Tile object.
*/
std::unique_ptr<Tile> Grid::createNewTile(TileType type) {
	// TODO: Update to use a smart pointer; improves memory safety
	// https://learn.microsoft.com/en-us/cpp/cpp/smart-pointers-modern-cpp?view=msvc-170
	if (type == TileType::MultiVisit) {
		return std::make_unique<MultiVisitTile>(type, 2);
	}
	else {
		return std::make_unique<StandardTile>(type);
	}
}


/**
* @brief Constructs a Grid object from a 2D vector of TileType enum values. 
* 
* Dynamically allocates memory for Tile objects for each position in the level.
* 
* Populates the 2D tiles member vector.
* 
* Records and counts:
* 
* - `startCoords` for the starting tile
* 
* - `endCoords` for the goal tile
* 
* - `remainingWalkableTiles` to track how many walkable visits remain for the win condition
* 
* @param levelData A 2D vector of TileType values representing a level
* @throw LevelLoadException on empty LevelData or missing Start or End Coords
*/
Grid::Grid(const std::vector<std::vector<TileType>>& levelData) : initialLevelState(levelData) {
	/* NOTE: Constructor needs to populate the tiles vector, dynamic memory 
	allocation is preferred
	Then, record game goal points and walkable tiles */

	if (levelData.empty() || levelData[0].empty()) {
		throw LevelLoadException("Level data is empty or invalid!");
	}

	this->height = static_cast<int>(levelData.size());
	this->width = static_cast<int>(levelData[0].size());

	tiles.reserve(this->height);

	for (size_t y = 0; y < this->height; ++y) { // ++y avoids unnecassary copies
		// Start new row
		tiles.emplace_back();

		for (size_t x = 0; x < this->width; ++x) {
			TileType type = levelData[y][x];
			tiles[y].emplace_back(createNewTile(type));

			if (type == TileType::MultiVisit) {
				this->remainingWalkableTiles += 2;
			}
			else if (type == TileType::Walkable) {
				this->remainingWalkableTiles++;
			}
			else if (type == TileType::Start) {
				this->startCoords = { static_cast<int>(x), static_cast<int>(y) };
			}
			else if (type == TileType::End) {
				this->endCoords = { static_cast<int>(x), static_cast<int>(y) };
			}
		}
	}

	// Validate level, check Start and End Coords set
	if (this->getStartCoords().x == -1 || this->getEndCoords().x == -1) {
		throw LevelLoadException("Level failed to initialise: Missing either Start or End tile (Sentinel value check).");
	}
}


/**
* @brief Private helper method that checks a co-ordinate is within bounds of grid
* @param target A set of co-ordinates to validate
* @return True if the co-ordinates are valid, else false
*/
bool Grid::isInBounds(const Coords& target) const {
	return target.x >= 0 && target.x < this->width &&
		target.y >= 0 && target.y < this->height;
}


/**
* @brief Validates whether a move is allowed or is a game fail-condition
* 
* 1. Check move doesn't go out of bounds of the Grid based on width and height
* 
* 2. Checks that the move is to a Tile that isWalkable (not Void or Visited)
* 
* 3. Checks that the move isn't revisiting the Start Tile
* @param target The co-ordinate of the intended move
* @return True if the move is valid, else false
*/
bool Grid::isValidMove(const Coords& target) const {
	// 1
	if (!isInBounds(target)) {
		std::cerr << "Invalid Move: Out of bounds." << std::endl;
		return false;
	}

	const Tile* targetTile = tiles[target.y][target.x].get(); // Get returns a non-owning
															  // raw pointer. unique_ptr
															  // still handles lifecycle

	// 2
	if (!targetTile->isWalkable()) {
		std::cerr << "Invalid Move: Fell into the void or hit an already visited Tile." << std::endl;
		return false;
	}

	// 3
	// Can't revisit Start tile, unless this becomes an intended gameplay mechanic?
	if (targetTile->getType() == TileType::Start) {
		std::cerr << "Invalid Move: Can't revisit the Start Tile." << std::endl;
		return false;
	}

	return true;
}


/**
* @brief Updates the state of the Tile the player just moved away from
* @param previous The co-ordinate of the previously occupied tile
*/
void Grid::updateLevelState(const Coords& previous) {
	Tile* previousTile = this->tiles[previous.y][previous.x].get();
	if (previousTile->updateStateOnExit()) {
		this->decrementWalkableTiles();
	}

}


/**
* @brief Resets the Grid to its initial state for a level restart

* Recreates the tiles dynamically based on the `initialLevelState`.
* 
* Resets `remainingWalkableTiles` to its initial value to correctly track win conditions.
* 
*/
void Grid::reset() {
	this->tiles.clear();
	this->remainingWalkableTiles = 0;

	for (size_t y = 0; y < this->height; ++y) {
		// Start new row
		tiles.emplace_back();

		for (size_t x = 0; x < this->width; ++x) {
			TileType type = initialLevelState[y][x];

			tiles[y].emplace_back(createNewTile(type));

			if (type == TileType::MultiVisit) {
				this->remainingWalkableTiles += 2;
			}
			else if (type == TileType::Walkable) {
				this->remainingWalkableTiles++;
			}
		}
	}
}


/**
* @brief Check if the win conditions have been met
* 1. The currentPos matches the endCoords of the level
* 2. All walkable tiles have been visited
* @param currentPos The co-ordinate of the current position
* @return True if the win conditions have been reached, else guarding falses
*/
bool Grid::checkWinConditions(const Coords& currentPosition) {
	if (currentPosition == this->endCoords && this->getRemainingWalkableTiles() == 0) {
		return true; // Win
	}

	return false; // Not yet finished
}


/**
* @brief Prints the current state of the game grid to the console
*/
void Grid::display(const Coords& playerPostion) const {
	std::cout << "\n";

	for (size_t y = 0; y < this->height; ++y) {
		for (size_t x = 0; x < this->width; ++x) {
			char cell;

			if (x == playerPostion.x && y == playerPostion.y) {
				std::cout << "P" << " ";
				continue;
			}

			cell = tiles[y][x]->tileTypeToChar(tiles[y][x]->getType());
			std::cout << cell << " ";
		}
		std::cout << "\n";
	}
}
