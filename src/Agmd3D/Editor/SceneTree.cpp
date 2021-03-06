#include <Editor/SceneTree.h>
#ifdef USE_EDITOR


//static data
/*
enum NodeType
{
ROOT_NODE,
DISPLAYABLE_NODE,
LIGHT_NODE,
MESH_NODE,
CAMERA_NODE
};

*/
const char* static_string[] = {
    "Root",
    "DisplayNode",
    "Light",
    "Mesh",
    "CameraNode",
    "TreeNode"
};

void SceneTree::addSceneNode( Agmd::SceneNode* node )
{
    Agmd::SceneNode* parent = node->getParent();
    std::map<Agmd::SceneNode*,wxTreeItemId>::iterator itr;
    if((itr = m_nodes.find(parent)) != m_nodes.end())
    {
        wxTreeItemId id = m_nodes[parent];
        m_nodes[node] = AppendItem(id,wxString(static_string[node->getType()]));
        m_nodesId[m_nodes[node]] = node;
        if(!node->isEmpty())
        {
            const a_vector<Agmd::SceneNode*>& children = node->GetChilden();
            for(auto i = 0; i < children.size(); ++i)
            {
                addSceneNode(children[i]);
            }
        }
    }else if(node->getType() ==  Agmd::NodeType::ROOT_NODE)
    {
        wxTreeItemId idRoot = GetRootItem();
        m_nodes[node] = AppendItem(idRoot,wxString(static_string[node->getType()]));
        m_nodesId[m_nodes[node]] = node;
    }
}

void SceneTree::removeSceneNode( Agmd::SceneNode* node )
{
    std::map<Agmd::SceneNode*,wxTreeItemId>::iterator itr;
    if((itr = m_nodes.find(node)) != m_nodes.end())
    {
        wxTreeItemId id = m_nodes[node];
        m_nodes.erase(itr);
        m_nodesId.erase(m_nodesId.find(id));
        if(GetSelection() ==id)
            UnselectAll();
        Delete(id);
    }
    
}

void SceneTree::setSelectedSceneNode( Agmd::SceneNode* node )
{
    std::map<Agmd::SceneNode*,wxTreeItemId>::iterator itr;
    if((itr = m_nodes.find(node)) != m_nodes.end())
    {
        SelectItem(itr->second);
    }else UnselectAll();
}

Agmd::SceneNode* SceneTree::getSelectedSceneNode()
{
    wxTreeItemId id =GetSelection();
    std::map<wxTreeItemId,Agmd::SceneNode*>::iterator itr;
    if((itr = m_nodesId.find(id)) != m_nodesId.end())
    {
        return itr->second;
    }
    return NULL;
}

SceneTree::SceneTree( EditorFrame* editor,wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, long style ) : wxTreeCtrl(parent,id,pos,size,style),
    m_editor(editor)
{
    Connect(this->GetId(),wxEVT_KEY_DOWN,wxKeyEventHandler(SceneTree::keyPressed));
    Connect(this->GetId(),wxEVT_KEY_UP,wxKeyEventHandler(SceneTree::keyReleased));
    Connect( wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler( SceneTree::OnSelect ), NULL, this );
}

void SceneTree::OnSelect( wxTreeEvent& event )
{
    wxTreeItemId id = event.GetItem();
    std::map<wxTreeItemId,Agmd::SceneNode*>::iterator itr;
    if((itr = m_nodesId.find(id)) != m_nodesId.end())
    {
        m_editor->__selectNode(itr->second);
    }else m_editor->__selectNode(NULL);
}

void SceneTree::keyPressed(wxKeyEvent& event) {
//printf("%c pressed\n",event.GetKeyCode());
}
void SceneTree::keyReleased(wxKeyEvent& event) {
//printf("%c release\n",event.GetKeyCode());
    a_uint8 key = event.GetKeyCode();
    Agmd::SceneNode* selected = getSelectedSceneNode();
    if(key == 127 && selected && selected->getParent())
    {
        selected->getParent()->removeChild(selected);
//delete selected
    }
}

#endif
