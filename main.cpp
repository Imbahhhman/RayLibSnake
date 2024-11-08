#include "raylib.h"
#include "Example.h"
#include "Memory.h"


int main() 
{
	Memory memory; 
	memory.Main();

	return 0;
}














void Collision()
{
	int r = 80;
	float speed = 1.0f; int size = 600;
	int cenX = size / 2, cenY = 100; Color c = RAYWHITE;
	float a = 0.25f;

	InitWindow(size, size, "Bouncing Ball");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing(); ClearBackground(GRAY);

		cenY += speed;
		speed += a;
		if (cenY > size - r) // if we collided with the bottom
		{
			cenY = size - r; // if we have already crossed the bottom
			// place us AT THE bottom
			speed *= -0.6f;
			if (a < 1) a += 0.1f;
		}

		DrawCircle(cenX, cenY, r, c);


		EndDrawing();
	}
}


enum State
{
	out, hover, pressed
};
void UICollision()
{
	InitWindow(500, 500, "UI Button");
	SetTargetFPS(60);

	Rectangle rect = { 150, 228, 200, 44 }; // 250 - 44/2
	Vector2 mousePos;

	State butState = out; Color c = BLUE;

	while (!WindowShouldClose()) {
		BeginDrawing(); ClearBackground(GRAY);
		mousePos = GetMousePosition();

		if (CheckCollisionPointRec(mousePos, rect)) {
			if (butState != pressed)
			{
				butState = hover;
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
					butState = pressed;
			}
			else
			{
				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
					butState = pressed;
			}
		}
		else if (butState != pressed) butState = out;


		if (butState == out) c = BLUE;
		else if (butState == hover) c = ORANGE;
		else c = GREEN;

		DrawRectangleRounded(rect, 0.5f, 12, c);

		EndDrawing();
	}

	CloseWindow();
}

void CollisionRectCircle()
{
	InitWindow(500, 500, "Circle Rect Collision"); SetTargetFPS(60);

	int y = 100; bool collision = false; int r = 50;
	Rectangle rect = { 200, 400, 100, 50 };

	while (!WindowShouldClose()) {
		BeginDrawing(); ClearBackground(GRAY);

		Vector2 cen = { 250 , y };
		collision = CheckCollisionCircleRec(cen, r, rect);

		if (!collision) DrawCircle(cen.x, cen.y, r, BLUE); y += 1;
		DrawRectangleRec(rect, GREEN);

		EndDrawing();
	}

	CloseWindow();
}