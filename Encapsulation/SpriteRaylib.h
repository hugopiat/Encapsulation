#pragma once
#include "ASprite.h"

class SpriteRaylib : public ASprite
{
private:
	//Texture2D texture;

public:
	SpriteRaylib();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void LoadImage(const std::string& filename) override;
};

