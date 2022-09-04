#include <raylib.h>

class Character
{
public:
	Character();
	Vector2 getWorldPos() { return worldPos; }
	void setScreenPos(int winWidth, int winHeight);
	void tick(float deltaTime);

private:

	Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
	
	Vector2 screenPos{};
	Vector2 worldPos{};

	// 1 : facing right, -1 : facing left
	float rightLeft = 1.0f;

	// Animation variables
	float runningTime = 0;
	int frame = 0;
	int maxFrames = 6;
	float updateTime = 1.0f / 20.0f;
	float speed = 4.0f;

	float width{};
	float height{};
};
