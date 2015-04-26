#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_


#include <CommonDefines.h>
#include <Thread/Thread.h>

#include <queue>
#include <vector>
#include <functional>

typedef void (*Functor)();
class CThreadPool;
class CJob
{
public:
    CJob(Functor _run): run(_run) {}
    Functor run;
    friend class CThreadPool;
private:
};

class CThreadPool
{
public:
    CThreadPool(a_uint32 poolSize = 2);
    //void init();
    void start();
	template<class J>
    void AddJob(J&& j);
    Mutex& GetMutex() {return m_mutex;}

    friend class IThread;
private:
    std::queue<std::function<void()>> m_jobs;
    std::vector<IThread> m_threads;
    Mutex m_mutex;
};


class IThread :  public CThread{
public:
    IThread(CThreadPool* manager) : CThread(), m_manager(manager) {}
    virtual a_uint32 Run()
    {
        Mutex& mutex = m_manager->GetMutex();
        while(true)
        {
            //if

            //get next jobs
            mutex.Lock();
            if(m_manager->m_jobs.empty()){
                mutex.Unlock();
                //sleep for  few seconds or wait for wake up
                
                continue;
            }

            std::function<void()> job = m_manager->m_jobs.front();
            m_manager->m_jobs.pop();
            mutex.Unlock();

            // handle Job;
            job();
        }
    }
private:
    CThreadPool* m_manager;
};




CThreadPool::CThreadPool( a_uint32 poolSize /*= 2*/ )
{
    m_threads.reserve(poolSize);
    for(a_uint32 i = 0; i < poolSize; i++)
    {
        m_threads.push_back(IThread(this));
    }
}

void CThreadPool::start()
{
    for(a_uint32 i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].Init();
    }
}
template<class Job>
void CThreadPool::AddJob( Job&& job )
{
    m_mutex.Lock();
    m_jobs.push(job);
    m_mutex.Unlock();
}






#endif