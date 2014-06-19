/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/Enums.h>
#include <Core/Texture/TextureBase.h>
#include <Rectangle.h>
#include <Utilities/SmartPtr.h>
#include <Utilities/Color.h>

using namespace AgmdUtilities;
using namespace AgmdMaths;

namespace Agmd
{

    class AGMD3D_EXPORT Texture
    {
    public :

        void Create(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags = 0, const std::string& name = "");

        void CreateFromFile(const std::string& filename, TPixelFormat format, unsigned long flags = 0);

        void CreateFromImage(const Image& image, TPixelFormat format, unsigned long flags = 0, const std::string& name = "");

        void CreateFromFile(const std::string filename[], TPixelFormat format, unsigned long flags = 0);
        void CreateFromImage(const Image image[], TPixelFormat format, unsigned long flags = 0, const std::string& name = "");

        void SaveToFile(const std::string& filename) const;


        void Update(const AgmdMaths::Rectangle& rect = AgmdMaths::Rectangle(-1, -1, -1, -1));

        Image& GetPixels();
		Image* GetPixelsPtr();

        const ivec2& GetSize() const;

        TPixelFormat GetFormat() const;

        TTextureType GetType() const;
    
        int GetActiveTexture() const;

        const std::string& GetName() const;

        const TextureBase* GetTexture() const;

        bool operator ==(const Texture& texture) const;

        bool operator !=(const Texture& texture) const;

        static void TextureAdd(Texture output, Texture input1, Texture input2);
        static void TextureProd(Texture output, Texture input1, Texture input2);
		static void TextureRender(Texture input,ivec2 pos = ivec2(0),ivec2 resolution=ivec2(-1));
        static void TextureRandom();

        static void BeginRenderToTexture(const Texture& texture);
        static void EndRenderToTexture();
        static BaseShaderProgram* s_addTexture;
        static BaseShaderProgram* s_prodTexture;
        static BaseShaderProgram* s_renderTexture;
        static BaseShaderProgram* s_randomTexture;
        static FrameBuffer* s_framebuffer;
        static void BeginRenderToCubeMap(const Texture& texture, TAttachment attachment, int face = -1);
        static void EndRenderToCubeMap();

    private :

        void Load(const Image& image, TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name);
        void Load(const Image image[], TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name);
		
		SmartPtr<TextureBase, ResourceCOM> m_Texture;
    };

}

#endif //TEXTURE_H
