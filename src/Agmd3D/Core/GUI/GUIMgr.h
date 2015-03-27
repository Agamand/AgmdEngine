/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GUIMGR_H_
#define _GUIMGR_H_

#include <Utilities\Singleton.h>
#include <Config/Export.h>
#include <Config\Fwd.h>

#include <CommonDefines.h>
#include <Vector2.h>

#include <Container/Vector.h>

namespace Agmd
{
    enum EventType
    {
        EV_NOTHING,
        EV_ON_MOUSE_BUTTON,
        EV_ON_KEY,
        EV_ON_MOUVE_MOVE,
    };

    struct EventEntry
    {    
        EventEntry() : 
        eventType(EV_NOTHING),
        mousePosition(0),
        var(0)
        {}

        EventEntry(EventType _event, ivec2& _mouse, ivec2& _mousediff, a_uint32 _mouseState, char _var) : 
        eventType(_event),
        mousePosition(_mouse),
        mouse_diff(_mousediff),
        mouseState(_mouseState),
        var(_var)
        {}

        EventType eventType;
        ivec2 mousePosition;
        ivec2 mouse_diff;
        a_uint32 mouseState;
        char var;
    };

    typedef a_vector<EventEntry> VectorEvent;
    typedef a_vector<AWidget*> VectorWidget;

    class AGMD3D_EXPORT GUIMgr : public Singleton<GUIMgr>
    {

    MAKE_SINGLETON(GUIMgr); 
    public:
        

        void Update(a_uint64 t_diff);
        void DrawGUI() const;
        void SetSelected(a_uint32 i);
        int HandleEvent(EventEntry& _event);
        void AddEvent(EventEntry& _event);
        void AddWidget(AWidget* widget);
        void RemoveWidget(AWidget* widget);
        void Enable(bool enable = true)
        {
            m_renderGUI = enable;
        }
        bool isEnable() const
        {
            return m_renderGUI;
        }

    private:
        GUIMgr();
        ~GUIMgr();
        

    protected:
        VectorWidget    m_vwWidget;
        VectorEvent        m_veEvents;
        bool            m_renderGUI;
    };
}

#endif /* _GUIMGR_H_ */