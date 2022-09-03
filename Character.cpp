#include "Character.h"
#include <raymath.h>

void Character::setScreenPos(int winWidth, int winHeight)
{
	screenPos = {
		(float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
		(float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
	};
}

void Character::tick(float deltatime)
{
	Vector2 direction{};

	// Movement
	if (IsKeyDown(KEY_A)) direction.x -= 1.0;
	if (IsKeyDown(KEY_D)) direction.x += 1.0;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0;
	if (IsKeyDown(KEY_S)) direction.y += 1.0;

	if (Vector2Length(direction) != 0.0)
	{
		// Set worldPos = worldPos + direction
		// Move the map
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

		// Switch direction
		direction.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;

		// Change animation 
		texture = run;
	}
	else
	{
		texture = idle;
	}

	// Update Animation frame
	runningTime += deltatime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0;
		if (frame > maxFrames)frame = 0;
	}

	// Draw the character
	Rectangle source{ frame * (float)texture.width / 6.0f, 0.0f, rightLeft * (float)texture.width / 6.0f, (float)texture.height };
	Rectangle dest{ screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0 * (float)texture.height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}