#include <iostream>
#include <map>

/* TODO:
Convert Tile to an abstract class
Then,

StandardTile : public Tile
MultiVisitTile : public Tile

This demonstrates polymorphism!
*/

enum class TileType {
	Void,
	Walkable,
	Start,
	End,
	Visited,
	Invalid,
};

class Tile {

private:
	TileType type;

public:
	Tile(TileType type = TileType::Invalid) : type(type) {}

	TileType getType() const {
		return this->type;
	}


	static char tileTypeToChar(TileType type) {
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


	void setType(TileType newType) {
		this->type = newType;
	}


	bool isWalkable() const {
		return (this->type == TileType::Walkable ||
				this->type == TileType::Start ||
				this->type == TileType::End
		);
	}
};
