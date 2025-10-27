#include "Tile.h"

/** 
* @brief Converts a TileType value to its corresponding display character
* @return type The TileType object that is to be converted to a display character
* @params A character representing the given TileType
*/
char Tile::tileTypeToChar(TileType type) const {
	switch (type) {
		case TileType::Void:
			return ' ';
		case TileType::Walkable:
			return '#';
		case TileType::Start:
			return 'S';
		case TileType::End:
			return 'E';
		case TileType::Visited:
			return '*';
		case TileType::Invalid:
		default:
			return '?';
	}
}
