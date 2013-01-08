#include <AgmdPhysics\Core\PhysicsMgr.h>


namespace AgmdPhysics
{
    SINGLETON_IMPL(PhysicsMgr);

    extern "C" __declspec(dllexport) void LoadPlugin()
    {
        PhysicsMgr::Instance();
    }


    extern "C" __declspec(dllexport) void UnloadPlugin()
    {
        PhysicsMgr::Instance();
    }

    PhysicsMgr::PhysicsMgr() :
    m_uidt(0)
    {}

    void PhysicsMgr::Add(Entities* _entitie)
    {
        m_evEntities.push_back(_entitie);
    }

    void PhysicsMgr::Remove(Entities* _entitie)
    {
        
    }

    void PhysicsMgr::Update(uint64 dt)
    {
        m_uidt = dt;
        std::size_t size = m_evEntities.size();
        for(std::size_t i = 0; i < size; i++)
            m_evEntities[i]->Update(dt);
        
        for(std::size_t i = 0; i < size; i++)
            TestCollision(m_evEntities[i]);
    }

    void PhysicsMgr::TestCollision(Entities* ent)
    {
        std::size_t size = m_evEntities.size();
        for(std::size_t i = 0; i < size; i++)
        {
            if(m_evEntities[i] == ent)
                continue; //Skip self-collision
            Intersection inter;
            if(ent->GetIntersection(m_evEntities[i],inter))
                m_ivIntersection.push_back(inter);
        }
    }
}
