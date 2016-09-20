/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Utilities/color.h>
#include <Debug/New.h>


namespace AgmdUtilities
{

    const Color Color::white(255, 255, 255);
    const Color Color::black(0, 0, 0);
    const Color Color::red(255, 0, 0);
    const Color Color::green(0, 255, 0);
    const Color Color::blue(0, 0, 255);

    Color::Color(a_uint32 color) :
    m_Color(color)
    {}

    Color::Color(a_uint8 r, a_uint8 g, a_uint8 b, a_uint8 a)
    {
        Set(r, g, b, a);
    }

    void Color::SetFloats(float r, float g, float b, float a)
    {
        int R = static_cast<int>(r * 255.0f);
        int G = static_cast<int>(g * 255.0f);
        int B = static_cast<int>(b * 255.0f);
        int A = static_cast<int>(a * 255.0f);

        SetInt(R, G, B, A);
    }


    void Color::Set(a_uint8 r, a_uint8 g, a_uint8 b, a_uint8 a)
    {
        m_Color = (a << 24) | (r << 16) | (g << 8) | (b << 0);
    }


    void Color::SetInt(int r, int g, int b, int a)
    {
        a_uint8 R = (r >= 0) ? (r <= 255 ? r : 255) : 0;
        a_uint8 G = (g >= 0) ? (g <= 255 ? g : 255) : 0;
        a_uint8 B = (b >= 0) ? (b <= 255 ? b : 255) : 0;
        a_uint8 A = (a >= 0) ? (a <= 255 ? a : 255) : 0;

        Set(R, G, B, A);
    }


    bool Color::operator ==(const Color& c) const
    {
        return m_Color == c.m_Color;
    }

    bool Color::operator!=(const Color& c) const
    {
        return !(*this == c);
    }

    const Color& Color::operator +=(const Color& c)
    {
        int R = GetRed()   + c.GetRed();
        int G = GetGreen() + c.GetGreen();
        int B = GetBlue()  + c.GetBlue();
        int A = GetAlpha() + c.GetAlpha();

        SetInt(R, G, B, A);

        return *this;
    }

    const Color& Color::operator -=(const Color& c)
    {
        int R = GetRed()   - c.GetRed();
        int G = GetGreen() - c.GetGreen();
        int B = GetBlue()  - c.GetBlue();
        int A = GetAlpha() - c.GetAlpha();

        SetInt(R, G, B, A);

        return *this;
    }

    Color Color::operator +(const Color& c) const
    {
        int R = GetRed()   + c.GetRed();
        int G = GetGreen() + c.GetGreen();
        int B = GetBlue()  + c.GetBlue();
        int A = GetAlpha() + c.GetAlpha();

        Color Ret;
        Ret.SetInt(R, G, B, A);

        return Ret;
    }

    Color Color::operator -(const Color& c) const
    {
        int R = GetRed()   - c.GetRed();
        int G = GetGreen() - c.GetGreen();
        int B = GetBlue()  - c.GetBlue();
        int A = GetAlpha() - c.GetAlpha();

        Color Ret;
        Ret.SetInt(R, G, B, A);

        return Ret;
    }

    Color Color::operator *(float v) const
    {
        int R = static_cast<int>(GetRed()   * v);
        int G = static_cast<int>(GetGreen() * v);
        int B = static_cast<int>(GetBlue()  * v);
        int A = static_cast<int>(GetAlpha() * v);

        Color Ret;
        Ret.SetInt(R, G, B, A);

        return Ret;
    }

    const Color& Color::operator *=(float v)
    {
        int R = static_cast<int>(GetRed()   * v);
        int G = static_cast<int>(GetGreen() * v);
        int B = static_cast<int>(GetBlue()  * v);
        int A = static_cast<int>(GetAlpha() * v);

        SetInt(R, G, B, A);

        return *this;
    }

    Color Color::operator /(float v) const
    {
        return *this * (1.0f / v);
    }

    const Color& Color::operator /=(float v)
    {
        return *this *= (1.0f / v);
    }

    Color Color::Add(const Color& c) const
    {
        return *this + c;
    }

    Color Color::Modulate(const Color& c) const
    {
        a_uint8 R = static_cast<a_uint8>(GetRed()   * c.GetRed()   / 255);
        a_uint8 G = static_cast<a_uint8>(GetGreen() * c.GetGreen() / 255);
        a_uint8 B = static_cast<a_uint8>(GetBlue()  * c.GetBlue()  / 255);
        a_uint8 A = static_cast<a_uint8>(GetAlpha() * c.GetAlpha() / 255);

        return Color(R, G, B, A);
    }

    a_uint8 Color::GetAlpha() const
    {
        return static_cast<a_uint8>((m_Color & 0xFF000000) >> 24);
    }

    a_uint8 Color::GetRed() const
    {
        return static_cast<a_uint8>((m_Color & 0x00FF0000) >> 16);
    }

    a_uint8 Color::GetGreen() const
    {
        return static_cast<a_uint8>((m_Color & 0x0000FF00) >> 8);
    }

    a_uint8 Color::GetBlue() const
    {
        return static_cast<a_uint8>((m_Color & 0x000000FF) >> 0);
    }

    void Color::ToFloat(float Dest[]) const
    {
        Dest[0] = GetRed()   / 255.0f;
        Dest[1] = GetGreen() / 255.0f;
        Dest[2] = GetBlue()  / 255.0f;
        Dest[3] = GetAlpha() / 255.0f;
    }

    a_uint8 Color::ToGrey() const
    {
        return static_cast<a_uint8>(GetRed() * 0.30 + GetGreen() * 0.59 + GetBlue() * 0.11);
    }

    a_uint32 Color::ToARGB() const
    {
        return (GetAlpha() << 24) | (GetRed() << 16) | (GetGreen() << 8) | (GetBlue() << 0);
    }

    a_uint32 Color::ToABGR() const
    {
        return (GetAlpha() << 24) | (GetBlue() << 16) | (GetGreen() << 8) | (GetRed() << 0);
    }

    a_uint32 Color::ToRGBA() const
    {
        return (GetRed() << 24) | (GetGreen() << 16) | (GetBlue() << 8) | (GetAlpha() << 0);
    }

    std::istream& operator >>(std::istream& Stream, Color& color)
    {
        int R, G, B, A;
        Stream >> R >> G >> B >> A;
        color.SetInt(R, G, B, A);

        return Stream;
    }


    std::ostream& operator <<(std::ostream& Stream, const Color& color)
    {
        return Stream << static_cast<int>(color.GetRed())   << " "
                      << static_cast<int>(color.GetGreen()) << " "
                      << static_cast<int>(color.GetBlue())  << " "
                      << static_cast<int>(color.GetAlpha());
    }

}
