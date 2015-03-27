#include <Core/2DRender/LineRenderer.h>
#include <Vector2.h>

namespace Agmd
{
    LineRenderer::LineRenderer( BaseSpline* spline ) : m_spline(spline),m_vertexCount(0),m_vertexControlCount(0)
    {
        spline->setUpdateListener(this);
        TDeclarationElement elements[] =
        {
            {0, ELT_USAGE_POSITION,        ELT_TYPE_FLOAT2}
        };
        Driver& driver = Driver::Get();
        m_declaration = driver.CreateVertexDeclaration(elements);
        a_vector<vec2> &points = spline->getComputedPoints();
        a_vector<vec2> &points_control = spline->getControlPoints();
        if(points.size())
        {
            m_vertex = driver.CreateVertexBuffer(points.size(),BUF_STREAM,&points[0]);
            m_vertexCount = points.size();
        }
        if(points_control.size())
        {
            m_vertexControl = driver.CreateVertexBuffer(points_control.size(),BUF_STREAM,&points_control[0]);
            m_vertexControlCount = points_control.size();
        }
        m_program.LoadFromFile("Shader/line_renderer.glsl");
        m_program_control.LoadFromFile("Shader/control_point.glsl");
    }

    void LineRenderer::draw( const mat4& projection ) const
    {
        //m_spline->updatePoint();
        if(m_vertex.GetCount() < 2)
            return;
        Driver& driver = Driver::Get();
        driver.SetCurrentProgram(m_program.GetShaderProgram());
        m_program.SetParameter("u_projection",projection);
        driver.SetDeclaration(m_declaration);
        driver.SetVertexBuffer(0,m_vertex);
        driver.DrawPrimitives(PT_LINESTRIP,0,m_vertexCount);
    }

    void LineRenderer::drawPoints( const mat4& projection ) const
    {
        if(!m_vertex.GetCount())
            return;
        Driver& driver = Driver::Get();
        driver.SetCurrentProgram(m_program_control.GetShaderProgram());
        m_program.SetParameter("u_projection",projection);
        driver.SetDeclaration(m_declaration);
        driver.SetVertexBuffer(0,m_vertexControl);
        driver.DrawPrimitives(PT_POINTLIST,0,m_vertexControlCount);
    }



    void LineRenderer::onUpdate( a_vector<vec2>& points )
    {
        Driver& driver = Driver::Get();
        
        a_vector<vec2>& ct_points = m_spline->getControlPoints();
        if(ct_points.size() <= m_vertexControl.GetCount())
        {
            vec2* p= m_vertexControl.Lock();
            for(a_uint32 i = 0, len = ct_points.size(); i < len;i++)
            {
                *(p) = ct_points[i]; 
                ++p;
            }

            m_vertexControl.Unlock();
            m_vertexControlCount = ct_points.size();
        }else
        {
            m_vertexControl.Release();
            m_vertexControl = driver.CreateVertexBuffer(ct_points.size(),BUF_STREAM,&ct_points[0]);
            
        }

        if(points.size() <= m_vertex.GetCount())
        {
            vec2* p= m_vertex.Lock();
            for(a_uint32 i = 0, len = points.size(); i < len;i++)
            {
                *(p) = points[i]; 
                ++p;
            }
            m_vertex.Unlock();
            m_vertexCount = points.size();
        }else
        {
            m_vertex.Release();
            m_vertex = driver.CreateVertexBuffer(points.size(),BUF_STREAM,&points[0]);

        }
    }

    

}

