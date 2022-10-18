#include "BaseCharacter.h"
#include "raylib.h"

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
