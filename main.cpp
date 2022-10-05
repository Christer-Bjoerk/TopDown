#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Character.h"

int main() 
{
	const int windowWidth = 384;
	const int windowHeight = 384;

	InitWindow(windowWidth, windowHeight, "Top Down");
	
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{0.0,0.0};
	const float mapScale = 4.0f;

	Character knight;
	knight.setScreenPos(windowWidth, windowHeight);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

		// Draw map
		DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
		knight.tick(GetFrameTime()); 

		// Map bounds
		if (knight.getWorldPos().x < 0.0f ||
			knight.getWorldPos().y < 0.0f ||
			knight.getWorldPos().x + windowWidth > map.width * mapScale ||
			knight.getWorldPos().y + windowHeight > map.height * mapScale)
		{
			knight.undoMovement();
		}

		EndDrawing();
	}

	UnloadTexture(map);

	CloseWindow();
	
}