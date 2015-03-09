
#ifndef _TOOLBAR_H_
#define _TOOLBAR_H_

#ifdef USE_EDITOR
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
class ToolBar : public wxAuiToolBar
{
public:
	ToolBar(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style);
	
private:
	friend class EditorFrame;
	void buildToolBar();
	wxAuiToolBarItem* m_createBox; 
	wxAuiToolBarItem* m_createSphere; 
	wxAuiToolBarItem* m_createIcosahedron; 
	wxAuiToolBarItem* m_translate_x; 
	wxAuiToolBarItem* m_translate_y; 
	wxAuiToolBarItem* m_translate_z; 
	wxAuiToolBarItem* m_rotate_x; 
	wxAuiToolBarItem* m_rotate_y; 
	wxAuiToolBarItem* m_rotate_z; 
};
#endif
#endif