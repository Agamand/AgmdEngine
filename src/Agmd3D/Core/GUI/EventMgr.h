#ifndef EVENTMGR_H
#define EVENTMGR_H

#include <Utilities\Singleton.h>

#include <AgmdDefines.h>
#include <Vector2.h>

#include <vector>

namespace Agmd
{
/*    enum EventType
    {
        EV_NOTHING,
        EV_ON_CLICK,
        EV_ON_KEY,
    };

    struct EventEntry
    {    
        EventEntry() : 
        eventType(EV_NOTHING),
        mousePosition(0),
        var(0)
        {}

        EventEntry(EventType _event, ivec2 _mouse, char _var) : 
        eventType(_event),
        mousePosition(_mouse),
        var(_var)
        {}

        EventType eventType;
        ivec2 mousePosition;
        char var;
    };

    typedef std::vector<EventEntry> VectorEvent;

    class EventMgr : public Singleton<EventMgr>
    {
        MAKE_SINGLETON(EventMgr);
    public:

        void Update(uint64 t_diff);

    private:
        EventMgr();
        ~EventMgr();

        VectorEvent m_veEvents;
    };*/
}

#endif //EVENTMGR_H