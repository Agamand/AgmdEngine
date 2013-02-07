#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <GameEngineConfig/ExportGameEngine.h>

namespace Agmd
{
    template <class T> class GAMEENGINE_EXPORT Component
	{
	public: 
		Component();
		~Component();
    private:
        T* m_component;
	};
}

#endif /* _COMPONENT_H_ */
