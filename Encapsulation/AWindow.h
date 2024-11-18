#pragma once
class AWindow
{
protected:
	virtual void OnCreate() = 0;
public:
	AWindow();
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Clear() = 0;
	virtual bool IsOpen() = 0;
};

