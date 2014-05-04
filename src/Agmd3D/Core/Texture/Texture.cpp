/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Texture/Texture.h>
#include <Core/Texture/TextureBase.h>
#include <Core/MediaManager.h>
#include <Core/ResourceManager.h>
#include <Core/Driver.h>
#include <Core/Texture/Image.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Utilities/PixelUtils.h>
#include <Utilities/Util.h>
#include <Debug/Logger.h>
#include <Debug/New.h>

#include <time.h>

namespace Agmd
{

    void Texture::Create(const ivec2& size, TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name)
    {
        Image image[6] = {Image(size,format)};
        switch(type)
        {
        case TEXTURE_2D:
            CreateFromImage(image[0], format, flags, name);
            break;
        case TEXTURE_CUBE:
            CreateFromImage(image,format,flags,name);
            break;
        }
    }

    void Texture::CreateFromFile(const std::string& filename, TPixelFormat format, unsigned long flags)
    {
        m_Texture = ResourceManager::Instance().Get<TextureBase>(filename);

        if (!m_Texture)
        {
            SmartPtr<Image> image = MediaManager::Instance().LoadMediaFromFile<Image>(filename);

            Load(*image, format, TEXTURE_2D, flags, filename);
        }
    }

    void Texture::CreateFromImage(const Image& image, TPixelFormat format, unsigned long flags, const std::string& name)
    {
        m_Texture = ResourceManager::Instance().Get<TextureBase>(name);

        if (!m_Texture)
            Load(image, format, TEXTURE_2D, flags, name);
    }

    void Texture::CreateFromFile(const std::string filename[], TPixelFormat format, unsigned long flags)
    {
        //m_Texture = ResourceManager::Instance().Get<TextureBase>(filename);

        if (!m_Texture)
        {
            Image image[6];
            for(a_int32 i = 0; i < 6; i++)
                image[i] = *MediaManager::Instance().LoadMediaFromFile<Image>(filename[i]);

           Load(image,format,TEXTURE_CUBE,flags,filename[0]);
        }
    }

    void Texture::CreateFromImage(const Image image[], TPixelFormat format, unsigned long flags, const std::string& name)
    {
        m_Texture = ResourceManager::Instance().Get<TextureBase>(name);

        if (!m_Texture)
            Load(image, format, TEXTURE_CUBE, flags, name);
    }

    void Texture::Load(const Image& pixels, TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name)
    {
        if (FormatCompressed(format) && !Driver::Get().HasCapability(CAP_DXT_COMPRESSION))
        {
            format = PXF_A8R8G8B8;
            Logger::Log(LOGNORMAL,"WARNING - Format compressé choisi, mais non supporté par le système de rendu. Le format utilisé sera PXF_A8R8G8B8. %s", (name != "" ? " (texture : \"" + name + "\")" : "").c_str());
        }

        ivec2 size(NearestPowerOfTwo(pixels.GetSize().x), NearestPowerOfTwo(pixels.GetSize().y));
        if ((size != pixels.GetSize()) && !Driver::Get().HasCapability(CAP_TEX_NON_POWER_2))
        {
            Logger::Log(LOGNORMAL,"WARNING - Dimensions de texture non-puissances de 2, mais non supporté par le système de rendu. Les dimensions seront ajustées. (%dx%d->%dx%d)", pixels.GetSize().x, pixels.GetSize().y, size.x, size.y);
        }
        else
        {
            size = pixels.GetSize();
        }

        try
        {
            m_Texture = Driver::Get().CreateTexture(size, format, type, flags);
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

    void Texture::Load(const Image image[], TPixelFormat format, TTextureType type, unsigned long flags, const std::string& name)
    {
        const Image &pixels = image[0];
        if (FormatCompressed(format) && !Driver::Get().HasCapability(CAP_DXT_COMPRESSION))
        {
            format = PXF_A8R8G8B8;
            Logger::Log(LOGNORMAL,"WARNING - Format compressé choisi, mais non supporté par le système de rendu. Le format utilisé sera PXF_A8R8G8B8. %s", (name != "" ? " (texture : \"" + name + "\")" : "").c_str());
        }

        ivec2 size(NearestPowerOfTwo(pixels.GetSize().x), NearestPowerOfTwo(pixels.GetSize().y));
        if ((size != pixels.GetSize()) && !Driver::Get().HasCapability(CAP_TEX_NON_POWER_2))
        {
            Logger::Log(LOGNORMAL,"WARNING - Dimensions de texture non-puissances de 2, mais non supporté par le système de rendu. Les dimensions seront ajustées. (%dx%d->%dx%d)", pixels.GetSize().x, pixels.GetSize().y, size.x, size.y);
        }
        else
        {
            size = pixels.GetSize();
        }

        try
        {
            m_Texture = Driver::Get().CreateTexture(size, format, type, flags);
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
			Image * img = &GetPixels();
			for(int i = 0; i < 6; i++)
				img[i].CopyImage(image[i]);
        Update();
    }

    void Texture::SaveToFile(const std::string& filename) const
    {
        //MediaManager::Instance().SaveMediaToFile(&m_Texture->m_Data, filename);
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
        return *m_Texture->getPixels();
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
    

    /*void Texture::SetPixel(const std::string& filename,uint32 face)
    {
        if(face > 5)
            return;

        SmartPtr<Image> image = MediaManager::Instance().LoadMediaFromFile<Image>(filename);
        SetPixel(*image,face);
    }

    void Texture::SetPixel(const Image& image,uint32 face)
    {
        if(face > 5)
            return;
        m_Texture->m_CubeData[face] = image;
        Update();
    }*/
    BaseShaderProgram* Texture::s_addTexture = NULL;
    BaseShaderProgram* Texture::s_prodTexture = NULL;
    BaseShaderProgram* Texture::s_renderTexture = NULL;
    BaseShaderProgram* Texture::s_randomTexture = NULL;
    FrameBuffer* Texture::s_framebuffer = NULL;

    void Texture::TextureAdd(Texture output, Texture input1, Texture input2)
    {
        Driver& render = Driver::Get();
        if(!s_addTexture)
        {
            s_addTexture = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/add_tex.glsl");
        }
        if(!s_framebuffer)
            s_framebuffer = render.CreateFrameBuffer();

        s_framebuffer->SetTexture(output,COLOR_ATTACHMENT);
        render.SetTexture(0,input1.GetTexture());
        render.SetTexture(1,input2.GetTexture());
        s_framebuffer->Clear();
        s_framebuffer->Bind();
        render.SetCurrentProgram(s_addTexture);
        Fast2DSurface::Instance().Draw();
        render.SetCurrentProgram(nullptr);
        s_framebuffer->UnBind();
    }

    void Texture::TextureProd(Texture output, Texture input1, Texture input2)
    {
        Driver& render = Driver::Get();
        if(!s_prodTexture)
        {
            s_prodTexture = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/prod_tex.glsl");
        }
        if(!s_framebuffer)
            s_framebuffer = render.CreateFrameBuffer();

        s_framebuffer->SetTexture(output,COLOR_ATTACHMENT);
        render.SetTexture(0,input1.GetTexture());
        render.SetTexture(1,input2.GetTexture());
        s_framebuffer->Clear();
        s_framebuffer->Bind();
        render.SetCurrentProgram(s_prodTexture);
        Fast2DSurface::Instance().Draw();
        render.SetCurrentProgram(nullptr);
        s_framebuffer->UnBind();
    }

    void Texture::TextureRender(Texture input)
    {
        Driver& render = Driver::Get();

        if(!s_renderTexture)
            s_renderTexture = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/render_tex.glsl");
        render.SetViewPort(ivec2(),render.GetScreen());
        render.SetTexture(0,input.GetTexture());
        render.SetCurrentProgram(s_renderTexture);
        Fast2DSurface::Instance().Draw();
        render.SetCurrentProgram(nullptr);
    }

    void Texture::TextureRandom()
    {
        Driver& render = Driver::Get();

        if(!s_randomTexture)
            s_randomTexture = MediaManager::Instance().LoadMediaFromFile<BaseShaderProgram>("Shader/rand_tex.glsl");

        int seed = clock();

        render.SetCurrentProgram(s_randomTexture);
        render.GetCurrentProgram()->SetParameter("seed",(float)seed);
        Fast2DSurface::Instance().Draw();
        render.SetCurrentProgram(nullptr);
    }

    void Texture::BeginRenderToTexture(const Texture& texture)
    {
        if(!s_framebuffer)
            s_framebuffer = Driver::Get().CreateFrameBuffer();
        s_framebuffer->SetTexture(texture,COLOR_ATTACHMENT);
        s_framebuffer->Clear(CLEAR_COLOR);
        s_framebuffer->Bind();
    }
    void Texture::EndRenderToTexture()
    {
        if(s_framebuffer)
            s_framebuffer->UnBind();
    }

    void Texture::BeginRenderToCubeMap(const Texture& texture, TAttachment attachment, int face)
    {
        if(!s_framebuffer)
            s_framebuffer = Driver::Get().CreateFrameBuffer();
        if(face < 0)
            s_framebuffer->SetTexture(texture,attachment);
        else s_framebuffer->SetTextureCube(texture,attachment,face);
        s_framebuffer->Clear(attachment == DEPTH_ATTACHMENT ? CLEAR_DEPTH : CLEAR_COLOR);
        s_framebuffer->Bind();
    }
    void Texture::EndRenderToCubeMap()
    {
        if(s_framebuffer)
            s_framebuffer->UnBind();
    }

    TTextureType Texture::GetType() const
    {
        return m_Texture->GetType();
    }

}
