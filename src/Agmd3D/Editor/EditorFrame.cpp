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
///////////////////////////////////////////////////////////////////////////

EditorFrame::EditorFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_mainMenu = new wxMenuBar( 0 );
	FileMenu = new wxMenu();
	wxMenuItem* QuitItem;
	QuitItem = new wxMenuItem( FileMenu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	FileMenu->Append( QuitItem );

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


	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorFrame::OnIdle ) );
	m_objectProperties->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( EditorFrame::OnPropertyChanged ), NULL, this );
	Agmd::AgmdApplication::getApplication()->CreateGlCanvas(m_viewPanel);
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

	if(click == 1 && !up)
	{
		Agmd::SceneNode* pick = Agmd::ColorPicking::Instance().pick(pos);
		if(m_sceneTree)
			m_sceneTree->setSelectedSceneNode(pick);
	}
}

void EditorFrame::OnMove( vec2 pos,ivec2 posdiff,a_uint32 mouseState )
{
	if(Agmd::TMouseState::MOUSE_LEFT & mouseState)
	{
		Agmd::SceneNode* selected = m_sceneTree->getSelectedSceneNode();
		ivec2 screen_2 = Agmd::AgmdApplication::getApplication()->getScreen()/2;
		if(selected)
		{
			vec3 _start(screen_2,0), _ray(screen_2,1);
			vec3 start(pos,0), ray(pos,1);
			Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(start);
			Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(ray);
			Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(_start);
			Agmd::Camera::getCurrent(Agmd::TCamera::CAMERA_3D)->unProject(_ray);
			ray -= start;
			ray = normalize(ray);
			_ray -= _start;
			_ray = normalize(_ray);
			vec3 center = selected->getTransform().getPosition();

				
			Plane p(_ray,center);

			
			
			vec3 res;
			if(p.intersect(start,ray,res))
			{
				vec3 t = res-center;
				printf("%f %f %f\n",t.x,t.y,t.z);
				selected->getTransform().translate(t);

			}
			
		}
	}
}

void EditorFrame::OnKey( a_char key,bool up )
{

}

#endif