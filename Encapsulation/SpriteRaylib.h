#pragma once
#include "ASprite.h"
#include "raylib.h"

class AWindow;
class WindowRaylib;

class SpriteRaylib : public ASprite
{
private:
	Texture2D* m_texture;
	WindowRaylib* m_windowRaylib;
	virtual void Load(const std::string& filename) override;

public:
	SpriteRaylib();
	~SpriteRaylib();

	virtual void Init(AWindow* window, const std::string& filename, int width = 50, int height = 50, int x = 0, int y = 0) override;
	virtual void Draw() override;

	virtual void SetPositionSprite(const Maths::Vector2& vect2D) override;
	virtual void SetSizeSprite(const Maths::Vector2& size2D) override;
};

