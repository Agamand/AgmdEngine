#ifndef COLOR_H
#define COLOR_H


#include <AgmdDefines.h>
#include <iostream>


namespace AgmdUtilities
{
    class Color
    {
    public :

        Color(uint32 Color = 0xFFFFFFFF);

        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

        uint8 ToGrey() const;

        uint32 ToARGB() const;

        uint32 ToABGR() const;

        uint32 ToRGBA() const;

        uint8 GetAlpha() const;

        uint8 GetRed() const;

        uint8 GetGreen() const;

        uint8 GetBlue() const;

        void SetFloats(float r, float g, float b, float a = 1.0f);
 
        void Set(uint8 r, uint8 g, uint8 b, uint8 a = 0xFF);

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
