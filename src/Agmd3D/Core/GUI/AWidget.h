/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef AWIDGET_H
#define AWIDGET_H

#include <Config/Export.h>

#include <Vector2.h>
#include <AgmdDefines.h>

#include <vector>

namespace Agmd
{
    class AWidget;
    typedef std::vector<AWidget*> WidgetVector;

    class AGMD3D_EXPORT AWidget
    {
    public:
        AWidget(AWidget* parent = NULL);
        virtual ~AWidget();

        virtual uint32 OnClick(ivec2 pos_mouse, uint32 mouseState) = 0;
        virtual uint32 OnMouseOver() = 0;
        virtual uint32 OnKey(char key) = 0;
        virtual uint32 OnMouseMove(ivec2 pos_diff, uint32 mouseState) = 0;
        virtual void OnSizeChanged() = 0;
        virtual void OnPosChanged() = 0;

        virtual void Draw() const = 0;

        ivec2 GetAbsPostion();
        ivec2 GetPosition();

        void SetPosition(ivec2 pos);
        void SetPosition(uint32 x, uint32 y);

        void SetSize(ivec2 size);
        void SetSize(uint32 x, uint32 y);

        void AddChild(AWidget* child);
        void RemoveChild(AWidget* child);

        virtual bool In(ivec2 pos);

    protected:
        AWidget* m_wParent;
        ivec2 m_vPosition;
        ivec2 m_vAbsolutePosition;
        ivec2 m_vSize;

        WidgetVector m_WidgetChild;

    };
}

#endif //AWIDGET_H