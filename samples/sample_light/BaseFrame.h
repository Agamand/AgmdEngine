///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __BASEFRAME_H__
#define __BASEFRAME_H__

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
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class BaseFrame
///////////////////////////////////////////////////////////////////////////////
class BaseFrame : public wxFrame
{
private:

protected:
    enum
    {
        wxID_VIEWPANEL = 1000,
        wxID_PROPERTY
    };

    wxMenuBar* m_menubar1;
    wxMenu* FileMenu;
    wxNotebook* m_notebook1;
    wxScrolledWindow* planetProperties;
    wxPropertyGrid* m_propertyPlanet;
    wxPGProperty* Lighting;
    wxPGProperty* position_x;
    wxPGProperty* m_propertyGridItem17;
    wxPGProperty* Shadow;
    wxPGProperty* m_offset;
    wxPGProperty* m_bias;
    wxPanel* m_panel3;

    // Virtual event handlers, overide them in your derived class
    virtual void OnIdle(wxIdleEvent& event) { event.Skip(); }
    virtual void OnPropertyChanged(wxPropertyGridEvent& event) { event.Skip(); }


public:
    wxPanel* m_viewPanel;

    BaseFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("StartBirth"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1139, 729), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
    wxAuiManager m_mgr;

    ~BaseFrame();
};

#endif //__BASEFRAME_H__
