#pragma once
#include <iostream>

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
