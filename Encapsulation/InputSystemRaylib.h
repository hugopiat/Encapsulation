#pragma once
#include "AInputSystem.h"
class InputSystemRaylib : public Encapsulation::AInputSystem
{
	// H�rit� via AInputSystem
	virtual void PoolEvent() override;
};

