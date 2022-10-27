#include "Character.h"
#include <raymath.h>

Character::Character(int winWidth, int winHeight) :
	windowWidth(winWidth),
	windowHeight(winHeight)
{
	width = texture.width / maxFrames;
	height = texture.height;
}

Vector2 Character::getScreenPos()
{
	return Vector2
	{
		static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
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

	// Origin point of the sword
	Vector2 origin{};
	// Adjust the offset of the sword origin
	Vector2 offset{};
	// Sword Rotation
	float rotation{};

	if (rightLeft > 0.0f)
	{
		origin = { 0.0f, weapon.height * scale };
		offset = { 35.0f, 55.0f };

		weaponCollisionRec =
		{
			getScreenPos().x + offset.x,
			getScreenPos().y + offset.y - weapon.height * scale,
			weapon.width * scale,
			weapon.height * scale
		};

		rotation = 35.0f;
	}
	else
	{
		origin = { weapon.width * scale, weapon.height * scale };
		offset = { 25.0f, 55.0f };

		weaponCollisionRec =
		{
			getScreenPos().x + offset.x - weapon.width * scale,
			getScreenPos().y + offset.y - weapon.height * scale,
			weapon.width * scale,
			weapon.height * scale
		};
		
		rotation = -35.0f;
	}


	// Draw sword
	Rectangle source{ 0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
	Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
	DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

	// Draw the Swords's collision box 
	DrawRectangleLines
	(
		weaponCollisionRec.x,
		weaponCollisionRec.y,
		weaponCollisionRec.width,
		weaponCollisionRec.height,
		RED
	);
}