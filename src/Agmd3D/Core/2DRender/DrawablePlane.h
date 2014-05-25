#ifndef _DRAWABLEPLANE_H_
#define _DRAWABLEPLANE_H_
#include <Vector2.h>
#include <Core/Texture/Texture.h>
#include <Core/2DRender/LineRenderer.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/MediaManager.h>
#include <vector>
#include <Core/AgmdApp.h>
#include <Config/Export.h>

namespace Agmd
{
	class AGMD3D_EXPORT DrawablePlane : public AgmdApp::InputListener
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

		float degree;
	private:
		std::vector<vec2> m_bufferPoint;
		ShaderProgram m_renderProgram;
		ivec2 m_pixelSize;
		vec2  m_repere;
		Texture m_texture;
		FrameBuffer* m_frame;
		std::vector<LineRenderer*> m_render;
		mat4 m_projection;
		mat4 m_reverse_projection;
		vec2* m_selectedPoint;
		BaseSpline* m_selectedSpline;
		int m_pointIndex;
		int key;
		
		enum KEY
		{
			CTRL =0x1,
			MAJ =0x2
		};
		
	};
}
#endif /* _DRAWABLEPLANE_H_ */
