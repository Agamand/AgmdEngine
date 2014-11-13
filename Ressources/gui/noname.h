///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* FileMenu;
		wxPanel* m_viewPanel;
		wxNotebook* m_notebook1;
		wxScrolledWindow* planetProperties;
		wxPropertyGrid* m_propertyPlanet;
		wxPGProperty* m_propertyGridItem30;
		wxPGProperty* m_propertyPersistance;
		wxPGProperty* m_propertyOctave;
		wxPGProperty* m_propertyFrequency;
		wxPGProperty* m_propertyLacunarity;
		wxPGProperty* m_propertyOffset;
		wxPGProperty* Atmosphere;
		wxPGProperty* m_propertyEsun;
		wxPGProperty* m_propertyRed;
		wxPGProperty* m_propertyBlue;
		wxPGProperty* m_propertyGreen;
		wxPGProperty* m_propertyGg;
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("StartBirth"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1244,729 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~MainFrame();
	
};

#endif //__NONAME_H__
