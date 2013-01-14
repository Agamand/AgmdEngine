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

        GraphicString(const ivec2 & StringPosition = ivec2(0), const std::string& StringText = "", const Color& StringColor = Color::white, const std::string& StringFont = "Arial", int StringSize = 16);

        void Draw() const;

        ivec2 GetPixelSize() const;



        void Align(unsigned long Mode, const AgmdMaths::Rectangle& Rect);

        ivec2   Position;
        std::string Text;
        Color      color;
        std::string Font;
        int         Size;
    };

}


#endif // GRAPHICSTRING_H
