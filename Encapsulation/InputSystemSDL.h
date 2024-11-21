#pragma once
#include "AInputSystem.h"
using namespace Encapsulation;

class InputSystemSDL : public Encapsulation::AInputSystem
{
	// Hérité via AInputSysteme
	virtual void PoolEvent() override;
};

