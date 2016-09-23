#ifndef _LINERENDERER_H_
#define _LINERENDERER_H_

#include <Core/Model/AModel.h>
#include <Core/2DRender/BaseSpline.h>
#include <core/Shader/ShaderProgram.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Driver.h>
#include <Config/Export.h>
#include <Container/Vector.h>


namespace Agmd
{
    class AGMD3D_EXPORT LineRenderer : public AModel, public BaseSpline::UpdateListener
    {
    public:
        LineRenderer(BaseSpline* spline);
        virtual void Draw(const Transform* transform) const;
        void draw() const;
        void drawLine() const;
        void drawPoints() const;
        void onUpdate(a_vector<vec3>& points);
        BaseSpline* getSpline() { return m_spline; };


    private:
        Color m_color;
        BaseSpline* m_spline;
        Buffer<vec3> m_vertex; // line
        Buffer<vec3> m_vertexControl; // point
        int m_vertexCount;
        int m_vertexControlCount;
        DeclarationPtr m_declaration;
        ShaderProgram m_program;
        ShaderProgram m_program_control;
    };
}
#endif /* _LINERENDERER_H_ */
