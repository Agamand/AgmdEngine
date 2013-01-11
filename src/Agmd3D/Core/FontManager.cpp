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
#pragma warning(disable:4996)
SINGLETON_IMPL(Agmd::FontManager);

namespace Agmd
{




FontManager::FontManager()
{

}


FontManager::~FontManager()
{
    UnloadFonts();
}


void FontManager::Initialize()
{
    TDeclarationElement Decl[] =
    {
        {0, ELT_USAGE_POSITION,  ELT_TYPE_FLOAT3},
        {0, ELT_USAGE_DIFFUSE,   ELT_TYPE_COLOR},
        {0, ELT_USAGE_TEXCOORD0, ELT_TYPE_FLOAT2}
    };

    m_Declaration = Renderer::Get().CreateVertexDeclaration(Decl);

    m_VertexBuffer = Renderer::Get().CreateVertexBuffer<TVertex>(4, BUF_STATIC);

   /* TVertex* Vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

    Vertices->Position = vec3(x,y,0);
    VEC3SET(Vertices[NbChars * 4 + 1].Position, x + str.Size,    y,               0);
    VEC3SET(Vertices[NbChars * 4 + 2].Position, x,               y + str.Size,    0);
    VEC3SET(Vertices[NbChars * 4 + 3].Position, x + str.Size,    y + str.Size,    0);

    // Couleur
    Vertices[NbChars * 4 + 0].Diffuse = Color;
    Vertices[NbChars * 4 + 1].Diffuse = Color;
    Vertices[NbChars * 4 + 2].Diffuse = Color;
    Vertices[NbChars * 4 + 3].Diffuse = Color;

    // Coordonnées de texture
    VEC2SET(Vertices[NbChars * 4 + 0].TexCoords, TexUnit * ((c % 16) + 0) + Offset, 1.0f - TexUnit * ((c / 16) + 1) - Offset);
    VEC2SET(Vertices[NbChars * 4 + 1].TexCoords, TexUnit * ((c % 16) + 1) - Offset, 1.0f - TexUnit * ((c / 16) + 1) - Offset);
    VEC2SET(Vertices[NbChars * 4 + 2].TexCoords, TexUnit * ((c % 16) + 0) + Offset, 1.0f - TexUnit * ((c / 16) + 0) + Offset);
    VEC2SET(Vertices[NbChars * 4 + 3].TexCoords, TexUnit * ((c % 16) + 1) - Offset, 1.0f - TexUnit * ((c / 16) + 0) + Offset);
        */

    std::vector<TIndex> Indices;
    Indices.push_back(0);
    Indices.push_back(2);
    Indices.push_back(1);
    Indices.push_back(1);
    Indices.push_back(2);
    Indices.push_back(3);

    m_IndexBuffer = Renderer::Get().CreateIndexBuffer((int)Indices.size(), 0, &Indices[0]);
}

void FontManager::UnloadFonts()
{
    m_Fonts.clear();
}

void FontManager::LoadFont(const std::string& FontName, int Quality)
{
    if (m_Fonts.find(FontName) != m_Fonts.end())
        return;

    int TexSize = Quality * 16;

    HDC Hdc = CreateCompatibleDC(NULL);
    if (!Hdc)
        throw LoadingFailed(FontName, "Impossible de charger la police (erreur dans CreateCompatibleDC)");

    BITMAPINFO BitmapInfo;
    memset(&BitmapInfo, 0, sizeof(BITMAPINFO));
    BitmapInfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    BitmapInfo.bmiHeader.biWidth    = TexSize;
    BitmapInfo.bmiHeader.biHeight   = TexSize;
    BitmapInfo.bmiHeader.biBitCount = 24;
    BitmapInfo.bmiHeader.biPlanes   = 1;

    // Création de la DIB section
    unsigned char* Data = NULL;
    HBITMAP BitmapHandle = CreateDIBSection(Hdc, &BitmapInfo, DIB_RGB_COLORS, reinterpret_cast<void**>(&Data), NULL, 0);
    if (!BitmapHandle)
        throw LoadingFailed(FontName, "Impossible de charger la police (erreur dans CreateDIBSection)");

    // Chargement de la police
    HFONT FontHandle = CreateFont(Quality, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, FontName.c_str());
    if (!FontHandle)
        throw LoadingFailed(FontName, "Impossible de charger la police (erreur dans CreateFont)");

    // Initialisation des couleurs
    SelectObject(Hdc, BitmapHandle);
    SelectObject(Hdc, FontHandle);
    SetBkColor(Hdc, RGB(0, 0, 0));
    SetTextColor(Hdc, RGB(255, 255, 255));

    // Affichage des caractères
    ivec2 CharSize[256];
    char Character = 0;
    for (int j = 0; j < 16; ++j)
        for (int i = 0; i < 16; ++i, ++Character)
        {
            // Stockage de la taille du caractère
            SIZE Size;
            GetTextExtentPoint32(Hdc, &Character, 1, &Size);
            CharSize[i + j * 16].x = Size.cx;
            CharSize[i + j * 16].y = Size.cy;

            // Affichage du caractère
            RECT Rect = {i * Quality, j * Quality, (i + 1) * Quality, (j + 1) * Quality};
            DrawText(Hdc, &Character, 1, &Rect, DT_LEFT);
        }

    // Création d'une image contenant les pixels de la bitmap
    // on est obligé de copier les pixels un à un pour ajouter la composante alpha
    Image ImgFont(ivec2(TexSize, TexSize), PXF_A8L8);
    for (int i = 0; i < TexSize; ++i)
        for (int j = 0; j < TexSize; ++j)
        {
            unsigned char* CurPixel = Data + (i + j * TexSize) * 3;
            ImgFont.SetPixel(i, j, Color(CurPixel[0], CurPixel[1], CurPixel[2], CurPixel[0]));
        }
    //ImgFont.Flip();

    // Destruction des ressources
    DeleteObject(FontHandle);
    DeleteObject(BitmapHandle);
    DeleteDC(Hdc);

    // Création de la texture
    m_Fonts[FontName].Texture.CreateFromImage(ImgFont, PXF_A8L8, TEX_NOMIPMAP, FontName);

    std::copy(CharSize, CharSize + 256, m_Fonts[FontName].CharSize);

    Logger::Log(LOGNORMAL,"Chargement de la police : %s ",FontName.c_str());
}

void FontManager::DrawString(const GraphicString& str)
{

    if (str.Text == "")
        return;

    // Si la partie rendering n'a pas été initialisée, on le fait
    if (!m_Declaration)
        Initialize();

    // Si la police n'a pas été chargée, on le fait
    if (m_Fonts.find(str.Font) == m_Fonts.end())
        LoadFont(str.Font);

    // Récupération de la font à utiliser
    const TFont& CurFont = m_Fonts[str.Font];

    // Variables intermédiaires utilisées pour les calculs
    float         Ratio   = str.Size * 16.0f / CurFont.Texture.GetSize().x;
    float         Offset  = 0.5f / CurFont.Texture.GetSize().x;
    float         TexUnit = 1.0f / 16.0f;
    float         x       = static_cast<float>(str.Position.x);
    float         y       = static_cast<float>(str.Position.y);
    unsigned long Color   = Renderer::Get().ConvertColor(str.color);

    // Verrouillage du vertex buffer
    //TVertex* Vertices = m_VertexBuffer.Lock(0, 0, LOCK_WRITEONLY);

    int NbChars = 0;
    for (std::string::const_iterator i = str.Text.begin(); (i != str.Text.end()) && (NbChars < NbCharMax); ++i)
    {
        // Conversion du caractère en unsigned
        // (pour gérer correctement les caractères ASCII étendus (code > 127))
        unsigned char c = *i;

        // Gestion des caractères spéciaux
        switch (c)
        {
            // Saut de ligne
            case '\n' :
                x  = static_cast<float>(str.Position.x);
                y += CurFont.CharSize['\n'].y * Ratio;
                continue;

            // Retour au début de ligne
            case '\r' :
                x = static_cast<float>(str.Position.x);
                continue;

            // Tabulation horizontale
            case '\t' :
                x += 4 * CurFont.CharSize[' '].x * Ratio;
                continue;

            // Tabulation verticale
            case '\v' :
                y += 4 * CurFont.CharSize['\n'].y * Ratio;
                continue;

            // Espace
            case ' ' :
                x += CurFont.CharSize[' '].x * Ratio;
                continue;
        }

        /*// Position
        VEC3SET(Vertices[NbChars * 4 + 0].Position, x,               y,               0);
        VEC3SET(Vertices[NbChars * 4 + 1].Position, x + str.Size,    y,               0);
        VEC3SET(Vertices[NbChars * 4 + 2].Position, x,               y + str.Size,    0);
        VEC3SET(Vertices[NbChars * 4 + 3].Position, x + str.Size,    y + str.Size,    0);

        // Couleur
        Vertices[NbChars * 4 + 0].Diffuse = Color;
        Vertices[NbChars * 4 + 1].Diffuse = Color;
        Vertices[NbChars * 4 + 2].Diffuse = Color;
        Vertices[NbChars * 4 + 3].Diffuse = Color;

        // Coordonnées de texture
        VEC2SET(Vertices[NbChars * 4 + 0].TexCoords, TexUnit * ((c % 16) + 0) + Offset, 1.0f - TexUnit * ((c / 16) + 1) - Offset);
        VEC2SET(Vertices[NbChars * 4 + 1].TexCoords, TexUnit * ((c % 16) + 1) - Offset, 1.0f - TexUnit * ((c / 16) + 1) - Offset);
        VEC2SET(Vertices[NbChars * 4 + 2].TexCoords, TexUnit * ((c % 16) + 0) + Offset, 1.0f - TexUnit * ((c / 16) + 0) + Offset);
        VEC2SET(Vertices[NbChars * 4 + 3].TexCoords, TexUnit * ((c % 16) + 1) - Offset, 1.0f - TexUnit * ((c / 16) + 0) + Offset);
        
        */
        x += CurFont.CharSize[c].x * Ratio;
        ++NbChars;
    }

    // Déverrouillage du vertex buffer
    //m_VertexBuffer.Unlock();

    // Paramètrage du rendu
    MatStack::push(mat4(1.0f));
    Renderer::Get().SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
    //Renderer::Get().SetupTextureUnit(0, TXO_COLOR_MODULATE, TXA_TEXTURE, TXA_DIFFUSE);
    //Renderer::Get().SetupTextureUnit(0, TXO_ALPHA_MODULATE, TXA_TEXTURE, TXA_DIFFUSE);
    Renderer::Get().Enable(RENDER_ALPHABLEND, true);
    Renderer::Get().Enable(RENDER_ZTEST, false);

    // Affichage du texte
    Renderer::Get().SetDeclaration(m_Declaration);
    Renderer::Get().SetTextureFlag(TEXTURE_UNIT_0);
    Renderer::Get().SetTexture(0, CurFont.Texture.GetTexture());
    Renderer::Get().SetVertexBuffer(0, m_VertexBuffer);
    Renderer::Get().SetIndexBuffer(m_IndexBuffer);
    Renderer::Get().DrawIndexedPrimitives(PT_TRIANGLELIST, 0, NbChars * 2*3);

    // Rétablissement des options de rendu
    Renderer::Get().Enable(RENDER_ZTEST, true);
    Renderer::Get().Enable(RENDER_ALPHABLEND, false);
    MatStack::pop();
}



/////////////////////////////////////////////////////////////
/// Renvoie la taille d'une chaîne graphique en pixels
///
/// \param String : Chaîne graphique
///
/// \return Taille du texte en pixels
///
////////////////////////////////////////////////////////////
ivec2 FontManager::GetStringPixelSize(const GraphicString& str)
{
    // Si la police n'a pas été chargée, on le fait
    if (m_Fonts.find(str.Font) == m_Fonts.end())
        LoadFont(str.Font);

    // Récupération de la font à utiliser
    const TFont& CurFont = m_Fonts[str.Font];
    const float  Ratio   = str.Size * 16.0f / CurFont.Texture.GetSize().x;

    // Tableau contenant la longueur de chaque ligne, afin de déterminer à la fin la plus longue
    std::vector<int> Lengths;

    // Valeur de retour
    ivec2 Size(0, str.Size);

    // Parcours de la chaîne de caractères
    for (std::string::const_iterator i = str.Text.begin(); i != str.Text.end(); ++i)
    {
        // Conversion du caractère en unsigned
        // (pour gérer correctement les caractères ASCII étendus (code > 127))
        unsigned char c = *i;

        switch (c)
        {
            // Retour à la ligne
            case '\n' :
                Lengths.push_back(Size.x);
                Size.y += str.Size;
                Size.x = 0;
                break;

            // Retour au début de ligne
            case '\r' :
                Lengths.push_back(Size.x);
                Size.x = 0;
                break;

            // Tabulation horizontale
            case '\t' :
                Size.x += (int)(4 * CurFont.CharSize[' '].x * Ratio);
                break;

            // Tabulation verticale
            case '\v' :
                Size.y += 4 * str.Size;
                break;

            // Défaut
            default :
                Size.x += (int)(CurFont.CharSize[c].x * Ratio);
                break;
        }
    }

    // On prend la longueur de la ligne la plus longue
    Lengths.push_back(Size.x);
    Size.x = *std::max_element(Lengths.begin(), Lengths.end());

    return Size;
}

} // namespace Yes
