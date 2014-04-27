#include <Core/2DRender/LineRenderer.h>
#include <Vector2.h>

namespace Agmd
{
	LineRenderer::LineRenderer( BaseSpline* spline ) : m_spline(spline)
	{
		spline->setUpdateListener(this);
		TDeclarationElement elements[] =
		{
			{0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT2}
		};
		Driver& driver = Driver::Get();
		m_declaration = driver.CreateVertexDeclaration(elements);
		std::vector<vec2> &points = spline->getComputedPoints();
		std::vector<vec2> &points_control = spline->getControlPoints();
		if(points.size())
			m_vertex = driver.CreateVertexBuffer(points.size(),0,&points[0]);
		if(points_control.size())
			m_vertex_control = driver.CreateVertexBuffer(points_control.size(),0,&points_control[0]);
		m_program.LoadFromFile("Shader/line_renderer.glsl");
		m_program_control.LoadFromFile("Shader/control_point.glsl");
	}

	void LineRenderer::draw( const mat4& projection ) const
	{
		if(m_vertex.GetCount() < 2)
			return;
		Driver& driver = Driver::Get();
		driver.SetCurrentProgram(m_program.GetShaderProgram());
		m_program.SetParameter("u_projection",projection);
		driver.SetDeclaration(m_declaration);
		driver.SetVertexBuffer(0,m_vertex);
		driver.DrawPrimitives(PT_LINESTRIP,0,m_vertex.GetCount());
	}

	void LineRenderer::drawPoints( const mat4& projection ) const
	{
		if(!m_vertex.GetCount())
			return;
		Driver& driver = Driver::Get();
		driver.SetCurrentProgram(m_program_control.GetShaderProgram());
		m_program.SetParameter("u_projection",projection);
		driver.SetDeclaration(m_declaration);
		driver.SetVertexBuffer(0,m_vertex_control);
		driver.DrawPrimitives(PT_POINTLIST,0,m_vertex_control.GetCount());
	}



	void LineRenderer::onUpdate( std::vector<vec2>& points )
	{
		Driver& driver = Driver::Get();
		m_vertex.Release();
		m_vertex = driver.CreateVertexBuffer(points.size(),0,&points[0]);
		std::vector<vec2>& ct_points = m_spline->getControlPoints();
		if(ct_points.size() <= m_vertex_control.GetCount())
		{
			vec2* p= m_vertex_control.Lock();
			for( std::vector<vec2>::iterator itr =ct_points.begin(); itr != ct_points.end(); itr++)
			{
				*(p) = *itr; 
				++p;
			}
			m_vertex_control.Unlock();
		}else
		{
			m_vertex_control.Release();
			m_vertex_control = driver.CreateVertexBuffer(ct_points.size(),0,&ct_points[0]);
		}
	}

	

}

