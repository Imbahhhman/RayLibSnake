#pragma once

#include "raylib.h"

#ifndef TILE_H
#define TILE_H


enum TileState
{
	Block, Apple, Snake, Follow
};



class Tile
{
public:

	Tile(int h, int v, int tileSize, int num);

	Rectangle rect; // rect where we draw the tile
	Vector2 txtPos = Vector2{};
	int heldDirection = 0; // stores direction in tile
	int num = 0;

	TileState state = TileState::Block;

	Color bgColor, txtColor;

	void Draw();
};




#endif // !TILE_H



/*
	Reusing Tile Code from class due to simplicity


*/