#pragma once

#include "raylib.h"
#include <vector>
#include "Tile.h"

#ifndef MEMORY_H
#define MEMORY_H
using namespace std;

class Memory
{
public:
#define GAP 1 
#define WAIT_Time 0.5f 


	Color bgColor = RAYWHITE;

	int gridSize = 10;
	static const int widthHeight = 800;
	vector<Tile> tilesArr;

	vector<Tile*> tail;
	
	int gameFrameSpeed = 20;
	int pos = 0;
	int snakeLength = 2;
	int keyPress;
	int direction = 0;
	int turncount;
	int difficulty = 0;
	int pickup = 0;
	
	bool gameFinished = false;
	bool compareMode = false;
	bool gameStarted = false;
	bool gameLost = false;
	bool isApple = false;

	void Main();
	void Start();
	void Draw();
	void Update();
};

#endif 
#pragma once
