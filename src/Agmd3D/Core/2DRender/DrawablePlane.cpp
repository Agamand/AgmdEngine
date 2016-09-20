#include <Core/2DRender/DrawablePlane.h>
#include <Core/Enums.h>
#include <Core/2DRender/Bezier.h>
#include <Core/2DRender/BSpline.h>
#include <Core/Tools/ColorPicking.h>
#define GRAB_DISTANCE 5.0f
#include <Core/GUI/GUIMgr.h>

namespace Agmd
{
    float clamp(float a, float min, float max)
    {
        return a > max ? max : (a < min ? min : a);
    }

    void DrawablePlane::OnClick(int click, int state, const vec2& pos, bool up)
    {
        //Camera* cam = Camera::getCurrent(CAMERA_2D);
        //mat4 proj = cam->getProjection();
        //mat4 invProj = inverse(proj);

        vec2 screenSize(Driver::Get().GetScreen());
        vec2 spos = (vec2(pos) + vec2(1)) * vec2(screenSize) / 2.0f;

        Agmd::ColorPicking::PickingResult pick = Agmd::ColorPicking::Instance().pick(spos);
        vec4 _pos(pick.hitPosition, 1);
        if (state == MOUSE_LEFT && !up && (key == MAJ))
        {
            printf("X: %f, Y: %f\n", _pos.x, _pos.y);
            vec3* point = NULL;
            BaseSpline* spline = NULL;
            int pointIndex = 0;
            for (a_uint32 i = 0, len = m_render.size(); i < len; i++)
            {
                LineRenderer** itr = &m_render[i];
                BaseSpline* spl = (*itr)->getSpline();
                int pi;
                vec3* p = spl->getNearControlPoint(_pos, pi);
                if (!p)
                    continue;
                float l = length((*p) - vec3(_pos));
                if (l > GRAB_DISTANCE)
                    continue;
                if (point)
                {
                    float l2 = length((*point) - vec3(_pos));
                    if (l2 <= l)
                        continue;
                }
                point = p;
                spline = spl;
                pointIndex = pi;
            }
            if (point && spline)
            {
                m_selectedPoint = point;
                m_selectedSpline = spline;
                m_pointIndex = pointIndex;
            }
        }

        if (m_selectedPoint && m_selectedSpline && click & MOUSE_RIGHT)
        {
            vec3* point = NULL;
            BaseSpline* spline = NULL;
            int pointIndex = 0;
            for (a_uint32 i = 0, len = m_render.size(); i < len; i++)
            {
                LineRenderer** itr = &m_render[i];
                BaseSpline* spl = (*itr)->getSpline();
                int pi = -1;
                vec3* p = getNearControlPoint(_pos, pi, m_selectedPoint);
                if (!p)
                    continue;
                float l = length((*p) - vec3(_pos));
                if (l > GRAB_DISTANCE)
                    continue;
                if (p == m_selectedPoint)
                    continue;
                if (point)
                {
                    float l2 = length((*point) - vec3(_pos));
                    if (l2 <= l)
                        continue;
                }
                point = p;
                spline = spl;
                pointIndex = pi;
            }
            if (point && spline)
            {
                *m_selectedPoint = *point;
                m_selectedSpline->updatePoint(m_pointIndex);
            }
        }

        if (state == MOUSE_LEFT && !up && (key == CTRL))
        {
            m_bufferPoint.push_back(vec3(_pos));
            if (!m_selectedSpline)
            {
                //for(int i  =0 ; i < m_slider.size(); i++)
                //m_slider[i]->setEnable(false);
                m_selectedSpline = /*new BaseSpline(m_bufferPoint);//sp =*/ new BSpline(m_bufferPoint, (int)floorf(degree));
                m_selectedPoint = m_selectedSpline->getLastPoint();
                m_render.push_back(new LineRenderer(m_selectedSpline));

                /*    if(sp->m_knot.size() > m_slider.size())
                    {
                        for(int i = m_slider.size(), j = sp->m_knot.size(); i < j; i++ )
                        {
    
    
                            ASlider* slider = new ASlider(NULL);
                            slider->setLabel(StringBuilder("t")(i).operator std::string());
                            GUIMgr::Instance().AddWidget(slider);
                            slider->SetPosition(1300,750-i*35);
                            slider->SetSize(200,20);
                            slider->setUpdateCallBack(this);
                            m_slider.push_back(slider);
                        }
    
                    }
                    for(int i =0, j = sp->m_knot.size(); i < j; i++ )
                    {
                        m_slider[i]->setEnable(true);
                        m_slider[i]->setValue(&sp->m_knot[i],-5,5);
                    }*/
            }
            else if (m_selectedPoint)
            {
                m_selectedPoint = NULL;
            }
            else
            {
                m_selectedSpline->addPoint(vec3(_pos));
                m_selectedPoint = m_selectedSpline->getLastPoint();
                BSpline* sp = static_cast<BSpline*>(m_selectedSpline);
                int id = sp->m_knot.size() - 1;
                /*if(sp->m_knot.size() > m_slider.size())
                {
                    ASlider* slider = new ASlider(NULL);
                    slider->setLabel(StringBuilder("t")(id).operator std::string());
                    GUIMgr::Instance().AddWidget(slider);
                    slider->SetPosition(1300,750-id*35);
                    slider->SetSize(200,20);
                    slider->setUpdateCallBack(this);
                    m_slider.push_back(slider);
                }
                for(int i = 0, j = sp->m_knot.size(); i < j; i++ )
                {
                    m_slider[i]->setEnable(true);
                    m_slider[i]->setValue(&sp->m_knot[i],-5,5);
                }*/
            }
        }

        if (!up)
            return;
        if (click == MOUSE_LEFT && !(key & CTRL))
        {
            m_selectedPoint = NULL;
            m_selectedSpline = NULL;
        }
        if (click & MOUSE_RIGHT)
            rightDown = true;
        else rightDown = false;
    }

    void DrawablePlane::OnKey(char key, bool up)
    {
        if (key == 52) //ctrl
        {
            this->key = !up ? this->key | CTRL : this->key & ~CTRL;
            //flush
            if (up)
            {
                m_selectedPoint = NULL;
                m_selectedSpline = NULL;
                m_bufferPoint.clear();
            }
        }
        if (key == 'L' && m_render.size() && !up)
        {
            BSpline* spline = static_cast<BSpline*>(m_render[m_render.size() - 1]->getSpline());
            spline->m_knot.clear();
            for (int i = -spline->m_degree - 1, j = spline->m_controlPoints.size(); i < j; i ++)
            {
                float knot = (i + 1) / (float)(j - spline->m_degree);
                spline->m_knot.push_back(clamp(knot, 0, 1));
            }
            spline->updatePoint();
            /*for(int i =0, j = spline->m_knot.size(); i < j; i++ )
            {
                m_slider[i]->setEnable(true);
                m_slider[i]->setValue(&spline->m_knot[i],-5,5);
            }*/
        }
        if (key == 'U' && !up && m_render.size())
            m_render[m_render.size() - 1]->getSpline()->m_localUpdate = !m_render[m_render.size() - 1]->getSpline()->m_localUpdate;

        if (key == 'M' && m_render.size() && !up)
        {
            BSpline* spline = static_cast<BSpline*>(m_render[m_render.size() - 1]->getSpline());
            spline->m_knot.clear();
            for (int i = -spline->m_degree - 1, j = spline->m_controlPoints.size(); i < j; i ++)
            {
                float knot = (i + 1) / (float)(j - spline->m_degree);
                spline->m_knot.push_back(knot);//clamp(knot,0,1));
            }
            spline->updatePoint();
            /*for(int i =0, j = spline->m_knot.size(); i < j; i++ )
            {
                m_slider[i]->setEnable(true);
                m_slider[i]->setValue(&spline->m_knot[i],-5,5);
            }*/
        }
        if (key == 50) //MAJ
            this->key = !up ? this->key | MAJ : this->key & ~MAJ;
        if (key == 'C' && !up)
            clear();
        if (key == 'W' && !up)
        {
            m_selectedPoint = NULL;
            m_selectedSpline = NULL;
            m_render.pop_back();
        }
    }

    void DrawablePlane::clear()
    {
        m_selectedPoint = NULL;
        m_selectedSpline = NULL;
        m_render.clear();
        /*    for(int i  =0 ; i < m_slider.size(); i++)
                m_slider[i]->setEnable(false);*/
    }

    void DrawablePlane::OnMouseMotion(const vec2& pos, const ivec2& posDiff)
    {
        //         Camera* cam = Camera::getCurrent(CAMERA_2D);
        //         mat4 proj = cam->getProjection();
        //         mat4 invProj = inverse(proj);
        //         if(m_selectedPoint && m_selectedSpline && !rightDown)
        //         {
        //             vec4 _pos(pos.x,-pos.y,0,1);
        //             _pos = invProj*_pos;
        //             *m_selectedPoint = vec3(_pos.x,_pos.y,0);
        //             m_selectedSpline->updatePoint(m_pointIndex);
        //         }

        if (m_selectedPoint && m_selectedSpline && !rightDown)
        {
            ivec2 screen_2 = Agmd::AgmdApplication::getApplication()->getScreen() / 2;
            vec2 oldPos = pos - vec2(posDiff);
            vec3 screen_start(screen_2, 0), screen_ray(screen_2, 1);
            vec3 start(pos, 0), ray(pos, 1),
                old_start(oldPos, 0), old_ray(oldPos, 1);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(ray);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(old_start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(old_ray);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(screen_start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(screen_ray);
            ray -= start;
            ray = normalize(ray);
            old_ray -= old_start;
            old_ray = normalize(old_ray);
            screen_ray -= screen_start;
            screen_ray = normalize(screen_ray);


            Plane p(screen_ray, *m_selectedPoint);


            vec3 res, _res;
            if (p.intersect(start, ray, res) && p.intersect(old_start, old_ray, _res))
            {
                vec3 t = _res - res;

                *m_selectedPoint = (*m_selectedPoint) + t;


                m_selectedSpline->updatePoint(m_pointIndex);
            }
        }
    }

    DrawablePlane::DrawablePlane(ivec2 pixelSize, vec2 repere) : m_pixelSize(pixelSize), m_repere(repere), m_selectedPoint(NULL), m_selectedSpline(NULL), m_pointIndex(0), key(0), degree(3.0f)
    {
        Driver& driver = Driver::Get();
        m_frame = driver.CreateFrameBuffer();
        m_texture.Create(m_pixelSize, PXF_A8R8G8B8, TEXTURE_2D);
        m_frame->SetTexture(m_texture, COLOR_ATTACHMENT);
        m_projection = ortho(-m_repere.x, m_repere.x, -m_repere.y, m_repere.y);
        m_reverse_projection = inverse(m_projection);
    }

    vec2 DrawablePlane::getPositionFromScreenSpace(vec2 pos)
    {
        Camera* cam = Camera::getCurrent(CAMERA_2D);
        mat4 proj = cam->getProjection();
        mat4 invProj = inverse(proj);
        vec4 _pos = vec4(pos, 0, 1);
        _pos = invProj * _pos;
        return vec2(_pos);
    }

    void DrawablePlane::render()
    {
        //m_frame->Bind();
        //m_frame->Clear(CLEAR_COLOR);
        Driver::Get().Enable(RENDER_POINTSIZE_SHADER, true);
        for (a_uint32 i = 0, len = m_render.size(); i < len; i++)
            m_render[i]->draw();
        for (a_uint32 i = 0, len = m_render.size(); i < len; i++)
            m_render[i]->drawPoints();
        //m_frame->UnBind();
    }

    void DrawablePlane::valueUpdate(float value, float cursor)
    {
        if (m_render.size() <= 0)
            return;
        m_render[m_render.size() - 1]->getSpline()->updatePoint();
    }

    vec3* DrawablePlane::getNearControlPoint(vec4 _pos, int pi, vec3* selectedPoint)
    {
        vec3* point = NULL;
        for (a_uint32 i = 0, len = m_render.size(); i < len; i++)
        {
            LineRenderer** itr = &m_render[i];
            BaseSpline* spl = (*itr)->getSpline();
            int pi;
            vec3* p = spl->getNearControlPoint(_pos, pi, selectedPoint);
            if (!p)
                continue;
            float l = length((*p) - vec3(_pos));
            if (l > GRAB_DISTANCE)
                continue;
            if (point)
            {
                float l2 = length((*point) - vec3(_pos));
                if (l2 <= l)
                    continue;
            }
            point = p;
        }
        return point;
    }
}
