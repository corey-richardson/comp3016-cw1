// app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "Tile.h"
#include "Grid.h"
#include "LevelLoader.h"

int main()
{
    std::string filename = "levels/level-example.txt";

    Grid level = Grid(LevelLoader::loadLevel(filename));
    level.display();

    std::cout << "Start Coords: " << level.getStartCoords().x << ", " << level.getStartCoords().y << std::endl;
    std::cout << "End Coords:   " << level.getEndCoords().x << ", " << level.getEndCoords().y << std::endl;

    std::cout << "Walkable Tiles: " << level.getRemainingWalkableTiles() << std::endl;
}
