/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/GUI/GUIMgr.h>
#include <Core/GUI/AWidget.h>
#include <Core/Enums.h>
#include <Core/Renderer.h>

SINGLETON_IMPL(Agmd::GUIMgr);


namespace Agmd
{
    GUIMgr::GUIMgr()
    {}

    GUIMgr::~GUIMgr()
    {}

    void GUIMgr::SetSelected(a_uint32 i)
    {
        AWidget* swapvalue = m_vwWidget[i];
        m_vwWidget.erase(m_vwWidget.begin()+i);
        m_vwWidget.push_back(swapvalue);
    }

    void GUIMgr::Update(a_uint64 t_diff)
    {
        /**/

        if(m_veEvents.empty() || m_vwWidget.empty())
            return;
        
        for(a_uint32 i = 0; i < m_veEvents.size(); i++)
        {
            HandleEvent(m_veEvents[i]);
        }

        m_veEvents.clear();
    }

    void GUIMgr::DrawGUI() const
    {
        if(m_vwWidget.empty())
            return;

        Driver::Get().Enable(RENDER_ZTEST,false);

        for(a_uint32 i = 0; i < m_vwWidget.size(); i++)
            m_vwWidget[i]->Draw();
    }

    void GUIMgr::HandleEvent(EventEntry& _event)
    {

        switch(_event.eventType)
        {
            case EV_ON_MOUSE_BUTTON:
                for(a_uint32 i = 0; i < m_vwWidget.size() ; i++)
                {
                    if(!m_vwWidget[m_vwWidget.size()-i-1]->OnClick(_event.mousePosition,_event.mouseState))
                        continue;
                    SetSelected(i);
                    break;
                }
                return;
            case EV_ON_KEY:
                return;
            case EV_ON_MOUVE_MOVE:
                for(a_int32 i = m_vwWidget.size()-1; i >= 0 ; i--)
                {
                    if(!m_vwWidget[i]->OnMouseMove(_event.mouse_diff, _event.mouseState))
                        continue;

                    break;
                }
                return;
            default:
                return;
        }
    }

    void GUIMgr::AddEvent(EventEntry& _event)
    {
        m_veEvents.push_back(_event);
    }

    void GUIMgr::AddWidget(AWidget* widget)
    {
        m_vwWidget.push_back(widget);
    }
}