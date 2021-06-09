#include <cerrno>
#include <assert.h>
#include "semaphore.hpp"
#include "semaphore_exceptions.hpp"

namespace advcpp {

Semaphore::Semaphore(size_t a_size) {
    if(0 != sem_init(&m_sem, 0, a_size)) {
        assert(errno != ENOSYS);
        assert(errno != EINVAL);
        assert(!"sem_init failed");
    }
}

Semaphore::~Semaphore() {
    if(0 != sem_destroy(&m_sem)) {
        assert(errno != EINVAL);
        assert(!"sem_destroy failed");
    }
}

void Semaphore::Acquire() {
    if(0 != sem_wait(&m_sem)) {
        assert(errno != EINVAL);
        assert(errno != EINTR);
        if(errno == ETIMEDOUT) {
        	throw SemaphoreTimedOut();
        }
        if(errno == EAGAIN) {
        	throw SemaphoreBlocked();
        }
        else {
        	assert(!"sem_wait failed");
        }
    }
}

void Semaphore::Release() {
    if(0 != sem_post(&m_sem)) {
        assert(errno != EINVAL);
        if(errno == EOVERFLOW) {
            throw SemaphoreOverFlow();
        }
        else {
            assert(!"sem_post failed");
        }
    }
}

} //advcpp
