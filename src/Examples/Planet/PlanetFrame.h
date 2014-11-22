

#ifndef __PLANETFRAME_H__
#define __PLANETFRAME_H__

#include "BaseFrame.h"
#include "Planet/PlanetModel.h"
#include <Core/Camera/Camera.h>
class PlanetModel;
class PlanetFrame : public BaseFrame
{
public:
	PlanetFrame(wxWindow* parent) : BaseFrame(parent), m_model(NULL)
	{
	}


	void setPlanetModel(PlanetModel* model){ 
		m_model = model;
		if(!m_model)
			return;
		wxPropertyGrid* grid = (wxPropertyGrid*)this->FindWindowById(wxID_PROPERTY);
		m_propertyPersistance->SetValue(wxVariant(m_model->m_persistance));
		m_propertyOctave->SetValue(wxVariant((int)m_model->m_octave));
		m_propertyFrequency->SetValue(wxVariant(m_model->m_frequency));
		m_propertyLacunarity->SetValue(wxVariant(m_model->m_lacunarity));
		m_propertyOffset->SetValue(wxVariant(m_model->m_offset));
		m_propertyEsun->SetValue(wxVariant(m_model->eSun));
		m_propertyRed->SetValue(wxVariant(m_model->rgb.r));
		m_propertyBlue->SetValue(wxVariant(m_model->rgb.b));
		m_propertyGreen->SetValue(wxVariant(m_model->rgb.g));
		m_propertyGg->SetValue(wxVariant(m_model->g));
		m_propertyAmplitude->SetValue(wxVariant(m_model->m_amplitude));
	}
	void setCamera(Agmd::Camera* cam){
		m_camera = cam;
		
		if(!m_camera)
			return;
		m_propertyCameraSpeed->SetValue(wxVariant(*m_camera->GetSpeedPtr()));
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
		if(property==m_propertyPersistance)
		{
			m_model->m_persistance = value.As<float>();
		}else if(property == m_propertyOctave)
		{
			m_model->m_octave = value.As<int>();

		}else if(property == m_propertyFrequency)
		{
			m_model->m_frequency = value.As<float>();

		}else if(property == m_propertyLacunarity)
		{
			m_model->m_lacunarity = value.As<float>();

		}else if(property == m_propertyOffset)
		{
			m_model->m_offset = value.As<float>();

		}else if(property == m_propertyEsun)
		{
			m_model->eSun = value.As<float>();

		}else if(property == m_propertyRed)
		{
			m_model->rgb.r = value.As<float>();

		}else if(property == m_propertyBlue)
		{
			m_model->rgb.b = value.As<float>();

		}else if(property == m_propertyGreen)
		{
			m_model->rgb.g = value.As<float>();

		}else if(property == m_propertyGg)
		{
			m_model->g = value.As<float>();

		}else if(property == m_propertyCameraSpeed)
		{
			*m_camera->GetSpeedPtr() = value.As<float>();
		}else if(property == m_propertyAmplitude)
		{
			m_model->m_amplitude = value.As<float>();
		}
		event.Skip();
	}
	

private:
	PlanetModel* m_model;
	Agmd::Camera* m_camera;
};


#endif //__PLANETFRAME_H__