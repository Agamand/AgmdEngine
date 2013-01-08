#ifndef GUIMGR_H
#define GUIMGR_H

#include <Utilities\Singleton.h>
#include <Config/Export.h>
#include <Config\Fwd.h>

#include <AgmdDefines.h>
#include <Vector2.h>

#include <vector>

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

        EventEntry(EventType _event, ivec2 _mouse, ivec2 _mousediff, uint32 _mouseState, char _var) : 
        eventType(_event),
        mousePosition(_mouse),
        mouse_diff(_mousediff),
        mouseState(_mouseState),
        var(_var)
        {}

        EventType eventType;
        ivec2 mousePosition;
        ivec2 mouse_diff;
        uint32 mouseState;
        char var;
    };

    typedef std::vector<EventEntry> VectorEvent;
    typedef std::vector<AWidget*> VectorWidget;

    class AGMD_EXPORT GUIMgr : public Singleton<GUIMgr>
    {

    MAKE_SINGLETON(GUIMgr);

    public:

        void Update(uint64 t_diff);
        void DrawGUI() const;
        void SetSelected(uint32 i);
        void HandleEvent(EventEntry _event);
        void AddEvent(EventEntry _event);
        void AddWidget(AWidget* widget);

    private:
        GUIMgr();
        ~GUIMgr();
        
    protected:
        VectorWidget m_vwWidget;
        VectorEvent  m_veEvents;
    };
}

#endif //EVENTMGR_H