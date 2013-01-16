/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef GRAPHICSTRING_H
#define GRAPHICSTRING_H

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Utilities/Color.h>
#include <Utilities/Singleton.h>
#include <Core/Buffer/Buffer.h>
#include <Vector2.h>
#include <Rectangle.h>
#include <map>
#include <string>


namespace Agmd
{
    class AGMD3D_EXPORT GraphicString
    {
    public :

        GraphicString(const ivec2 & stringPosition = ivec2(0), const std::string& stringText = "", const Color& stringColor = Color::white, const std::string& stringFont = "Arial", int stringSize = 16);

        void Draw() const;

        ivec2 GetPixelSize() const;

        void Align(unsigned long mode, const AgmdMaths::Rectangle& rect);

        ivec2       m_Position;
        std::string m_Text;
        Color       m_color;
        std::string m_Font;
        int         m_Size;
    };

}


#endif // GRAPHICSTRING_H
