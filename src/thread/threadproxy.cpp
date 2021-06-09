#include <errno.h>
#include <assert.h>
#include <stdexcept>
#include <unistd.h>
#include <iostream>

#include "threadproxy.hpp"
#include "objProxy.hpp"
#include "thread_exceptions.hpp"
#include "logger.hpp"

namespace advcpp {

void* ThreadProxy::Start(void* a_arg) {
	assert(a_arg);
	CloningProxy<Runnable>* pproxy = static_cast<CloningProxy<Runnable>*>(a_arg);
	Runnable* runnable = pproxy->Clone();
	pproxy->Notify();
	try {
		runnable->operator()();
	}
	catch(const std::exception& ex) {
		GetLogger().exception(ex);
	}
	
	delete runnable;
	
    return 0;
}

ThreadProxy::ThreadProxy(Runnable& a_func)
: m_joinable(true)
, m_detachable(true)
{
	CloningProxy<Runnable> proxy(a_func);
	proxy.Wait();
    const int TRIES = 3;
	int sleepTimeUs = 80;
	for(int i = 0; i < TRIES; ++i) {
		int result = pthread_create(&m_thread, 0, Start, &proxy);
	    switch(result) {
	    	case 0:
	    		proxy.Wait();
	    		return;
			case EINVAL:
			case EPERM:
				assert(!"pthread_create failed");
				break;
			case EAGAIN:
				SleepMicroSeconds(sleepTimeUs);
				sleepTimeUs = sleepTimeUs * sleepTimeUs;
				break;
    	}
	}
	throw ThreadLackResourcesException();
}

ThreadProxy::~ThreadProxy()
{
	if(m_joinable && m_detachable) {
		assert(!"thread was not joined / detached");
		GetLogger().log("thread was not joined / detached");
		std::terminate();
    }
}

void ThreadProxy::Join()
{
    if(!m_joinable || !m_detachable) {
    	throw ThreadAlreadyJoinedException();
    }
    int result = pthread_join(m_thread, 0);
    switch(result) {
    	case 0:
    		m_joinable = false;
    		m_detachable = false;
    		break;
    	case EDEADLK:
    		throw ThreadJoiningEachOtherException();
    		break;
    	default:
    		assert(!"thread join failed");
    }
}

void ThreadProxy::Detach()
{
	if(!m_joinable || !m_detachable) {
        throw ThreadAlreadyJoinedException();
    }
    int result = pthread_detach(m_thread);
	switch(result) {
    	case 0:
    		m_joinable = false;
    		m_detachable = false;
    		break;
    	default:
    		assert(errno != EINVAL);
    		assert(!"thread join failed");
	}
}

void ThreadProxy::Cancel()
{
	if(!m_joinable) {
        throw ThreadAlreadyJoinedException();
    }
    int result = pthread_cancel(m_thread);
	switch(result) {
    	case 0:
    		void* exit;
    		result = pthread_join(m_thread, &exit);
    		if(result == 0 && exit == PTHREAD_CANCELED) {
    			m_joinable = false;
    			m_detachable = false;
    		}
    		break;
    	default:
    		assert(result != ESRCH);
    		assert(!"thread Cancel failed");
	}
}

bool ThreadProxy::operator==(const ThreadProxy& a_other) const
{
	return pthread_equal(m_thread, a_other.m_thread);
}

bool ThreadProxy::operator!=(const ThreadProxy& a_other) const
{
	return !(*this == a_other);
}

void ThreadProxy::Yield()
{
    int result = pthread_yield();
    assert(result == 0);
}

void ThreadProxy::SleepMicroSeconds(unsigned long a_microSeconds)
{
    usleep(a_microSeconds);
}

} //advcpp
