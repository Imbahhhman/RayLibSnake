#include "Memory.h"

#include <time.h>

#include <string>



void Memory::Main() 
{
	Start(); 

	InitWindow(widthHeight, widthHeight, "Snake");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing(); 
		ClearBackground(bgColor);

		Update(); 
		Draw(); 

		EndDrawing();
	}
	CloseWindow();
}

void Memory::Start()
{
	tilesArr.clear();
	int tileSize = (int)((widthHeight - (GAP * (gridSize + 1))) / gridSize);

	vector<int> numbers;
	for (int i = 0; i < gridSize * gridSize / 2; i++)
	{
		numbers.push_back(i + 1); // 1 -> 8
		numbers.push_back(i + 1); // 1 -> 8
	}

	srand(time(NULL));
	for (int row = 0; row < gridSize; row++)
		for (int col = 0; col < gridSize; col++)
		{
			int randomIndex = rand() % numbers.size(); // 132158
			int tileNum = numbers[randomIndex];
			Tile tile = Tile(	row, 
								col, 
								tileSize, 
								tileNum);
			tilesArr.push_back(tile); // populting the array
			numbers.erase(numbers.begin() + randomIndex);
		}
	tilesArr[0].state = TileState::Snake;
}

void Memory::Update()
{
	int key;
	if (gameStarted)
	{
		srand(time(NULL));

		if (isApple == false)
		{
			int randomIndex = rand() % tilesArr.size();
			if (tilesArr[randomIndex].state == TileState::Block)
			{
				tilesArr[randomIndex].state = TileState::Apple; // Random Apple
				isApple = true;
			}
		}


		tilesArr[pos].num = snakeLength;
		key = GetKeyPressed();

		if (key == KEY_UP)
		{
			direction = -1; 
		}
		else if (key == KEY_DOWN)
		{
			direction = 1;
		}
		else if (key == KEY_LEFT)
		{
			direction = -10;
		}
		else if (key == KEY_RIGHT)
		{
			direction = 10;
		}

		if (gameFrameSpeed == 0)
		{
			if ((pos + 1) % 10 == 0)
				if(direction == 1)//Detects if going out of bounds off top or bottom
				gameLost = true;

			if ((pos + 10) % 10 == 0)
				if(direction == -1)
				gameLost = true;




			if ((pos + direction) < 0 || (pos + direction) > tilesArr.size())
			{
				gameLost = true;
			}
			else
			{

				if (tilesArr[pos + direction].state == TileState::Block) //empty spot
				{
					tilesArr[pos].state = TileState::Follow;
					tail.push_back(&tilesArr[pos]);
					pos = pos + direction;
					tilesArr[pos].state = TileState::Snake;
				}
				else if (tilesArr[pos + direction].state == TileState::Apple) //Apple
				{
					snakeLength++;
					tilesArr[pos].state = TileState::Follow;
					tail.push_back(&tilesArr[pos]);
					for (int i = 0; i < tail.size(); i++)
						tail[i]->num++;
					pos = pos + direction;
					tilesArr[pos].state = TileState::Snake;
					isApple = false;
					pickup++;
					if (pickup >= 3 && difficulty != 12)
					{
						difficulty++;
						difficulty++;
					}
				}
				else if (tilesArr[pos + direction].state == TileState::Follow) //Tail
				{
					gameLost = true;
				}
				

			}

			for (int i = 0; i < tail.size(); i++)
			{
				tail[i]->num--;

				if (tail[i]->num == 0)
				{
					tail[i]->state = TileState::Block;
					tail.erase(tail.begin() + i);
				}
			}
			

			gameFrameSpeed = (20 - difficulty); // Resets the count
		}
		else
		{
			gameFrameSpeed--;
			
		}
	}

	else // Starts the game by pressing the left mouse button
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			gameStarted = true;
			gameLost = false;
		}
	}
}

void Memory::Draw()
{
	string txt = "Congrations";

	if (!gameFinished && !gameLost)
		for (Tile tile : tilesArr)
			tile.Draw();
	else if (gameFinished)
		DrawText(txt.c_str(), 400, 400, 50, BLACK);
	else
	{
		for (int i = 0; i < tilesArr.size(); i++)
			tilesArr[i].state = Block;
		isApple = false;
		direction = 0;
		pos = 0;
		gameStarted = false;
		DrawText("You Lose",275 , 350, 50, BLACK);
	}
}

