#pragma once
#include "ASprite.h"
#include "raylib.h"

class AWindow;

class SpriteRaylib : public ASprite
{
private:
	Texture2D texture;

public:
	SpriteRaylib();
	~SpriteRaylib();

	virtual void Init(AWindow* window, int x, int y, int width, int height) override;
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Load(const std::string& filename) override;
};

