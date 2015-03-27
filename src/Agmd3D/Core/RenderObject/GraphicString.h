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
#include <Core/Buffer/Buffer.h>
#include <Core/RenderObject/Displayable.h>
#include <Core/FontManager.h>
#include <Vector2.h>
#include <Rectangle.h>
#include <map>
#include <string>
#include <core/Buffer/Buffer.h>


namespace Agmd
{
    class AGMD3D_EXPORT GraphicString : public Displayable
    {
    private:

    public :
        friend class FontManager;

        GraphicString(const ivec2 & stringPosition = ivec2(0), const std::string& stringText = "", const Color& stringColor = Color::white, const std::string& stringFont = "Arial", int stringSize = 20);

        void draw() const;
        void render(TRenderPass) const {}
        void buildModel();
        ivec2 getPixelSize() const;
        void setSize(int size)
        {
            m_size = size;
        }
        int getSize() const
        {
            return m_size;
        }
        void align(unsigned long mode, const AgmdMaths::Rectangle& rect);

        GraphicString& operator=( const std::string& str);

        //ivec2       m_position;
        std::string   m_text;

        Color       m_color;
        std::string m_font;
        int         m_size;
    private:
        Buffer<FontManager::TVertex> m_vertexBuffer;
        Buffer<FontManager::TIndex> m_indexBuffer; 
    };

}


#endif // GRAPHICSTRING_H
