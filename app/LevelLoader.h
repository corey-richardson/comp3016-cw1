#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "Tile.h"

class LevelLoadException : public std::runtime_error {
public:
	LevelLoadException(const std::string& message) : std::runtime_error("Level Load Error: " + message) {}
};

class LevelLoader {
public:
	static std::vector<std::vector<TileType>> loadLevel(const std::string& filename);
};

#endif // ! LEVEL_LOADER_H
