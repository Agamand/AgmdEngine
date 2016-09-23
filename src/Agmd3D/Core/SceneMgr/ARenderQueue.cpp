#include "ARenderQueue.h"
#include "Node.h"

Agmd::Drawable::Drawable(ANode* node) :
    model(node->GetModel()),
    mat(node->GetMaterial()),
    transform((node->GetTransform()))
{
}

Agmd::ARenderQueue::ARenderQueue()
{
    for (a_uint32 i = 0; i < MAX_TYPE; i++)
        m_drawable[i].reserve(1000);
}

void Agmd::ARenderQueue::Push(ANode* node)
{
    Drawable d(node);
    m_drawable[d.mat->GetRenderQueue()].emplace_back(d);
}

void Agmd::ARenderQueue::Clear()
{
    for (a_uint32 i = 0; i < MAX_TYPE; i++)
        m_drawable[i].clear();
}

const a_vector<Agmd::Drawable>& Agmd::ARenderQueue::GetDrawable(TRenderType type /*= TYPE_DIFFUSE*/) const
{
    return m_drawable[type];
}
