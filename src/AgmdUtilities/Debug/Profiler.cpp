/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Debug/Profiler.h>


void Profiler::StartProfiler()
{
    Profiler* profiler = GetProfiler();
    if (!profiler)
        return;
    profiler->timer.start();
}

void Profiler::Start(std::string name)
{
    s_Profiler->m_operations.push_back(Operation(name, s_Profiler->timer.getElapsedTimeInMicroSec()));
    s_Profiler->cur_operation = &s_Profiler->m_operations[s_Profiler->m_operations.size() - 1];
}

void Profiler::End()
{
    s_Profiler->cur_operation->diff_time = s_Profiler->timer.getElapsedTimeInMicroSec() - s_Profiler->cur_operation->cur_time;
}

void Profiler::ResetProfiler()
{
    GetProfiler();
    s_Profiler->m_operations.clear();
    s_Profiler->timer.stop();
}


void Profiler::ShowProfilerInfo()
{
    size_t size = s_Profiler->m_operations.size();
    printf("SHOW PROFILER INFO : end_timer %.3f us, operation_count : %d\n", s_Profiler->timer.getElapsedTimeInMicroSec(), size);
    for (size_t i = 0; i < size; i++)
        printf("OPERATION \"%s\"  at %.3f us, diff_time : %.3f us\n", s_Profiler->m_operations[i].name.c_str(), s_Profiler->m_operations[i].cur_time, s_Profiler->m_operations[i].diff_time);

    system("pause");
}


Profiler::Profiler() :
    cur_operation(NULL)
{
}


Profiler* Profiler::GetProfiler()
{
    if (!s_Profiler)
        s_Profiler = new Profiler();

    return s_Profiler;
}

Profiler* Profiler::s_Profiler = NULL;

Profiler::Operation::Operation() :
    name(""), cur_time(0), diff_time(0)
{
}

Profiler::Operation::Operation(std::string& _name, double time) :
    name(_name), cur_time(time), diff_time(0)
{
}
