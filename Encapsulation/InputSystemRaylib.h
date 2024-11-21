#pragma once
#include "AInputSystem.h"
class InputSystemRaylib : public Encapsulation::AInputSystem
{
	// Hérité via AInputSystem
	virtual void PoolEvent() override;
};

