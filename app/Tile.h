#pragma once
#include <iostream>
#include <map>

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


	static TileType charToTileType(char c) {
		switch (c) {
			case '.':
			case ' ':
				return TileType::Void;
			case '#':
				return TileType::Walkable;
			case 'S':
				return TileType::Start;
			case 'E':
				return TileType::End;
			case '*':
				return TileType::Visited;
			case '?':
			default:
				return TileType::Invalid;
		}
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
