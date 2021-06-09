#include <errno.h>
#include <assert.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "thread.hpp"
#include "threadproxy.hpp"
#include "objProxy.hpp"
#include "thread_exceptions.hpp"
#include "logger.hpp"

namespace advcpp {

Thread::Thread(Runnable& a_func)
: m_thread(new ThreadProxy(a_func))
{}

Thread::~Thread()
{
	delete m_thread;
}

void Thread::Join()
{
    m_thread->Join();
}

void Thread::Detach()
{
	m_thread->Detach();
}

void Thread::Cancel()
{
	m_thread->Cancel();
}

bool Thread::operator==(const Thread& a_other) const
{
	return *m_thread == *(a_other.m_thread);
}

bool Thread::operator!=(const Thread& a_other) const
{
	return !(*this == a_other);
}

void Thread::Yield()
{
    ThreadProxy::Yield();
}

void Thread::SleepMicroSeconds(unsigned long a_microSeconds)
{
    ThreadProxy::SleepMicroSeconds(a_microSeconds);
}

} //advcpp
