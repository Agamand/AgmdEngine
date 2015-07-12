///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#ifdef USE_EDITOR
#include <Editor/EditorFrame.h>
#include <Core/AgmdApplication.h>
#include <Core/Tools/ColorPicking.h>
#include <Core/AgmdApplication.h>
#include <Editor/SceneTree.h>
#include <Core/Model/IcosahedronModel.h>
#include <Core/Driver.h>
#include <Core/Model/SceneMgr.h>
#include <Core/MediaManager.h>
#include <Loaders/FBXLoader.h>
#include "wx/wxprec.h"
///////////////////////////////////////////////////////////////////////////

EditorFrame::EditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ), m_action(false)
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    m_mgr.SetManagedWindow(this);
    m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

    m_mainMenu = new wxMenuBar( 0 );
    FileMenu = new wxMenu();
    wxMenuItem* OpenItem,
        *QuitItem;
    OpenItem = new wxMenuItem( FileMenu, wxID_ANY, wxString( wxT("Open model") ) , wxEmptyString, wxITEM_NORMAL );
    QuitItem = new wxMenuItem( FileMenu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
    FileMenu->Append(OpenItem);
    FileMenu->Append( QuitItem );
    this->Connect(OpenItem->GetId(),wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(EditorFrame::OnMenuFileOpen));

    m_mainMenu->Append( FileMenu, wxT("File") ); 

    this->SetMenuBar( m_mainMenu );

    m_viewPanel = new wxPanel( this, wxID_VIEWPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    m_viewPanel->SetExtraStyle( wxWS_EX_PROCESS_IDLE );

    m_mgr.AddPane( m_viewPanel, wxAuiPaneInfo() .Name( wxT("3D view") ).Left() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).CentrePane() );

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer( wxVERTICAL );


    m_viewPanel->SetSizer( bSizer3 );
    m_viewPanel->Layout();
    bSizer3->Fit( m_viewPanel );
    m_notebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), 0 );
    m_mgr.AddPane( m_notebook, wxAuiPaneInfo() .Right() .PinButton( true ).Gripper().Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ) );

    m_scrolledWindow = new wxScrolledWindow( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
    m_scrolledWindow->SetScrollRate( 5, 5 );
    wxBoxSizer* bSizer2;
    bSizer2 = new wxBoxSizer( wxVERTICAL );

    m_objectProperties = new ObjectPropertyGrid(m_scrolledWindow, wxID_PROPERTY, wxDefaultPosition, wxSize( -1,-1 ), wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
    bSizer2->Add( m_objectProperties, 1, wxALL|wxEXPAND, 5 );


    m_scrolledWindow->SetSizer( bSizer2 );
    m_scrolledWindow->Layout();
    bSizer2->Fit( m_scrolledWindow );
    m_notebook->AddPage( m_scrolledWindow, wxT("Properties"), false );

    m_sceneTree = new SceneTree( this,this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
    m_mgr.AddPane( m_sceneTree, wxAuiPaneInfo() .Left() .PinButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,-1 ) ).MinSize( wxSize( 150,-1 ) ).Layer( 10 ) );

    m_auiToolBar1 = new ToolBar( this, wxID_ANY, wxDefaultPosition, wxSize( -1,20 ), wxAUI_TB_HORZ_LAYOUT ); 

    m_mgr.AddPane( m_auiToolBar1, wxAuiPaneInfo().Top().PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 42,49 ) ).DockFixed( false ).Row( 0 ).Layer( 11 ) );

    //m_auiToolBar1->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( EditorFrame::onClick ), NULL, this );

    this->Connect( m_auiToolBar1->m_createBox->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_createSphere->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_createIcosahedron->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_translate_x->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_translate_y->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_translate_z->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );


    this->Connect( m_auiToolBar1->m_rotate_x->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_rotate_y->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    this->Connect( m_auiToolBar1->m_rotate_z->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EditorFrame::onClick ) );

    m_mgr.Update();
    this->Centre( wxBOTH );

    // Connect Events
    this->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorFrame::OnIdle ) );
    m_objectProperties->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( EditorFrame::OnPropertyChanged ), NULL, this );
    Agmd::AgmdApplication::getApplication()->CreateGlCanvas(m_viewPanel);
}

// File|Open... command
void EditorFrame::OnMenuFileOpen( wxCommandEvent& WXUNUSED(event) )
{
    wxString filename = wxFileSelector(wxT("Choose Model"), wxT(""), wxT(""), wxT(""),
        // #if wxUSE_ZLIB
        //         wxT("DXF Drawing (*.o;*.dxf.gz)|*.dxf;*.dxf.gz|All files (*.*)|*.*"),
        // #else
        wxT("Model file (*.fbx)|*.FBX)|All files (*.*)|*.*"),
        /*#endif*/
        wxFD_OPEN);
    if (!filename.IsEmpty())
    {
        //         m_canvas->LoadDXF(filename);
        //         //                       
        Agmd::SceneNode* node = Agmd::FBXLoader().LoadFromFile(filename.ToStdString());
        if(!node)
            return;
         Agmd::SceneMgr* scene = Agmd::Driver::Get().GetActiveScene();
         scene->AddNode(node);
        //Agmd::MediaManager::Instance().LoadMediaFromFile<SceneNode>(filename)                                                                                                                                                        ->Refresh(false);
    }
}


EditorFrame::~EditorFrame()
{
    // Disconnect Events
    this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorFrame::OnIdle ) );
    m_objectProperties->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( EditorFrame::OnPropertyChanged ), NULL, this );

    m_mgr.UnInit();

}

void EditorFrame::__addNode(  Agmd::SceneNode* node )
{
    if(m_sceneTree)
        m_sceneTree->addSceneNode(node);
    
}

void EditorFrame::__removeNode( Agmd::SceneNode* node )
{
    if(m_sceneTree)
        m_sceneTree->removeSceneNode(node);
}


void EditorFrame::__selectNode(Agmd::SceneNode* node){

    if(m_objectProperties)
        m_objectProperties->setCurrent(node);
}

void EditorFrame::OnClick( int click, vec2 pos, bool up )
{
    if(m_action == TACTION::DRAW_ICOSAHEDRE && click == 1 && !up)
    {
        ivec2 screen = Agmd::AgmdApplication::getApplication()->getScreen()/2;
        Agmd::Camera* cam = Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D);
        Agmd::SceneNode* node = cam->getNode();
        vec3 start(pos,0);
        vec3 end(pos,1);
        if(node && cam->unProject(start) &&    cam->unProject(end))
        {
            end = normalize(end - start);
            Agmd::Icosahedron* ico =  new Agmd::Icosahedron(4);
            Transform* t = new Transform();
            t->setPosition(start+end*10.f);
            Agmd::MeshNode* node = new Agmd::MeshNode(ico,t);
    
            Agmd::SceneMgr* scene = Agmd::Driver::Get().GetActiveScene();

            scene->AddNode(node);

        }
        return;
    }

    //std::cout << "click " <<  click << " up? " << up << std::endl;
    return;
    if(click == 1)
    {
        if(!m_sceneTree->getSelectedSceneNode() || up)
        {
            Agmd::ColorPicking::PickingResult pick = Agmd::ColorPicking::Instance().pick(pos);
            if(m_sceneTree)
                m_sceneTree->setSelectedSceneNode(pick.node);
            
        }
    }
}

void EditorFrame::DoAction( vec2 pos,ivec2 posdiff )
{
    Agmd::SceneNode* node = m_sceneTree->getSelectedSceneNode();
    if(!node)
        return;
    vec3 axe_x = vec3(1,0,0);
    vec3 axe_y = vec3(0,1,0);
    vec3 axe_z = vec3(0,0,1);

    axe_x = node->getParent() ? mat3(node->getParent()->getTransform().modelMatrix())*axe_x : axe_x;
    axe_y = node->getParent() ? mat3(node->getParent()->getTransform().modelMatrix())*axe_y : axe_y;
    axe_z = node->getParent() ? mat3(node->getParent()->getTransform().modelMatrix())*axe_z : axe_z;
    float a = posdiff.x/10.f;
    switch(m_action)
    {
    case TACTION::TRANSLATE_X:

        
        node->getTransform().translate(a,0,0);
        break;
    case TACTION::TRANSLATE_Y:
        node->getTransform().translate(0,a,0);
        break;
    case TACTION::TRANSLATE_Z:
        node->getTransform().translate(0,0,a);
        break;
    case TACTION::ROTATION_X:
        node->getTransform().rotate(a,vec3(1,0,0));
        break;
    case TACTION::ROTATION_Y:
        node->getTransform().rotate(a,vec3(0,1,0));
        break;
    case TACTION::ROTATION_Z:
        node->getTransform().rotate(a,vec3(0,0,1));
        break;


    }
}


void EditorFrame::OnMove( vec2 pos,ivec2 posdiff,a_uint32 mouseState )
{
    if(m_action >= TRANSLATE_X && mouseState & Agmd::TMouseState::MOUSE_LEFT)
    {
        DoAction(pos,posdiff);
        return;
    }
        
    if(Agmd::TMouseState::MOUSE_LEFT & mouseState)
    {
        Agmd::SceneNode* selected = m_sceneTree->getSelectedSceneNode();
        ivec2 screen_2 = Agmd::AgmdApplication::getApplication()->getScreen()/2;
        if(selected)
        {
            vec2 oldPos = pos-vec2(posdiff);
            vec3 screen_start(screen_2,0), screen_ray(screen_2,1);
            vec3 start(pos,0), ray(pos,1),
                 old_start(oldPos,0), old_ray(oldPos,1);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(ray);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(old_start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(old_ray);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(screen_start);
            Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(screen_ray);
            ray -= start;
            ray = normalize(ray);
            old_ray -= old_start;
            old_ray = normalize(old_ray);
            screen_ray -= screen_start;
            screen_ray = normalize(screen_ray);
            vec3 center = selected->getTransform().getPosition();

                
            Plane p(screen_ray,center);

            
            
            vec3 res,_res;
            if(p.intersect(start,ray,res) && p.intersect(old_start,old_ray,_res))
            {
                vec3 t = _res-res;
                printf("%f %f %f\n",t.x,t.y,t.z);

                if(selected->getParent())
                {
                    t = inverse(mat3(selected->getParent()->getTransform().modelMatrix()))*t;
                }

                selected->getTransform().translate(t);

            }
            
        }
    }
}



void EditorFrame::OnKey( a_char key,bool up )
{
    
    if(key == 27 && !up)
    {
        m_action = 0;
        return;
    }
    Agmd::SceneNode* selected = m_sceneTree->getSelectedSceneNode();
    if(key == 127 && selected && selected->getParent() && up)
    {
        selected->getParent()->removeChild(selected);
        //delete selected;

    }
}
void EditorFrame::onClick( wxCommandEvent& event  )
{
    m_action = 1+event.GetId();
    
}

#endif