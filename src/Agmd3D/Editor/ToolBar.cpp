#include <Editor/ToolBar.h>

#ifdef USE_EDITOR
ToolBar::ToolBar( wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style ) : wxAuiToolBar(parent,id,pos,size,style)
{
	buildToolBar();
}

void ToolBar::buildToolBar()
{
	m_createBox = this->AddTool( wxID_ANY+1, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Cube.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createSphere = this->AddTool( wxID_ANY+2, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Sphere.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createIcosahedron = this->AddTool( wxID_ANY+3, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Icosahedron.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	this->AddSeparator(); 

	m_translate_x = this->AddTool( wxID_ANY+4, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_translate_y = this->AddTool( wxID_ANY+5, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_translate_z = this->AddTool( wxID_ANY+6, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	this->AddSeparator(); 

	m_rotate_x = this->AddTool( wxID_ANY+7, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_rotate_y = this->AddTool( wxID_ANY+8, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_rotate_z = this->AddTool( wxID_ANY+9, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 
	
	this->Realize();
}
#endif
