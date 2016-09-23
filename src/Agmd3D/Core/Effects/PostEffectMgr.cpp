#include <Core/Effects/PostEffectMgr.h>

SINGLETON_IMPL(Agmd::PostEffectMgr)

namespace Agmd
{
    PostEffectMgr::PostEffectMgr()
    {
    }

    PostEffectMgr::~PostEffectMgr()
    {
    }

    void PostEffectMgr::AddEffect(PostEffectPtr effect)
    {
        m_Effects.push_back(effect);
    }

    void PostEffectMgr::ApplyEffect(Texture& input, Texture& output)
    {
        size_t numeffect = m_Effects.size();
        for (size_t i = 0; i < numeffect; i++)
        {
            if (!(i % 2))
                m_Effects[i]->ApplyEffect(input, output);
            else m_Effects[i]->ApplyEffect(output, input);
        }
        if (!(numeffect % 2))
            std::swap(input, output);
    }

    bool PostEffectMgr::HaveEffect() const
    {
        return m_Effects.size() > 0;
    }
}
