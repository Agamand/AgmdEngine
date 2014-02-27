/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <Utilities/Singleton.h>
#include <Config/Export.h>
#include <core/Shader/ShaderProgram.h>
#include <Core/Texture/Texture.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Transform.h>

#include <CommonDefines.h>

#include <map>


namespace Agmd
{

    class AGMD3D_EXPORT FontManager : public Singleton<FontManager>
    {
    MAKE_SINGLETON(FontManager)

    public :
        friend class GraphicString;
        void LoadFont(const std::string& fontName, int quality = 32);

        void UnloadFonts();

        void DrawString(const GraphicString& string);

        void GenerateStringMesh(GraphicString& string);

        ivec2 GetStringPixelSize(const GraphicString& string);

    private :

        FontManager();

        ~FontManager();

        void Initialize();

        struct TVertex
        {
            vec3     position;
            vec2     texcoord;
        };

        typedef a_uint16 TIndex;

        struct TFont
        {
            Texture  texture;
            ivec2    charSize[256];
        };

        typedef std::map<std::string, TFont> TFontsMap;
        static const unsigned int nbCharMax = 512;

        TFontsMap       m_Fonts;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        DeclarationPtr  m_Declaration;
        ShaderProgram   m_program;
        Transform*      m_transform;
    };

}


#endif //FONTMANAGER_H
