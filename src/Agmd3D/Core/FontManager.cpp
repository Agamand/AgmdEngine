/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/FontManager.h>
#include <Core/GraphicString.h>
#include <Core/Renderer.h>
#include <Core/Texture/Texture.h>
#include <Core/Texture/Image.h>
#include <Core/MatStack.h>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <Debug/Logger.h>
#include <Debug/New.h>
SINGLETON_IMPL(Agmd::FontManager);

namespace Agmd
{
    FontManager::FontManager()
    {
        m_program.LoadFromFile("Shader/text.glsl");
    }

    FontManager::~FontManager()
    {
        UnloadFonts();
    }

    void FontManager::Initialize()
    {
        TDeclarationElement decl[] =
        {
            {0, ELT_USAGE_POSITION,  ELT_TYPE_FLOAT4},
            {0, 11, ELT_TYPE_INT}
        };

        m_Declaration = Renderer::Get().CreateVertexDeclaration(decl);

        m_VertexBuffer = Renderer::Get().CreateVertexBuffer<TVertex>(4, BUF_STATIC);

        TVertex* vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

        vertices[0].position = vec4(0,0,0,1);
        vertices[1].position = vec4(1,0,0,1);
        vertices[2].position = vec4(0,1,0,1);
        vertices[3].position = vec4(1,1,0,1);

        vertices[0].vertexId = 0;
        vertices[1].vertexId = 1;
        vertices[2].vertexId = 2;
        vertices[3].vertexId = 3;
        
        m_VertexBuffer.Unlock();

        std::vector<TIndex> Indices;
        Indices.push_back(0);
        Indices.push_back(1);
        Indices.push_back(2);
        Indices.push_back(1);
        Indices.push_back(3);
        Indices.push_back(2);

        m_IndexBuffer = Renderer::Get().CreateIndexBuffer((int)Indices.size(), 0, &Indices[0]);
    }

    void FontManager::UnloadFonts()
    {
        m_Fonts.clear();
    }

    void FontManager::LoadFont(const std::string& fontName, int quality)
    {
        if (m_Fonts.find(fontName) != m_Fonts.end())
            return;

        int texSize = quality * 16;

        HDC hdc = CreateCompatibleDC(NULL);
        if (!hdc)
            throw LoadingFailed(fontName, "Impossible de charger la police (erreur dans CreateCompatibleDC)");

        BITMAPINFO bitmapInfo;
        memset(&bitmapInfo, 0, sizeof(BITMAPINFO));
        bitmapInfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
        bitmapInfo.bmiHeader.biWidth    = texSize;
        bitmapInfo.bmiHeader.biHeight   = texSize;
        bitmapInfo.bmiHeader.biBitCount = 24;
        bitmapInfo.bmiHeader.biPlanes   = 1;

        unsigned char* data = NULL;
        HBITMAP bitmapHandle = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, reinterpret_cast<void**>(&data), NULL, 0);
        if (!bitmapHandle)
            throw LoadingFailed(fontName, "Impossible de charger la police (erreur dans CreateDIBSection)");

        // Load font
        HFONT fontHandle = CreateFont(quality, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, fontName.c_str());
        if (!fontHandle)
            throw LoadingFailed(fontName, "Impossible de charger la police (erreur dans CreateFont)");

        SelectObject(hdc, bitmapHandle);
        SelectObject(hdc, fontHandle);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(255, 255, 255));

        ivec2 charSize[256];
        char character = 0;
        for (int j = 0; j < 16; ++j)
            for (int i = 0; i < 16; ++i, ++character)
            {
 
                SIZE size;
                GetTextExtentPoint32(hdc, &character, 1, &size);
                charSize[i + j * 16].x = size.cx;
                charSize[i + j * 16].y = size.cy;

                RECT rect = {i * quality, j * quality, (i + 1) * quality, (j + 1) * quality};
                DrawText(hdc, &character, 1, &rect, DT_LEFT);
            }

        Image imgFont(ivec2(texSize, texSize), PXF_A8L8);
        for (int i = 0; i < texSize; ++i)
            for (int j = 0; j < texSize; ++j)
            {
                unsigned char* CurPixel = data + (i + j * texSize) * 3;
                imgFont.SetPixel(i, j, Color(CurPixel[0], CurPixel[1], CurPixel[2], CurPixel[0]));
            }

        DeleteObject(fontHandle);
        DeleteObject(bitmapHandle);
        DeleteDC(hdc);


        m_Fonts[fontName].texture.CreateFromImage(imgFont, PXF_A8L8, TEX_NOMIPMAP, fontName);

        std::copy(charSize, charSize + 256, m_Fonts[fontName].charSize);

        Logger::Log(LOGNORMAL,"Chargement de la police : %s ",fontName.c_str());
    }

    void FontManager::DrawString(const GraphicString& str)
    {

        if (str.m_Text == "")
            return;

        if (!m_Declaration)
            Initialize();

        if (m_Fonts.find(str.m_Font) == m_Fonts.end())
            LoadFont(str.m_Font);

        const TFont& curFont = m_Fonts[str.m_Font];

        float ratio = str.m_Size * 16.0f / curFont.texture.GetSize().x;
        float offset  = 0.5f / curFont.texture.GetSize().x;
        
        float x = static_cast<float>(str.m_Position.x);
        float y = static_cast<float>(str.m_Position.y);
        uint32 color = Renderer::Get().ConvertColor(str.m_color);

        
        Renderer::Get().Enable(RENDER_ZTEST, false);
        Renderer::Get().SetDeclaration(m_Declaration);
        Renderer::Get().SetTexture(0, curFont.texture.GetTexture());
        Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
        Renderer::Get().SetIndexBuffer(m_IndexBuffer);
        Renderer::Get().SetCurrentProgram(m_program.GetShaderProgram());
        Renderer::Get().GetCurrentProgram()->SetParameter("u_size", str.m_Size);
        Renderer::Get().GetCurrentProgram()->SetParameter("u_offset", offset);

        int nbChars = 0;
        for (std::string::const_iterator i = str.m_Text.begin(); (i != str.m_Text.end()) && (nbChars < nbCharMax); ++i)
        {
            unsigned char c = *i;

            switch (c)
            {
                // Saut de ligne
                case '\n' :
                    x  = static_cast<float>(str.m_Position.x);
                    y += curFont.charSize['\n'].y * ratio;
                    continue;

                // Retour au début de ligne
                case '\r' :
                    x = static_cast<float>(str.m_Position.x);
                    continue;

                // Tabulation horizontale
                case '\t' :
                    x += 4 * curFont.charSize[' '].x * ratio;
                    continue;

                // Tabulation verticale
                case '\v' :
                    y += 4 * curFont.charSize['\n'].y * ratio;
                    continue;

                // Espace
                case ' ' :
                    x += curFont.charSize[' '].x * ratio;
                    continue;
            }
            
            MatStack::push(translate(mat4(1.0f),vec3(x,y,0)));
            Renderer::Get().GetCurrentProgram()->SetParameter("u_char",(int)c);
            Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 0, 6);
            MatStack::pop();

            x += curFont.charSize[c].x * ratio;
            ++nbChars;
        }

        Renderer::Get().SetCurrentProgram(NULL);
        //Renderer::Get().Enable(RENDER_ZTEST, true);
    }

    ivec2 FontManager::GetStringPixelSize(const GraphicString& str)
    {
        if (m_Fonts.find(str.m_Font) == m_Fonts.end())
            LoadFont(str.m_Font);

        const TFont& curFont = m_Fonts[str.m_Font];
        const float  ratio   = str.m_Size * 16.0f / curFont.texture.GetSize().x;

        std::vector<int> lengths;

        ivec2 size(0, str.m_Size);

        for (std::string::const_iterator i = str.m_Text.begin(); i != str.m_Text.end(); ++i)
        {
            unsigned char c = *i;

            switch (c)
            {
                // Retour à la ligne
                case '\n' :
                    lengths.push_back(size.x);
                    size.y += str.m_Size;
                    size.x = 0;
                    break;

                // Retour au début de ligne
                case '\r' :
                    lengths.push_back(size.x);
                    size.x = 0;
                    break;

                // Tabulation horizontale
                case '\t' :
                    size.x += (int)(4 * curFont.charSize[' '].x * ratio);
                    break;

                // Tabulation verticale
                case '\v' :
                    size.y += 4 * str.m_Size;
                    break;

                // Défaut
                default :
                    size.x += (int)(curFont.charSize[c].x * ratio);
                    break;
            }
        }

        lengths.push_back(size.x);
        size.x = *std::max_element(lengths.begin(), lengths.end());

        return size;
    }

}
