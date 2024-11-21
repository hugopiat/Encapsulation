#pragma once
class AText;

class TextManager
{
private:
	static TextManager* s_instance;
public:
	AText* InstantiateText();
	static TextManager* GetInstance();
};

