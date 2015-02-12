///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EDITORFRAME_H__
#define __EDITORFRAME_H__
#ifdef USE_EDITOR
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
#include <wx/treectrl.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class EditorFrame
///////////////////////////////////////////////////////////////////////////////
class EditorFrame : public wxFrame 
{
private:

protected:
	enum
	{
		wxID_VIEWPANEL = 1000,
		wxID_PROPERTY
	};

	wxMenuBar* m_mainMenu;
	wxMenu* FileMenu;
	wxNotebook* m_notebook;
	wxScrolledWindow* objectProperties;
	wxPropertyGrid* m_propertyPlanet;
	wxTreeCtrl* m_sceneTree;
	wxAuiToolBar* m_auiToolBar1;
	wxAuiToolBarItem* m_createBox; 
	wxAuiToolBarItem* m_createSphere; 
	wxAuiToolBarItem* m_createIcosahedron; 
	wxAuiToolBarItem* m_translate; 
	wxAuiToolBarItem* m_; 
	wxAuiToolBarItem* m_tool6; 
	wxAuiToolBarItem* m_tool7; 
	wxAuiToolBarItem* m_tool8; 
	wxAuiToolBarItem* m_tool9; 

	// Virtual event handlers, overide them in your derived class
	virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
	virtual void OnPropertyChanged( wxPropertyGridEvent& event ) { event.Skip(); }


public:
	wxPanel* m_viewPanel;

	EditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1130,729 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	wxAuiManager m_mgr;

	~EditorFrame();

};
#endif
#endif //__EDITORFRAME_H__
