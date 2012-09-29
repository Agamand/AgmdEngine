#include <Core\GUI\GUIMgr.h>
#include <Core\GUI\AWidget.h>
#include <Core\Enums.h>

SINGLETON_IMPL(Agmd::GUIMgr);


namespace Agmd
{
	GUIMgr::GUIMgr()
	{}

	GUIMgr::~GUIMgr()
	{}

	void GUIMgr::SetSelected(AWidget* widget)
	{

	}

	void GUIMgr::Update(uint64 t_diff)
	{
		/**/

		if(m_veEvents.empty() || m_vwWidget.empty())
			return;
		
		for(uint32 i = 0; i < m_veEvents.size(); i++)
		{
			HandleEvent(m_veEvents[i]);
		}

		m_veEvents.clear();
	}

	void GUIMgr::DrawGUI() const
	{
		if(m_vwWidget.empty())
			return;

		for(int32 i = m_vwWidget.size()-1; i >= 0; i--)
			m_vwWidget[i]->Draw();

	}

	void GUIMgr::HandleEvent(EventEntry _event)
	{

		switch(_event.eventType)
		{
			case EV_ON_MOUSE_BUTTON:
				for(int32 i = m_vwWidget.size()-1; i >= 0 ; i--)
				{
					if(!m_vwWidget[i]->OnClick(_event.mousePosition,_event.mouseState))
						continue;

					break;
				}
				return;
			case EV_ON_KEY:
				return;
			case EV_ON_MOUVE_MOVE:
				for(int32 i = m_vwWidget.size()-1; i >= 0 ; i--)
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

	void GUIMgr::AddEvent(EventEntry _event)
	{
		m_veEvents.push_back(_event);
	}

	void GUIMgr::AddWidget(AWidget* widget)
	{
		m_vwWidget.push_back(widget);
	}
}