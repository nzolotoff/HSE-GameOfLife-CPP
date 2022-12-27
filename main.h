#pragma once
#include <iostream>

bool** createGrid(int n, int m);

void displayGrid(bool** grid, int n, int m);

void releaseGrid(bool** grid, int n);

int countAliveNeighbours(bool** grid, int k, int l);

bool** nextGeneration(bool** grid, int n, int m);

bool checksTwoGridsForDifferences(bool** prevGrid, bool** nextGrid, int n, int m);

void fillGrid(bool** grid, int n, int m);


#ifndef GAMEOFLIFE_MAIN_H
#define GAMEOFLIFE_MAIN_H

#endif //GAMEOFLIFE_MAIN_H
