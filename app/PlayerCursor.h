#ifndef PLAYER_CURSOR_H
#define PLAYER_CURSOR_H

#include <iostream>
#include "Grid.h"

enum class Direction {
	Up,
	Down,
	Left,
	Right,
	Neutral,
};


class PlayerCursor {
private:
	Grid& grid;
	Coords currentPosition;

	Coords calculateTarget(Direction direction) const;

public:
	PlayerCursor(Grid& grid);
	bool move(Direction direction);
	
	Coords getCurrentPosition() const { return this->currentPosition; }
};

#endif
