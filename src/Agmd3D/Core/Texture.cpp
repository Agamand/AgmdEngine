#include <Core/Texture.h>
#include <Core/TextureBase.h>
#include <Core/MediaManager.h>
#include <Core/ResourceManager.h>
#include <Core/Renderer.h>
#include <Core/Image.h>
#include <Utilities/PixelUtils.h>
#include <Utilities/Util.h>
#include <Debug/Logger.h>
#include <Debug/New.h>

namespace Agmd
{

	void Texture::Create(const ivec2& size, TPixelFormat format, unsigned long flags, const std::string& name)
	{
		CreateFromImage(Image(size, format), format, flags, name);
	}

	void Texture::CreateFromFile(const std::string& filename, TPixelFormat format, unsigned long flags)
	{
		m_Texture = ResourceManager::Instance().Get<TextureBase>(filename);

		if (!m_Texture)
		{
			SmartPtr<Image> image = MediaManager::Instance().LoadMediaFromFile<Image>(filename);

			Load(*image, format, flags, filename);
		}
	}

	void Texture::CreateFromImage(const Image& image, TPixelFormat format, unsigned long flags, const std::string& name)
	{
		m_Texture = ResourceManager::Instance().Get<TextureBase>(name);

		if (!m_Texture)
		   Load(image, format, flags, name);
	}

	void Texture::Load(const Image& pixels, TPixelFormat format, unsigned long flags, const std::string& name)
	{
		if (FormatCompressed(format) && !Renderer::Get().HasCapability(CAP_DXT_COMPRESSION))
		{
			format = PXF_A8R8G8B8;
			Logger::Log(LOGNORMAL,"WARNING - Format compressé choisi, mais non supporté par le système de rendu. Le format utilisé sera PXF_A8R8G8B8. %s\n", (name != "" ? " (texture : \"" + name + "\")" : "").c_str());
		}

		ivec2 size(NearestPowerOfTwo(pixels.GetSize().x), NearestPowerOfTwo(pixels.GetSize().y));
		if ((size != pixels.GetSize()) && !Renderer::Get().HasCapability(CAP_TEX_NON_POWER_2))
		{
			Logger::Log(LOGNORMAL,"WARNING - Dimensions de texture non-puissances de 2, mais non supporté par le système de rendu. Les dimensions seront ajustées. (%dx%d->%dx%d)\n", pixels.GetSize().x, pixels.GetSize().y, size.x, size.y);
		}
		else
		{
			size = pixels.GetSize();
		}

		try
		{
			m_Texture = Renderer::Get().CreateTexture(size, format, flags);
		}
		catch (const std::exception& E)
		{
			throw LoadingFailed(name, E.what());
		}

		if (name != "")
			ResourceManager::Instance().Add(name, m_Texture);

		if (FormatCompressed(format))
			GetPixels() = Image(GetSize(), PXF_A8R8G8B8);

		// Copie des pixels
		GetPixels().CopyImage(pixels);
		Update();
	}

	void Texture::SaveToFile(const std::string& filename) const
	{
		MediaManager::Instance().SaveMediaToFile(&m_Texture->m_Data, filename);
	}

	void Texture::Update(const AgmdMaths::Rectangle& rect)
	{
		if (rect.Width() == -1)
			m_Texture->Update(AgmdMaths::Rectangle(0, 0, GetSize().x, GetSize().y));
		else
			m_Texture->Update(rect);
	}

	Image& Texture::GetPixels()
	{
		return m_Texture->m_Data;
	}

	const ivec2& Texture::GetSize() const
	{
		return m_Texture->m_Size;
	}

	TPixelFormat Texture::GetFormat() const
	{
		return m_Texture->m_Format;
	}

	const std::string& Texture::GetName() const
	{
		return m_Texture->GetName();
	}

	const TextureBase* Texture::GetTexture() const
	{
		return m_Texture;
	}

	bool Texture::operator ==(const Texture& texture) const
	{
		return m_Texture == texture.m_Texture;
	}

	bool Texture::operator !=(const Texture& texture) const
	{
		return !(*this == texture);
	}

}
