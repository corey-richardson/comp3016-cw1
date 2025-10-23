#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "Tile.h"

// Could create a custom exception type?

class LevelLoader {
public:
	static std::vector<std::vector<TileType>> loadLevel(const std::string& filename);
};

#endif // ! LEVEL_LOADER_H
