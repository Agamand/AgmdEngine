
#ifndef _OBJECTPROPERTYGRID_H_
#define _OBJECTPROPERTYGRID_H_

#ifdef USE_EDITOR
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneNode/RootNode.h>
#include <Core/SceneNode/DisplayNode.h>
#include <Core/SceneNode/CameraNode.h>
#include <Core/SceneNode/MeshNode.h>

class ObjectPropertyGrid : public wxPropertyGrid
{
public:
    ObjectPropertyGrid(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style): wxPropertyGrid(parent,id,pos,size,style)
    {
        Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( ObjectPropertyGrid::OnPropertyChanged ), NULL, this );

    }
    virtual void OnPropertyChanged( wxPropertyGridEvent& event );
    void setCurrent(Agmd::SceneNode* node);
    Agmd::SceneNode* getCurrent() const{
        return m_current;
    }
private:

    void buildProperty(Agmd::SceneNode* node);
    void buildProperty(Agmd::RootNode* node);
    void buildProperty(Agmd::DisplayNode* node);
    void buildProperty(Agmd::CameraNode* node);
    void buildProperty(Agmd::MeshNode* node);

    Agmd::SceneNode* m_current;


};
#endif
#endif