#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

namespace advcpp {

class Mutex {
public:
    explicit Mutex();
    ~Mutex();

    void Lock();
    void UnLock();
private:
    Mutex(const Mutex&); //no copy
    Mutex& operator=(const Mutex&); //no copy

    pthread_mutex_t m_mutex;
};

} //advcpp

#endif //MUTEX_HPP
