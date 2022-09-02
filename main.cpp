#include <iostream>
#include <raylib.h>
#include <raymath.h>

int main() 
{
	const int windowWidth = 384;
	const int windowHeight = 384;

	InitWindow(windowWidth, windowHeight, "Top Down");

	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{ 0.0,0.0 };

	float speed = 5.0f;

	Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
	Vector2 knightPos = {
		(float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
		(float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)
	};

	// 1 : facing right, -1 : facing left
	float rightLeft = 1.0f;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		Vector2 direction{};

		// Movement
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;

		if (Vector2Length(direction) != 0.0)
		{
			// Set mapPos = mapPos - direction
			// Move the map
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

			direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
		}
		
		// Draw map
		DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

		// Draw the character
		Rectangle source{ 0.0f, 0.0f, (float)knight.width / 6.0f, (float)knight.height };
		Rectangle dest{ knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0 * (float)knight.height };
		DrawTexturePro(knight, source, dest, Vector2{}, 0.0f, WHITE);

		EndDrawing();
	}

	UnloadTexture(map);

	CloseWindow();
	
}