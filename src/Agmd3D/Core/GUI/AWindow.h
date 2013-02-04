/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _AWINDOW_H_
#define _AWINDOW_H_

#include <Config/Export.h>
#include <Core/GUI/AWidget.h>
#include <Core/Texture/Texture.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Shader/BaseShaderProgram.h>
#include <Core/MediaManager.h>

namespace Agmd
{
    class AGMD3D_EXPORT AWindow : public AWidget
    {
    public:
        AWindow(AWidget* parent = NULL);
        virtual ~AWindow();

        void SetFont(Texture& font);

        virtual uint32 OnClick(ivec2& pos_mouse, uint32 mouseState);
        virtual uint32 OnMouseOver();
        virtual uint32 OnMouseMove(ivec2& pos_diff, uint32 mouseState);
        virtual uint32 OnKey(char key);
        virtual void OnSizeChanged();
        virtual void OnPosChanged();

        virtual void Draw() const;

        virtual bool In(ivec2& pos_mouse);

        

    private:

        struct TVertex
        {
            vec3     Position;
            uint32   Diffuse;
            vec2     TexCoords0; 
            vec2     TexCoords1;
            vec2     TexCoords2;
            vec2     TexCoords3;
        };

        typedef unsigned short TIndex;

        void BuildWindow();
    

        Buffer<TVertex>     m_VertexBuffer;
        Buffer<TIndex>      m_IndexBuffer;
        DeclarationPtr      m_Declaration;
        Texture             m_Texture;
        Texture             m_Font;
        BaseShaderProgram*  m_Program;

        bool                hold;
        bool                extend;
        Transform*          m_transform;
    };
}

#endif /* _AWINDOW_H_ */