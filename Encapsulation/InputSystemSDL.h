#pragma once
#include "AInputSystem.h"
using namespace Encapsulation;

class InputSystemSDL : public Encapsulation::AInputSystem
{
	// H�rit� via AInputSysteme
	virtual void PoolEvent() override;
};

