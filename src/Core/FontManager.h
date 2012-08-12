#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <Utilities/Singleton.h>
#include <Config/Export.h>
#include <Core/Texture.h>
#include <Core/Buffer.h>
#include <Core/Declaration.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>

#include <AgmdDefines.h>

#include <map>


namespace Agmd
{

    class AGMD_EXPORT FontManager : public Singleton<FontManager>
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
        // Données membres
        //----------------------------------------------------------
        TFontsMap        m_Fonts;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        DeclarationPtr  m_Declaration;
    };

}


#endif //FONTMANAGER_H
