#include "LevelLoader.h"

/**
* @brief Loads and parses a level from a file into a 2D vector of TileTypes
* @param filename The path to the level (blueprint?) file
* @return levelData A 2D vector of TileTypes
* @throws LevelLoadException
* 1. The file cannot be opened
* 2. File contains invalid characters that can't be parsed
* 3. File line have inconsistent lengths
*/
static std::vector<std::vector<TileType>> loadLevel(const std::string& filename) {
	std::ifstream file(filename); // ios::in

	if (!file.is_open()) {
		throw LevelLoadException("Failed to open level file: " + filename); // Change to custom exception type
	}

	std::vector<std::vector<TileType>> levelData;

	std::string line;
	int lineLength = -1;

	try {
		while (std::getline(file, line)) {
			std::vector<TileType> row;

			// Skip empty lines
			if (line.empty()) {
				continue; 
			}

			for (char c : line) {
				TileType type = Tile::charToTileType(c);

				if (type == TileType::Invalid) {
					// https://stackoverflow.com/questions/17201590/how-can-i-create-a-string-from-a-single-character
					// anonymous string conversion woah
					throw LevelLoadException("Failed to parse character '" + std::string(1, c) + " into a Tile.");
				}

				row.push_back(type);
			}

			// Skip empty lines
			if (row.empty()) {
				continue;
			}

			if (lineLength == -1) { // First line with data
				lineLength = row.size();
			}
			else if (row.size() != lineLength) {
				throw LevelLoadException("Inconsistent line length in level file " + filename);
			}

			levelData.push_back(row);
		}
	}
	// https://en.cppreference.com/w/cpp/language/catch.html
	catch (...) {
		file.close();
		throw; // Bubble up
	}

	// Resource cleanup BEFORE level data check
	file.close();

	// No valid level data?
	if (levelData.empty()) {
		throw LevelLoadException("File contained no level setup data.");
	}

	return levelData;
}
