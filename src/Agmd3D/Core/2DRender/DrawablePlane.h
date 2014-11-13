#ifndef _DRAWABLEPLANE_H_
#define _DRAWABLEPLANE_H_
#include <Core/AgmdApplication.h>
#include <Vector2.h>
#include <Core/Texture/Texture.h>
#include <Core/2DRender/LineRenderer.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/MediaManager.h>
#include <Container/Vector.h>

#include <Config/Export.h>
#include <core/gui/ASlider.h>

namespace Agmd
{
	class AGMD3D_EXPORT DrawablePlane : public AgmdApplication::InputListener , public ASlider::ASliderListener
	{
	public:
		DrawablePlane(ivec2 pixelSize, vec2 repere);
		void addSpline(LineRenderer* render)
		{
			m_render.push_back(render);
		}

		void render();
		const Texture& getTexture(){ return m_texture;}

		virtual void OnClick( int click,int state, const vec2& pos, bool up );

		virtual void OnKey( char key, bool up );

		virtual void OnMouseMotion( const vec2& pos );
		void clear();

		virtual void valueUpdate( float value,float cursor );
		a_vector<LineRenderer*>& getRender()
		{
			return m_render;
		}
		vec2 getPositionFromScreenSpace(vec2 pos);
		float degree;
	private:
		a_vector<vec2> m_bufferPoint;
		ShaderProgram m_renderProgram;
		ivec2 m_pixelSize;
		vec2  m_repere;
		Texture m_texture;
		FrameBuffer* m_frame;
		a_vector<LineRenderer*> m_render;
		mat4 m_projection;
		mat4 m_reverse_projection;
		vec2* m_selectedPoint;
		BaseSpline* m_selectedSpline;
		int m_pointIndex;
		int key;
		bool rightDown;
		a_vector<ASlider*> m_slider;
		enum KEY
		{
			CTRL =0x1,
			MAJ =0x2
		};
		
	};
}
#endif /* _DRAWABLEPLANE_H_ */
