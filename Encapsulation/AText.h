#pragma once
#include <string>
#include <functional>
#include "Vector2.h"


class AText
{
protected:
	std::string m_text;
	Maths::Vector2 m_pos;
	int m_fontSize;


public:
	AText();
	void Init(std::string text, int posX, int posY, int fontSize);
	virtual void OnInit() = 0;
	virtual void Draw() = 0;

	void SetText(std::string text);
};

