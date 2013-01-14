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
#include <Core/Texture/Texture.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Vector2.h>
#include <Vector3.h>

#include <AgmdDefines.h>

#include <map>


namespace Agmd
{

    class AGMD3D_EXPORT FontManager : public Singleton<FontManager>
    {
    MAKE_SINGLETON(FontManager)

    public :

        void LoadFont(const std::string& FontName, int Quality = 32);

        void UnloadFonts();

        void DrawString(const GraphicString& String);

        ivec2 GetStringPixelSize(const GraphicString& String);

    private :

        FontManager();

        ~FontManager();

        void Initialize();

        struct TVertex
        {
            vec3     Position;
            uint32   Diffuse;
            vec2     TexCoords; 
        };

        typedef unsigned short TIndex;

        struct TFont
        {
            Texture  Texture;
            ivec2    CharSize[256];
        };

        typedef std::map<std::string, TFont> TFontsMap;
        static const unsigned int NbCharMax = 512;

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        TFontsMap        m_Fonts;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        DeclarationPtr  m_Declaration;
    };

}


#endif //FONTMANAGER_H
