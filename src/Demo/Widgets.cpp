///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Widgets.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_menubar1 = new wxMenuBar( 0 );
	FileMenu = new wxMenu();
	wxMenuItem* QuitItem;
	QuitItem = new wxMenuItem( FileMenu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	FileMenu->Append( QuitItem );

	m_menubar1->Append( FileMenu, wxT("File") ); 

	this->SetMenuBar( m_menubar1 );

	m_viewPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_mgr.AddPane( m_viewPanel, wxAuiPaneInfo() .Name( wxT("3D view") ).Left() .CloseButton( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).CentrePane() );

	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	m_mgr.AddPane( m_notebook1, wxAuiPaneInfo() .Right() .PinButton( true ).Gripper().Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ) );

	planetProperties = new wxScrolledWindow( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	planetProperties->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_propertyPlanet = new wxPropertyGrid(planetProperties, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxPG_DEFAULT_STYLE|wxPG_HIDE_MARGIN|wxPG_SPLITTER_AUTO_CENTER);
	m_propertyGridItem30 = m_propertyPlanet->Append( new wxPropertyCategory( wxT("Planet"), wxT("Planet") ) ); 
	m_propertyPersistance = m_propertyPlanet->Append( new wxFloatProperty( wxT("Persistance"), wxT("Persistance") ) ); 
	m_propertyOctave = m_propertyPlanet->Append( new wxIntProperty( wxT("Octaves"), wxT("Octaves") ) ); 
	m_propertyFrequency = m_propertyPlanet->Append( new wxFloatProperty( wxT("Frequency"), wxT("Frequency") ) ); 
	m_propertyLacunarity = m_propertyPlanet->Append( new wxFloatProperty( wxT("Lacunarity"), wxT("Lacunarity") ) ); 
	m_propertyOffset = m_propertyPlanet->Append( new wxFloatProperty( wxT("Height offset"), wxT("Height offset") ) ); 
	Atmosphere = m_propertyPlanet->Append( new wxPropertyCategory( wxT("Atmosphere"), wxT("Atmosphere") ) ); 
	m_propertyEsun = m_propertyPlanet->Append( new wxFloatProperty( wxT("esun"), wxT("esun") ) ); 
	m_propertyRed = m_propertyPlanet->Append( new wxFloatProperty( wxT("red"), wxT("red") ) ); 
	m_propertyBlue = m_propertyPlanet->Append( new wxFloatProperty( wxT("blue"), wxT("blue") ) ); 
	m_propertyGreen = m_propertyPlanet->Append( new wxFloatProperty( wxT("green"), wxT("green") ) ); 
	m_propertyGg = m_propertyPlanet->Append( new wxFloatProperty( wxT("gg"), wxT("gg") ) ); 
	bSizer2->Add( m_propertyPlanet, 1, wxALL|wxEXPAND, 5 );


	planetProperties->SetSizer( bSizer2 );
	planetProperties->Layout();
	bSizer2->Fit( planetProperties );
	m_notebook1->AddPage( planetProperties, wxT("Properties"), false );


	m_mgr.Update();
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
	m_mgr.UnInit();

}
