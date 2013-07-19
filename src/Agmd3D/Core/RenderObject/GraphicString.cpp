/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderObject/GraphicString.h>
#include <Core/FontManager.h>
#include <Debug/New.h>
#include <Transform.h>

namespace Agmd
{
    GraphicString::GraphicString(const ivec2& stringPosition, const std::string& stringText, const Color& stringColor, const std::string& stringFont, int stringSize) :
        Displayable(new Transform(vec3(stringPosition.x,stringPosition.y,0.0f))),
    m_Text    (stringText),
    m_color   (stringColor),
    m_Font    (stringFont),
    m_Size    (stringSize)
    {
        BuildModel();
    }

    void GraphicString::Draw() const
    {
        FontManager::Instance().DrawString(*this);
    }

    ivec2 GraphicString::GetPixelSize() const
    {
        return FontManager::Instance().GetStringPixelSize(*this);
    }

    GraphicString& GraphicString::operator=( const std::string& str)
    {
        if(!this->m_Text.compare(str))
            return *this;
        this->m_Text = str;
        BuildModel();
        return *this;
    }

    void GraphicString::BuildModel()
    {
        FontManager::Instance().GenerateStringMesh(*this);
    }

    void GraphicString::Align(unsigned long mode, const AgmdMaths::Rectangle& rect)
    {
        ivec2 pSize = GetPixelSize();
        /*
        if (mode & ALIGN_RIGHT)
        {
            m_Position.x = rect.Right() - pSize.x;
        }
        else if (mode & ALIGN_HCENTER)
        {
            m_Position.x = rect.Left() + (rect.Width() - pSize.x) / 2;
        }
        else
        {
            m_Position.x = rect.Left();
        }

        if (mode & ALIGN_BOTTOM)
        {
            m_Position.y = rect.Bottom() - pSize.y;
        }
        else if (mode & ALIGN_VCENTER)
        {
            m_Position.y = rect.Top() + (rect.Height() - pSize.y) / 2;
        }
        else
        {
            m_Position.y = rect.Top();
        }*/
    }

}
