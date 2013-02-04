/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ASLIDER_H_
#define _ASLIDER_H_

#include <Config/Export.h>
#include <Core/GUI/AWidget.h>
#include <Core/Texture/Texture.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Shader/BaseShaderProgram.h>
#include <Core/MediaManager.h>

namespace Agmd
{
    class AGMD3D_EXPORT ASlider : public AWidget
    {
    public:
        ASlider(AWidget* parent);
        virtual ~ASlider();
        virtual uint32 OnClick(ivec2& pos_mouse, uint32 mouseState);
        virtual uint32 OnMouseOver();
        virtual uint32 OnMouseMove(ivec2& pos_diff, uint32 mouseState);
        virtual uint32 OnKey(char key);
        virtual void OnSizeChanged();
        virtual void OnPosChanged();

        virtual void Draw() const;

        virtual bool In(ivec2& pos_mouse);

        void SetCursor(float value);
    private:

        void BuildSlider();
        struct TVertex
        {
            vec3     Position;
            uint32   Diffuse;
            vec2     TexCoords0; 
        };

        typedef unsigned short TIndex;

        Buffer<TVertex>     m_VertexBuffer;
        Buffer<TIndex>      m_IndexBuffer;
        DeclarationPtr      m_Declaration;
        Texture             m_Texture;
        Texture             m_Font;
        BaseShaderProgram*  m_Program;
        float               m_cursor; // range [0.0f-1.0f]
        bool                hold; // hold = true if mouse is hold the cursor else hold = false
    };
}

#endif /* _ASLIDER_H_ */