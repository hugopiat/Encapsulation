#pragma once
#include "AWindow.h"

class WindowRaylib :
    public AWindow
{
    // H�rit� via AWindow
    void Init() override;
    void Draw() override;
    void Clear() override;
    bool IsOpen() override;
    bool Close() override;
};

