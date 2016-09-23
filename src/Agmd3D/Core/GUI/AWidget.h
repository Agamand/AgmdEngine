/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _AWIDGET_H_
#define _AWIDGET_H_

#include <Config/Export.h>

#include <Vector2.h>
#include <CommonDefines.h>

#include <Container/Vector.h>

namespace Agmd
{
    class AWidget;
    typedef a_vector<AWidget*> WidgetVector;

    class AGMD3D_EXPORT AWidget
    {
    public:
        friend class GUIMgr;
        AWidget(AWidget* parent = NULL);
        virtual ~AWidget();

        virtual a_uint32 OnClick(ivec2& pos_mouse, a_uint32 mouseState) = 0;
        virtual a_uint32 OnMouseOver() = 0;
        virtual a_uint32 OnKey(char key) = 0;
        virtual a_uint32 OnMouseMove(ivec2& pos_diff, a_uint32 mouseState) = 0;
        virtual void OnSizeChanged() = 0;
        virtual void OnPosChanged() = 0;

        virtual void Draw() const = 0;

        const ivec2& GetAbsPostion();
        const ivec2& GetPosition();

        void SetPosition(const ivec2& pos);
        void SetPosition(a_uint32 x, a_uint32 y);

        void SetSize(const ivec2& size);
        void SetSize(a_uint32 x, a_uint32 y);

        void AddChild(AWidget* child);
        void RemoveChild(AWidget* child);

        virtual bool In(ivec2& pos);

        void setEnable(bool enable = true)
        {
            m_enable = enable;
        }

    protected:
        AWidget* m_wParent;
        ivec2 m_vPosition;
        ivec2 m_vAbsolutePosition;
        ivec2 m_vSize;
        bool m_enable;

        WidgetVector m_WidgetChild;
    };
}

#endif /* _AWIDGET_H_ */
