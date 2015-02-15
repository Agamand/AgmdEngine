#include <Editor/ToolBar.h>


ToolBar::ToolBar( wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style ) : wxAuiToolBar(parent,id,pos,size,style)
{
	buildToolBar();
}

void ToolBar::buildToolBar()
{
	m_createBox = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Cube.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createSphere = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Sphere.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_createIcosahedron = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap/*wxBitmap( wxT("Icosahedron.png"), wxBITMAP_TYPE_ANY )*/, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	this->AddSeparator(); 

	m_translate = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_ = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool6 = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	this->AddSeparator(); 

	m_tool7 = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool8 = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	m_tool9 = this->AddTool( wxID_ANY, wxT("tool"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL ); 

	this->Realize();
}

