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


void GraphicString::Align(unsigned long Mode, const Rectangle& Rect)
{
    // Calcul de la taille en pixels
    ivec2 PSize = GetPixelSize();

    // Alignement horizontal
    if (Mode & ALIGN_RIGHT)
    {
        Position.x = Rect.Right() - PSize.x;
    }
    else if (Mode & ALIGN_HCENTER)
    {
        Position.x = Rect.Left() + (Rect.Width() - PSize.x) / 2;
    }
    else // par défaut : ALIGN_LEFT
    {
        Position.x = Rect.Left();
    }

    // Alignement vertical
    if (Mode & ALIGN_BOTTOM)
    {
        Position.y = Rect.Bottom() - PSize.y;
    }
    else if (Mode & ALIGN_VCENTER)
    {
        Position.y = Rect.Top() + (Rect.Height() - PSize.y) / 2;
    }
    else // par défaut : ALIGN_TOP
    {
        Position.y = Rect.Top();
    }
}

}
