/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/GraphicString.h>
#include <Core/FontManager.h>
#include <Debug/New.h>

namespace Agmd
{


GraphicString::GraphicString(const ivec2& StringPosition, const std::string& StringText, const Color& StringColor, const std::string& StringFont, int StringSize) :
Position(StringPosition),
Text    (StringText),
color   (StringColor),
Font    (StringFont),
Size    (StringSize)
{

}

void GraphicString::Draw() const
{
    FontManager::Instance().DrawString(*this);
}

ivec2 GraphicString::GetPixelSize() const
{
    return FontManager::Instance().GetStringPixelSize(*this);
}


void GraphicString::Align(unsigned long Mode, const AgmdMaths::Rectangle& Rect)
{
    ivec2 PSize = GetPixelSize();

    if (Mode & ALIGN_RIGHT)
    {
        Position.x = Rect.Right() - PSize.x;
    }
    else if (Mode & ALIGN_HCENTER)
    {
        Position.x = Rect.Left() + (Rect.Width() - PSize.x) / 2;
    }
    else
    {
        Position.x = Rect.Left();
    }

    if (Mode & ALIGN_BOTTOM)
    {
        Position.y = Rect.Bottom() - PSize.y;
    }
    else if (Mode & ALIGN_VCENTER)
    {
        Position.y = Rect.Top() + (Rect.Height() - PSize.y) / 2;
    }
    else
    {
        Position.y = Rect.Top();
    }
}

}
