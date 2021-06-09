#ifndef THREAD_PROXY_H
#define THREAD_PROXY_H

#include <pthread.h>
#include "uncopyable.hpp"
#include "runnable.hpp"

namespace advcpp {

class ThreadProxy : private Uncopyable {
public:
	explicit ThreadProxy(Runnable& a_func);
    ~ThreadProxy();

    void Join();
    void Detach();
    
    void Cancel();
    
    bool operator==(const ThreadProxy& a_other) const;
    bool operator!=(const ThreadProxy& a_other) const;
    
public:
	static void SleepMicroSeconds(unsigned long a_microSeconds);
	static void Yield();

private:	
	bool m_joinable;
	bool m_detachable;
	pthread_t m_thread;

private:
    static void* Start(void*);
	// ThreadProxy() = default;
	// ~ThreadProxy() = default;
	
	pthread_t& operator()();
};

} //advcpp

#endif // THREAD_PROXY_H
