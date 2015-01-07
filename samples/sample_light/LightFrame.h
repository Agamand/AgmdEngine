

#ifndef __PLANETFRAME_H__
#define __PLANETFRAME_H__

#include "BaseFrame.h"
#include <Agmd3D/Core/ShadowMapRenderer.h>
#include <Core/Camera/Camera.h>
using namespace Agmd;
class LightFrame : public BaseFrame
{
public:
	LightFrame(wxWindow* parent) : BaseFrame(parent), m_model(NULL)
	{
	}


	void setModel(ShadowMapRenderer* model){ 
		m_model = model;
		if(!m_model)
			return;
		wxPropertyGrid* grid = (wxPropertyGrid*)this->FindWindowById(wxID_PROPERTY);

	}
	virtual void OnPropertyChanged( wxPropertyGridEvent& event )
	{
		if(!m_model)
			return;
		wxPGProperty* property = event.GetProperty();

		wxAny value = property->GetValue();
		if ( value.IsNull() )
			return;
		// Handle changes in values, as needed
		if(property==m_bias)
		{
			m_model->SetBias(value.As<float>());
		}else if(property == m_offset)
		{
			m_model->SetOffset(value.As<float>());
		}

		event.Skip();
	}


private:
	ShadowMapRenderer* m_model;
	Agmd::Camera* m_camera;
};


#endif //__PLANETFRAME_H__