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

	virtual void Init(AWindow* window, const std::string& filename, int width = 0, int height = 0, int x = 0, int y = 0) override;
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Load(const std::string& filename) override;
};

