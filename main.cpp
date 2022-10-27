#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main() 
{
	const int windowWidth = 384;
	const int windowHeight = 384;

	InitWindow(windowWidth, windowHeight, "Top Down");
	
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{0.0,0.0};
	const float mapScale = 4.0f;

	Character knight{windowWidth, windowHeight};

	Prop props[2]
	{
		Prop { Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
		Prop { Vector2{400.0f,500.0f}, LoadTexture("nature_tileset/Log.png")}
	};

	Enemy goblin
	{ 
		Vector2{800.0f, 300.0f}, 
		LoadTexture("characters/goblin_idle_spritesheet.png"), 
		LoadTexture("characters/goblin_run_spritesheet.png") 
	};

	goblin.setTarget(&knight);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

		// Draw map
		DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

		// Draw props
		for (auto prop : props)
		{
			prop.Render(knight.getWorldPos());
		}

		knight.tick(GetFrameTime()); 

		// Map bounds
		if (knight.getWorldPos().x < 0.0f ||
			knight.getWorldPos().y < 0.0f ||
			knight.getWorldPos().x + windowWidth > map.width * mapScale ||
			knight.getWorldPos().y + windowHeight > map.height * mapScale)
		{
			knight.undoMovement();
		}

		// Check prop collision
		for (auto prop : props)
		{
			if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
			{
				knight.undoMovement();
			}
		}

		goblin.tick(GetFrameTime());

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec()));
			{
				goblin.setAlive(false);
			}
		}

		EndDrawing();
	}

	UnloadTexture(map);

	CloseWindow();
	
}