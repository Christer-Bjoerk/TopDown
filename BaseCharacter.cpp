#include "BaseCharacter.h"
#include "raylib.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() 
{

}

void BaseCharacter::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollision()
{
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}

void BaseCharacter::tick(float deltatime)
{
	worldPosLastFrame = worldPos;

	// Update Animation frame
	runningTime += deltatime;
	if (runningTime >= updateTime)
	{
		frame++;
		runningTime = 0;
		if (frame > maxFrames) frame = 0;
	}

	// Draw the character
	Rectangle source{ frame * width, 0.0f, rightLeft * width, height };
	Rectangle dest{ screenPos.x, screenPos.y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}
