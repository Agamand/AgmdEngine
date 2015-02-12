///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#ifdef USE_EDITOR
#include "EditorFrame.h"

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

	objectProperties = new wxScrolledWindow( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	objectProperties->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_propertyPlanet = new wxPropertyGrid(objectProperties, wxID_PROPERTY, wxDefaultPosition, wxSize( -1,-1 ), wxPG_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER);
	bSizer2->Add( m_propertyPlanet, 1, wxALL|wxEXPAND, 5 );


	objectProperties->SetSizer( bSizer2 );
	objectProperties->Layout();
	bSizer2->Fit( objectProperties );
	m_notebook->AddPage( objectProperties, wxT("Properties"), false );

	m_sceneTree = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	m_mgr.AddPane( m_sceneTree, wxAuiPaneInfo() .Left() .PinButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( 200,-1 ) ).MinSize( wxSize( 150,-1 ) ).Layer( 10 ) );

	m_auiToolBar1 = new wxAuiToolBar( this, wxID_ANY, wxDefaultPosition, wxSize( -1,20 ), wxAUI_TB_HORZ_LAYOUT ); 
	m_createBox = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("Cube.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createSphere = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("Sphere.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createIcosahedron = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("Icosahedron.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_auiToolBar1->AddSeparator(); 

	m_translate = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_ = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool6 = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_auiToolBar1->AddSeparator(); 

	m_tool7 = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool8 = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool9 = m_auiToolBar1->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_auiToolBar1->Realize();
	m_mgr.AddPane( m_auiToolBar1, wxAuiPaneInfo().Top().PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 42,49 ) ).DockFixed( false ).Row( 0 ).Layer( 11 ) );


	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_IDLE, wxIdleEventHandler( EditorFrame::OnIdle ) );
	m_propertyPlanet->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( EditorFrame::OnPropertyChanged ), NULL, this );
}

EditorFrame::~EditorFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( EditorFrame::OnIdle ) );
	m_propertyPlanet->Disconnect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( EditorFrame::OnPropertyChanged ), NULL, this );

	m_mgr.UnInit();

}
#endif