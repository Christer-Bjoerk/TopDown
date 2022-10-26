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

void Character::tick(float deltaTime)
{

	// Movement
	if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0;
	
	BaseCharacter::tick(deltaTime);
}