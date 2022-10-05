#include "Character.h"
#include <raymath.h>

Character::Character(int winWidth, int winHeight)
{
	width = texture.width / maxFrames;
	height = texture.height;

	screenPos = {
		static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(winHeight) / 2.0f - scale *(0.5f * height)
	};
}

void Character::tick(float deltatime)
{
	worldPosLastFrame = worldPos;

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
	Rectangle source{ frame * width, 0.0f, rightLeft * width, height};
	Rectangle dest{ screenPos.x, screenPos.y, scale * width, scale * height};
	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void Character::undoMovement() 
{
	worldPos = worldPosLastFrame;
}