#pragma once
#include "AText.h"
#include "raylib.h"
class TextRaylib :
    public AText
{
public:
    // H�rit� via AText
    void OnInit() override;
    void Draw() override;
private:
    Font m_font;
};

