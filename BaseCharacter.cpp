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

Rectangle BaseCharacter::getCollisionRec()
{
	return Rectangle
	{
		getScreenPos().x,
		getScreenPos().y,
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

		if (frame > maxFrames) 
			frame = 0;
	}

	if (Vector2Length(velocity) != 0.0)
	{
		// Set worldPos = worldPos + velocity
		// Move the map
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

		// Switch direction
		velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;

		// Change animation 
		texture = run;
	}
	else
	{
		texture = idle;
	}

	velocity = {};

	// Draw the character
	Rectangle source{ frame * width, 0.0f, rightLeft * width, height };
	Rectangle dest{ getScreenPos().x, getScreenPos().y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}
