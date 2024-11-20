#pragma once
#include "AWindow.h"

class WindowRaylib :
    public AWindow
{
    // Hérité via AWindow
    void Init() override;
    void Draw() override;
    void Clear() override;
    bool IsOpen() override;
    bool Close() override;
};

