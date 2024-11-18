#if _SDL
#pragma once
#include "AWindow.h"

class WindowSDL : public AWindow
{
protected:
	void OnCreate() override;
public:

	// H�rit� via AWindow
	void Init() override;
	void Draw() override;
	void Clear() override;
	bool IsOpen() override;
};
#endif // _SDL

