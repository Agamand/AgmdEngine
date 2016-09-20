/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _PROFILER_
#define _PROFILER_

#include <AgmdUtilities\Utilities\Timer.h>

#include <cstdlib>

#include <string>
#include <Container/Vector.h>

class Profiler
{
public:
    static void StartProfiler();
    static void Start(std::string name);
    static void End();
    static void ResetProfiler();

    static void ShowProfilerInfo();

private:
    struct Operation
    {
        Operation();
        Operation(std::string&, double);
        std::string name;
        double diff_time;
        double cur_time;
    };

    Profiler();
    Operation* cur_operation;

    static Profiler* GetProfiler();
    static Profiler* s_Profiler;

    a_vector<Operation> m_operations;
    Timer timer;
};


#ifdef PROFILING_TIME
#define PROFILE_INIT() ;
#else
#define PROFILE_INIT() ;
#endif

#ifdef PROFILING_TIME
#define PROFILE_START() ;
#else
#define PROFILE_START() ;
#endif

#ifdef PROFILING_TIME
#define PROFILE_END() ;
#else
#define PROFILE_END() ;
#endif


#ifdef PROFILING_TIME
#define PROFILER_INIT() \
    Profiler::ResetProfiler(); \
    Profiler::StartProfiler();
#else
#define PROFILER_INIT() ;
#endif

#ifdef PROFILING_TIME
#define PROFILER_INFO() \
    Profiler::ShowProfilerInfo();
#else
#define PROFILER_INFO() ;
#endif


#ifdef PROFILING_TIME
#define PROFILER(func) \
    Profiler::start(#func); \
    func;\
    Profiler::end();
#else
#define PROFILER(func) func;
#endif


#ifdef PROFILING_TIME
#define PROFILE_TIME(func) \
    diff = timer.getElapsedTimeInMicroSec() - _timer; \
    _timer += diff; \
    printf("Time at %s : %f us, diff : %f us\n",#func,_timer,diff);
#else
#define PROFILE_TIME(func) ;
#endif


#endif
