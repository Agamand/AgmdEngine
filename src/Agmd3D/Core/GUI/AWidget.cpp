/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\GUI\AWidget.h>

namespace Agmd
{
    AWidget::AWidget(AWidget* parent) :
        m_wParent(parent)
    {
        if (parent)
            parent->AddChild(parent);
    }

    AWidget::~AWidget()
    {
    }


    const ivec2& AWidget::GetAbsPostion()
    {
        return m_vAbsolutePosition;
    }

    const ivec2& AWidget::GetPosition()
    {
        return m_vPosition;
    }

    void AWidget::SetPosition(const ivec2& pos)
    {
        m_vPosition = pos;
        if (m_wParent)
            m_vAbsolutePosition = m_wParent->m_vAbsolutePosition + pos;
        else m_vAbsolutePosition = pos;
        OnPosChanged();
    }

    void AWidget::SetPosition(a_uint32 x, a_uint32 y)
    {
        SetPosition(ivec2(x, y));
    }

    void AWidget::SetSize(const ivec2& size)
    {
        m_vSize = size;
        if (m_vSize.x < 0)
            m_vSize.x = 0;

        if (m_vSize.y < 0)
            m_vSize.y = 0;

        OnSizeChanged();
    }

    void AWidget::SetSize(a_uint32 x, a_uint32 y)
    {
        SetSize(ivec2(x, y));
    }

    void AWidget::AddChild(AWidget* child)
    {
        if (child != NULL)
            m_WidgetChild.push_back(child);
    }

    void AWidget::RemoveChild(AWidget* child)
    {
        if (child == NULL)
            return;

        for (a_uint32 i = 0; i < m_WidgetChild.size(); i++)
        {
            if (m_WidgetChild[i] = child)
            {
                m_WidgetChild.erase(m_WidgetChild.begin() + i);
                child->m_wParent = NULL;
                child->m_vPosition = child->m_vAbsolutePosition;
                break;
            }
        }
    }

    bool AWidget::In(ivec2& pos)
    {
        if (pos.x < m_vAbsolutePosition.x || pos.y < m_vAbsolutePosition.y || pos.x > (m_vAbsolutePosition.x + m_vSize.x) || pos.y > (m_vAbsolutePosition.y + m_vSize.y))
            return false;

        return true;
    }
}
