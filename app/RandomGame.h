#ifndef RANDOM_GAME_H
#define RANDOM_GAME_H

#include "Game.h"

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

class RandomGame : public Game {
public:
	RandomGame();
protected:
	void loadLevelManifest(const std::string& levelManifestFilename) override;
	void loadNextLevel(unsigned int attempts = 0) override;
	void onLevelSolved() override;
private:
	std::default_random_engine rng;
	unsigned int levelsCompleted = 0;
};

#endif
