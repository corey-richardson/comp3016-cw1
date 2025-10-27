#include "RandomGame.h"

/**
* @brief Default constructor for the RandomGame class, using base Game class constructor
*/
RandomGame::RandomGame()
	: Game(),
	rng(std::chrono::system_clock::now().time_since_epoch().count())
{
}


/**
* @brief Overridden method to load the level manifest (using base) before shuffling the order
* @param levelManifestFilename The path to the Level Manifest file
*/
void RandomGame::loadLevelManifest(const std::string& levelManifestFilename) {
	Game::loadLevelManifest(levelManifestFilename);

	if (!this->levelFiles.empty()) {
		// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector Mehmet 
		std::shuffle(levelFiles.begin(), levelFiles.end(), this->rng);
	}
}


/**
* @brief Overridden method to load levels in an endless random cycle
* 
* Checks if the end of the manifest has been reached. If so, it resets the level index to 0
* and then reshuffles the level file order. 
* 
* Base method Game::loadNextLevel handles cleanup and file loading
*/
void RandomGame::loadNextLevel() {

	if (this->currentLevelIndex >= this->levelFiles.size()) {
		std::cout << "\nAll levels completed! Reshuffling " << this->levelFiles.size() << " levels...\n" << std::endl;

		this->currentLevelIndex = 0;
		std::shuffle(levelFiles.begin(), levelFiles.end(), this->rng);
	}

	Game::loadNextLevel();
}


/**
* @brief Overriden method that increments total levels completed counter and
* outputs number of levels solved.
*/
void RandomGame::onLevelSolved() {
	this->levelsCompleted++;

	std::cout << "\nLevel " << this->currentLevelIndex + 1 << " solved!" << std::endl;
	std::cout << "(Total Completed: " << this->levelsCompleted << ")\n" << std::endl;
}
