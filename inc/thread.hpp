#ifndef THREAD_H
#define THREAD_H

#include "uncopyable.hpp"
#include "runnable.hpp"

namespace advcpp {

class ThreadProxy;

class Thread : private Uncopyable {
public:
	explicit Thread(Runnable& a_func);
    ~Thread();

    void Join();
    void Detach();
    
    void Cancel();
    
    bool operator==(const Thread& a_other) const;
    bool operator!=(const Thread& a_other) const;
    
public:
	static void SleepMicroSeconds(unsigned long a_microSeconds);
	static void Yield();

private:	
	//bool m_joinable;
	//bool m_detachable;
	ThreadProxy* m_thread;
	//pthread_t m_thread;

private:
    static void* Start(void*);
};

} //advcpp

#endif // THREAD_H
