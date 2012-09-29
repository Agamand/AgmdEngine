#include <Core/Image.h>
#include <Core/MediaManager.h>
#include <algorithm>
#include <Utilities/PixelUtils.h>
#include <Debug/Exception.h>
#include <Debug/New.h>


namespace Agmd
{

	Image::Image(const ivec2& size, TPixelFormat format) :
	m_Size  (size),
	m_Format(format),
	m_Pixels(size.x * size.y * GetBytesPerPixel(format), 0x00)
	{}

	Image::Image(const ivec2& size, TPixelFormat format, const unsigned char* pixels) :
	m_Size  (size),
	m_Format(format),
	m_Pixels(pixels, pixels + size.x * size.y * GetBytesPerPixel(format))
	{}

	const ivec2& Image::GetSize() const
	{
		return m_Size;
	}

	TPixelFormat Image::GetFormat() const
	{
		return m_Format;
	}

	const unsigned char* Image::GetData() const
	{
		return &m_Pixels[0];
	}

	void Image::LoadFromFile(const std::string& filename)
	{
		SmartPtr<Image> image = MediaManager::Instance().LoadMediaFromFile<Image>(filename);

		CopyImage(*image);
	}

	void Image::Fill(const Color& color)
	{

		SetPixel(0, 0, color);

		unsigned int Bpp = GetBytesPerPixel(m_Format);
		std::vector<unsigned char>::iterator Begin = m_Pixels.begin();
		for (std::vector<unsigned char>::iterator i = Begin + Bpp; i != m_Pixels.end(); i += Bpp)
			std::copy(Begin, Begin + Bpp, i);
	}

	void Image::SetPixel(int x, int y, const unsigned char* pix)
	{
		std::copy(pix, pix + GetBytesPerPixel(m_Format), &m_Pixels[(x + y * m_Size.x) * GetBytesPerPixel(m_Format)]);
	}

	void Image::SetPixel(int x, int y, const Color& color)
	{
		unsigned char* pix = &m_Pixels[(x + y * m_Size.x) * GetBytesPerPixel(m_Format)];

		unsigned char Components[4] = {color.GetBlue(), color.GetGreen(), color.GetRed(), color.GetAlpha()};
		ConvertPixel(PXF_A8R8G8B8, Components, m_Format, pix);
	}

	void Image::GetPixel(int x, int y, unsigned char* pix) const
	{
		const unsigned char* begin = &m_Pixels[(x + y * m_Size.x) * GetBytesPerPixel(m_Format)];
		std::copy(begin, begin + GetBytesPerPixel(m_Format), pix);
	}

	Color Image::GetPixel(int x, int y) const
	{
		unsigned char components[4];

		const unsigned char* pix = &m_Pixels[(x + y * m_Size.x) * GetBytesPerPixel(m_Format)];

		ConvertPixel(m_Format, pix, PXF_A8R8G8B8, components);

		return Color(components[2], components[1], components[0], components[3]);
	}

	void Image::CopyImage(const Image& src)
	{
		if (m_Size == src.m_Size)
		{
			if (m_Format == src.m_Format)
			{
				m_Pixels = src.m_Pixels;
			}
			else
			{
				const unsigned char* srcPix  = &src.m_Pixels[0];
				unsigned char*       destPix = &m_Pixels[0];
				unsigned int         srcBpp  = GetBytesPerPixel(src.m_Format);
				unsigned int         destBpp = GetBytesPerPixel(m_Format);

				for (int i = 0; i < m_Size.x; ++i)
					for (int j = 0; j < m_Size.y; ++j)
					{
						ConvertPixel(src.m_Format, srcPix, m_Format, destPix);
						srcPix  += srcBpp;
						destPix += destBpp;
					}
			}
		}
		else
		{

			vec2 step(static_cast<float>(src.m_Size.x) / m_Size.x, static_cast<float>(src.m_Size.y) / m_Size.y);

			if (m_Format == src.m_Format)
			{
				unsigned char pixel[16];
				for (int i = 0; i < m_Size.x; ++i)
					for (int j = 0; j < m_Size.y; ++j)
					{
						src.GetPixel(static_cast<int>(i * step.x), static_cast<int>(j * step.y), pixel);
						SetPixel(i, j, pixel);
					}
			}
			else
			{
				unsigned char srcPix[16], destPix[16];
				for (int i = 0; i < m_Size.x; ++i)
					for (int j = 0; j < m_Size.y; ++j)
					{
						src.GetPixel(static_cast<int>(i * step.x), static_cast<int>(j * step.y), srcPix);
						ConvertPixel(src.m_Format, srcPix, m_Format, destPix);
						SetPixel(i, j, destPix);
					}
			}
		}
	}

	Image Image::SubImage(const AgmdMaths::Rectangle& rect) const
	{
		Assert(AgmdMaths::Rectangle(0, 0, m_Size.x, m_Size.y).Intersects(rect) == INT_IN);

		// Création de la sous-image à remplir
		Image Img(ivec2(rect.Width(), rect.Height()), m_Format);

		// Calcul de variables temporaires
		const unsigned char* src       = &m_Pixels[(rect.Left() + rect.Top() * m_Size.x) * GetBytesPerPixel(m_Format)];
		unsigned char*       dest      = &Img.m_Pixels[0];
		const unsigned int   srcPitch  = m_Size.x * GetBytesPerPixel(m_Format);
		const unsigned int   destPitch = Img.m_Size.x * GetBytesPerPixel(Img.m_Format);

		// Copie des pixels de l'image originale dans la sous-image
		for (int i = rect.Left(); i < rect.Right(); ++i)
		{
			std::copy(src, src + destPitch, dest);
			src  += srcPitch;
			dest += destPitch;
		}

		return Img;
	}


	/////////////////////////////////////////////////////////////
	/// Retourne l'image (symétrie verticale)
	///
	////////////////////////////////////////////////////////////
	void Image::Flip()
	{
		return;
		int bpp = GetBytesPerPixel(m_Format);

		for (int j = 0; j < m_Size.y / 2; ++j)
		{
			std::swap_ranges(&m_Pixels[j * m_Size.x * bpp],
							 &m_Pixels[(j + 1) * m_Size.x * bpp - 1],
							 &m_Pixels[(m_Size.y - j - 1) * m_Size.x * bpp]);
		}
	}

	void Image::Mirror()
	{
		int Bpp = GetBytesPerPixel(m_Format);

		for (int i = 0; i < m_Size.x / 2; ++i)
			for (int j = 0; j < m_Size.y; ++j)
			{
				std::swap_ranges(&m_Pixels[(i + j * m_Size.x) * Bpp],
								 &m_Pixels[(i + j * m_Size.x + 1) * Bpp],
								 &m_Pixels[(m_Size.x - i - 1 + j * m_Size.x) * Bpp]);
			}
	}


}
