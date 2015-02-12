///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EDITORFRAME_H__
#define __EDITORFRAME_H__
#ifdef USE_EDITOR


#include <Core/SceneNode/RootNode.h>


#include <wx/treectrl.h>
class SceneTree : public wxTreeCtrl
{
public:
	SceneTree();

	void setRootNode(Agmd::RootNode);
private:
	Agmd::RootNode* m_sceneTree;
};

#endif
#endif //__EDITORFRAME_H__
