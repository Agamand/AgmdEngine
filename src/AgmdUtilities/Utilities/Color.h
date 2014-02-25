/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef COLOR_H
#define COLOR_H


#include <CommonDefines.h>
#include <iostream>


namespace AgmdUtilities
{
    class Color
    {
    public :

        Color(a_uint32 Color = 0xFFFFFFFF);

        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

        a_uint8 ToGrey() const;

        a_uint32 ToARGB() const;

        a_uint32 ToABGR() const;

        a_uint32 ToRGBA() const;

        a_uint8 GetAlpha() const;

        a_uint8 GetRed() const;

        a_uint8 GetGreen() const;

        a_uint8 GetBlue() const;

        void SetFloats(float r, float g, float b, float a = 1.0f);
 
        void Set(a_uint8 r, a_uint8 g, a_uint8 b, a_uint8 a = 0xFF);

        void ToFloat(float Dest[]) const;

        bool operator ==(const Color& c) const;

        bool operator !=(const Color& c) const;

        const Color& operator +=(const Color& c);

        const Color& operator -=(const Color& c);

        Color operator +(const Color& c) const;

        Color operator -(const Color& c) const;

        Color operator *(float v) const;

        const Color& operator *=(float v);

        Color operator /(float v) const;

        const Color& operator /=(float v);

        Color Add(const Color& c) const;

        Color Modulate(const Color& c) const;

        static const Color white;
        static const Color black;
        static const Color red;
        static const Color green;
        static const Color blue;

        friend std::istream& operator >>(std::istream& stream, Color& color);
        friend std::ostream& operator <<(std::ostream& stream, const Color& color);

    private :

        void SetInt(int r, int g, int b, int a = 0xFF);

        unsigned long m_Color;
    };

}


#endif //COLOR_H
