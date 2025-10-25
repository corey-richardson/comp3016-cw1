#include "PlayerCursor.h"

/**
* @brief Constructs a PlayerCursor for the provided Grid object
* @param grid A reference to the Grid object that the PlayerCursor will interact with
*/
PlayerCursor::PlayerCursor(Grid& grid) : grid(grid) {
	this->currentPosition = grid.getStartCoords();
}



/**
* @brief Caclulates the next target coordinates based on the movement direction
* @param direction The direction in which the cursor intends to move
* @return target The coordinates representing the new position
*/
Coords PlayerCursor::calculateTarget(Direction direction) const {
	Coords target = this->currentPosition;

	switch (direction) {

		case Direction::Up:
			target.y++;
			break;
		case Direction::Down:
			target.y--;
			break;

		case Direction::Right:
			target.x++;
			break;
		case Direction::Left:
			target.x--;
			break;
	}

	return target;
}


/**
* @brief Attempts to move the player cursor in the specified direction.
* Only moves if the update if the attempt is a valid move
* @param direction The direction in which the cursor should move
* @return True if the movement is a valid move, else false
*/
bool PlayerCursor::move(Direction direction) {
	Coords newPosition = calculateTarget(direction);
	if (!grid.isValidMove(newPosition)) {
		// Not a valid move
		return false;
	}

	grid.updateLevelState(this->currentPosition);
	this->currentPosition = newPosition;

	std::cout << "Player moved to (" << currentPosition.x << ", " << currentPosition.y << ")." << std::endl;
	return true;
}
