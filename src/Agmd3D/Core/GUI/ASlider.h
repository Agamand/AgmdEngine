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
#include <Core/Shader/ShaderProgram.h>
#include <Core/MediaManager.h>

namespace Agmd
{
    class AGMD3D_EXPORT ASlider : public AWidget
    {
    public:
        ASlider(AWidget* parent);
        virtual ~ASlider();
        virtual a_uint32 OnClick(ivec2& pos_mouse, a_uint32 mouseState);
        virtual a_uint32 OnMouseOver();
        virtual a_uint32 OnMouseMove(ivec2& pos_diff, a_uint32 mouseState);
        virtual a_uint32 OnKey(char key);
        virtual void OnSizeChanged();
        virtual void OnPosChanged();

        virtual void Draw() const;

        virtual bool In(ivec2& pos_mouse);

        void SetCursor(float value);
		void setValue(float* value,float min,float max);
    private:

        void BuildSlider();
        struct TVertex
        {
            vec3     Position;
            a_uint32   Diffuse;
            vec2     TexCoords0; 
        };

        typedef unsigned short TIndex;
		Transform*          m_transform;
        Buffer<TVertex>     m_VertexBuffer;
        Buffer<TIndex>      m_IndexBuffer;
        DeclarationPtr      m_Declaration;
        Texture             m_Texture;
        Texture             m_Font;
        ShaderProgram       m_Program;
		ShaderProgram       m_ProgramCursor;
        float               m_cursor;
		float*				m_value;
		float				m_max;
		float				m_min;// range [0.0f-1.0f]
        bool                hold; // hold = true if mouse is hold the cursor else hold = false
	
	};
}

#endif /* _ASLIDER_H_ */