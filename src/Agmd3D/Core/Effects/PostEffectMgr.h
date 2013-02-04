/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _POSTEFFECTMGR_H_
#define _POSTEFFECTMGR_H_

#include <Core/Texture/Texture.h>
#include <Core/Effects/PostEffect.h>

#include <Utilities/Singleton.h>

#include <vector>

namespace Agmd
{
    class AGMD3D_EXPORT PostEffectMgr : public Singleton<PostEffectMgr>
    {
        MAKE_SINGLETON(PostEffectMgr)
    public:
        PostEffectMgr();
        ~PostEffectMgr();

        void ApplyEffect(Texture& input, Texture& output);
        void AddEffect(PostEffectPtr effect);
        bool HaveEffect() const;
    private:
        std::vector<PostEffectPtr> m_Effects;
    };

}

#endif /* _POSTEFFECTMGR_H_ */
