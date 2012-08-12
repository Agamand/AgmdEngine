#ifndef IMAGE_H
#define IMAGE_H

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/Enums.h>
#include <Maths/Vector2.h>
#include <Utilities/Color.h>
#include <vector>

namespace Agmd
{
    class AGMD_EXPORT Image
    {
    public :

        Image(const ivec2& Size = ivec2(1, 1), TPixelFormat format = PXF_A8R8G8B8);

        Image(const ivec2& Size, TPixelFormat format, const unsigned char* pixels);

        const ivec2& GetSize() const;

        TPixelFormat GetFormat() const;

        const unsigned char* GetData() const;

        void LoadFromFile(const std::string& filename);

        void Fill(const Color& color);

        void SetPixel(int x, int y, const unsigned char* pix);

        void SetPixel(int x, int y, const Color& Color);

        void GetPixel(int x, int y, unsigned char* Pix) const;

        Color GetPixel(int x, int y) const;

        void CopyImage(const Image& src);

        Image SubImage(const Rectangle& rect) const;

        void Flip();

        void Mirror();

    private :

        ivec2					   m_Size;
        TPixelFormat               m_Format;
        std::vector<unsigned char> m_Pixels;
    };

}

#endif //IMAGE_H
