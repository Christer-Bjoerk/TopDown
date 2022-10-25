#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
	worldPos = pos;
	texture = idle_texture;
	idle = idle_texture;
	run = run_texture;

	width = texture.width / maxFrames;
	height = texture.height;

	speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
	// Get toTarget
	Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);

	// Normalize toTarget
	toTarget = Vector2Normalize(toTarget);

	// Multiply toTarget by speed
	toTarget = Vector2Scale(toTarget, speed);

	// Move the Enemy
	worldPos = Vector2Add(worldPos, toTarget);

	// To avoid getting the enemy stuck in the same position
	screenPos = Vector2Subtract(worldPos, target->getWorldPos());

	BaseCharacter::tick(deltaTime);
}
