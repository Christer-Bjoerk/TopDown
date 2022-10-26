#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
	BaseCharacter();

	Vector2 getWorldPos() { return worldPos; }

	void undoMovement();

	Rectangle getCollision();

	virtual void tick(float deltaTime);

	virtual Vector2 getScreenPos() = 0;

protected:
	Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");

	Vector2 worldPos{};
	Vector2 worldPosLastFrame{};

	// 1 : facing right, -1 : facing left
	float rightLeft = 1.0f;

	// Animation variables
	float runningTime = 0;
	int frame = 0;
	int maxFrames = 6;
	float updateTime = 1.0f / 20.0f;
	float speed = 4.0f;
	float width = 0.0f;
	float height = 0.0f;
	float scale = 4.0f;
	Vector2 velocity{};
private:

};

#endif

