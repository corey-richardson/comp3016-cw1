#include "LevelLoader.h"

static std::vector<std::vector<TileType>> loadLevel(const std::string& filename) {
	std::ifstream file(filename); // ios::in

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open level file: " + filename); // Change to custom exception type
	}

	std::vector<std::vector<TileType>> levelData;

	std::string line;

	try {
		while (!file.eof()) {
			std::vector<TileType> row;

			for (char c : line) {
				TileType type = Tile::charToTileType(c);

				if (type == TileType::Invalid) {
					throw std::runtime_error("Failed to parse character to Tile: " + c);
				}

				row.push_back(type);
			}

			levelData.push_back(row);
		}
	}
	// https://en.cppreference.com/w/cpp/language/catch.html
	catch (...) {
		file.close();
		throw;
	}

	file.close();
	return levelData;
}
