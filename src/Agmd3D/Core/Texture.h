#ifndef TEXTURE_H
#define TEXTURE_H

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/Enums.h>
#include <Core/TextureBase.h>
#include <Rectangle.h>
#include <Utilities/SmartPtr.h>
#include <Utilities/Color.h>

using namespace AgmdUtilities;
using namespace AgmdMaths;

namespace Agmd
{

    class AGMD_EXPORT Texture
    {
    public :

        void Create(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags = 0, const std::string& name = "");

        void CreateFromFile(const std::string& filename, TPixelFormat format, unsigned long flags = 0);

        void CreateFromImage(const Image& image, TPixelFormat format, TTextureType type, unsigned long flags = 0, const std::string& name = "");

        void SaveToFile(const std::string& filename) const;

        void Update(const AgmdMaths::Rectangle& rect = AgmdMaths::Rectangle(-1, -1, -1, -1));

		void SetActiveTexture(int32 id);

        Image& GetPixels();

        const ivec2& GetSize() const;

        TPixelFormat GetFormat() const;

		TTextureType GetType() const;
	
		int GetActiveTexture() const;

        const std::string& GetName() const;

        const TextureBase* GetTexture() const;

        bool operator ==(const Texture& texture) const;

        bool operator !=(const Texture& texture) const;

    private :

        void Load(const Image& image, TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name);

        SmartPtr<TextureBase, ResourceCOM> m_Texture;
    };

}

#endif //TEXTURE_H