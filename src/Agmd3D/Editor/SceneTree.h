
#ifndef _SCENETREE_H_
#define _SCENETREE_H_
#ifdef USE_EDITOR


#include <Core/SceneNode/RootNode.h>
#include <Editor/EditorFrame.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>

#include <wx/treectrl.h>
#include <map>


class SceneTree : public wxTreeCtrl
{
public:
	SceneTree(EditorFrame* editor,wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style);
	void addSceneNode( Agmd::SceneNode* node );
	void removeSceneNode( Agmd::SceneNode* node );
	void setSelectedSceneNode( Agmd::SceneNode* pick );
	Agmd::SceneNode* getSelectedSceneNode();
private:
	virtual void OnSelect( wxTreeEvent& event );
	std::map<Agmd::SceneNode*,wxTreeItemId> m_nodes;
	std::map<wxTreeItemId,Agmd::SceneNode*> m_nodesId; //reverse search
	EditorFrame* m_editor;
};

#endif
#endif //_SCENETREE_H_
