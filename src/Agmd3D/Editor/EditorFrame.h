#ifndef _EDITORFRAME_H_
#define _EDITORFRAME_H_
#ifdef USE_EDITOR
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include "wx/defs.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include "wx/wfstream.h"
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/treectrl.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/frame.h>
#include "wx/app.h"
#include "wx/menu.h"
#include "wx/dcclient.h"
#include "wx/wfstream.h"
#include <Editor/Toolbar.h>
#include <Editor/ObjectPropertyGrid.h>

class Agmd::SceneNode;
class SceneTree;


class EditorFrame : public wxFrame 
{
private:

protected:
    enum
    {
        wxID_VIEWPANEL = 1000,
        wxID_PROPERTY
    };
    enum TACTION
    {
        DRAW_CUBE = 1,
        DRAW_SPHERE,
        DRAW_ICOSAHEDRE,
        TRANSLATE_X,
        TRANSLATE_Y,
        TRANSLATE_Z,
        ROTATION_X,
        ROTATION_Y,
        ROTATION_Z
    };

    wxMenuBar* m_mainMenu;
    wxMenu* FileMenu;
    wxNotebook* m_notebook;
    wxScrolledWindow* m_scrolledWindow;

    ObjectPropertyGrid* m_objectProperties;
    SceneTree* m_sceneTree;
    ToolBar* m_auiToolBar1;

// Virtual event handlers, overide them in your derived class
    virtual void OnIdle( wxIdleEvent& event ) { event.Skip(); }
    virtual void OnPropertyChanged( wxPropertyGridEvent& event ) { event.Skip(); }
    virtual void onClick( wxCommandEvent& event  );
    void DoAction(vec2 pos,ivec2 posdiff);
    virtual void OnMenuFileOpen( wxCommandEvent& WXUNUSED(event) );
public:
    void OnClick(int click, vec2 pos, bool up);
    void OnMove(vec2 pos,ivec2 posdiff,a_uint32 mouseState);
    void OnKey(a_char key,bool up);
    wxPanel* m_viewPanel;

    EditorFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1130,729 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    
    wxAuiManager m_mgr;
    a_uint32 m_action;
    ~EditorFrame();
    void __addNode( Agmd::SceneNode* node );
    void __removeNode(  Agmd::SceneNode* node );
    void __selectNode(Agmd::SceneNode* node);


};
#endif
#endif //_EDITORFRAME_H_
